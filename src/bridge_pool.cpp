#include "bridge_pool.h"
#include "glob_match.h"
#include <cstdio>
#include <cstring>

std::string BridgePool::make_key(const std::string &bridge_binary,
                                   const std::string &plugin_path,
                                   uint32_t format,
                                   IsolationMode mode) {
    switch (mode) {
    case IsolationMode::SHARED:
        // Group by bridge binary + format (one process per arch+format)
        return bridge_binary + "|" + std::to_string(format);

    case IsolationMode::PER_BINARY:
        // Group by plugin binary path
        return bridge_binary + "|" + plugin_path;

    case IsolationMode::PER_INSTANCE:
        // Unique key per instance
        return bridge_binary + "|instance|" + std::to_string(++instance_counter);
    }
    return bridge_binary;
}

IsolationMode BridgePool::resolve_mode(const std::string &plugin_id,
                                         const std::string &plugin_name,
                                         const std::string &plugin_path) const {
    for (const auto &ov : overrides) {
        // Managed-file rows key on the stable plugin ID only — a display name
        // that happens to look like an ID must not pull in someone else's
        // policy. config.toml rows keep the historical ID-or-name glob.
        if (ov.exact_plugin_id) {
            if (ov.match == plugin_id) return ov.mode;
            continue;
        }
        // config.toml rows glob against every key a user could reasonably
        // have written: the exposed plugin ID, the display name, and the
        // plugin file path.
        if (keepsake_glob_match(ov.match, plugin_id) ||
            keepsake_glob_match(ov.match, plugin_name) ||
            (!plugin_path.empty() && keepsake_glob_match(ov.match, plugin_path))) {
            return ov.mode;
        }
    }
    return default_mode;
}

BridgeProcess *BridgePool::acquire(const std::string &bridge_binary,
                                     const std::string &plugin_path,
                                     uint32_t format,
                                     IsolationMode mode) {
    std::lock_guard<std::mutex> lock(pool_mutex);
    std::string key = make_key(bridge_binary, plugin_path, format, mode);

    // Reuse existing process if available
    auto it = pool.find(key);
    if (it != pool.end() && it->second->alive) {
        it->second->ref_count++;
        fprintf(stderr, "keepsake: reusing bridge process for '%s' (refs=%d)\n",
                key.c_str(), it->second->ref_count);
        return it->second;
    }

    // Spawn new bridge process
    auto *bp = new BridgeProcess();
    bp->key = key;
    if (!platform_spawn(bridge_binary, bp->proc)) {
        fprintf(stderr, "keepsake: failed to spawn bridge for '%s'\n",
                bridge_binary.c_str());
        delete bp;
        return nullptr;
    }
    bp->alive = true;
    bp->ref_count = 1;
    pool[key] = bp;

    fprintf(stderr, "keepsake: spawned bridge process for '%s'\n", key.c_str());
    return bp;
}

void BridgePool::release(BridgeProcess *bp) {
    if (!bp) return;
    std::lock_guard<std::mutex> lock(pool_mutex);
    bp->ref_count--;

    if (bp->ref_count <= 0) {
        // Shut down the process
        if (bp->alive) {
            // Send SHUTDOWN with instance_id=0 (shut down entire process)
            uint32_t zero_id = 0;
            ipc_write_instance_msg(bp->proc.pipe_to, IPC_OP_SHUTDOWN, zero_id);

            uint32_t op;
            std::vector<uint8_t> resp;
            ipc_read_msg(bp->proc.pipe_from, op, resp, 5000);
            platform_kill(bp->proc);
            bp->alive = false;
        }

        pool.erase(bp->key);
        delete bp;
    }
}

void BridgePool::abandon(BridgeProcess *bp) {
    if (!bp) return;
    std::lock_guard<std::mutex> lock(pool_mutex);
    bp->ref_count--;

    if (bp->ref_count <= 0) {
        if (bp->alive) {
            platform_force_kill(bp->proc);
            bp->alive = false;
        }

        pool.erase(bp->key);
        delete bp;
    }
}

void BridgePool::terminate(BridgeProcess *bp) {
    if (!bp) return;
    std::lock_guard<std::mutex> lock(pool_mutex);
    if (bp->alive) {
        platform_force_kill(bp->proc);
        bp->alive = false;
    }
}

void BridgePool::shutdown_all() {
    std::lock_guard<std::mutex> lock(pool_mutex);
    for (auto &kv : pool) {
        auto *bp = kv.second;
        if (bp->alive) {
            uint32_t zero_id = 0;
            ipc_write_instance_msg(bp->proc.pipe_to, IPC_OP_SHUTDOWN, zero_id);

            uint32_t op;
            std::vector<uint8_t> resp;
            ipc_read_msg(bp->proc.pipe_from, op, resp, 2000);
            platform_kill(bp->proc);
            bp->alive = false;
        }
        delete bp;
    }
    pool.clear();
}
