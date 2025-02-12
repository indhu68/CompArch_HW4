#pragma once

#include <vector>

#include "cache.hpp"

class Cache;

class Bus {
public:
    explicit Bus();
    
    void addCache(Cache *cache);
    int checkCacheCluster(uint32_t address, int id);
    void invalidateCaches(uint32_t address, int id);
    std::vector<uint32_t> getCacheData(uint32_t address, int size, int pos);
private:
    std::vector<Cache *> cache_cluster;
};

