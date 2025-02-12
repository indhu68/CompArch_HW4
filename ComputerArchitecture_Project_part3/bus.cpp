#include <ctime>
#include <cstdlib>
#include <cstdio>

#include "bus.hpp"

//
// The constructor
//
Bus::Bus() {
    srand(time(NULL));
}

//
// Adds the cache to the cluster
//
void Bus::addCache(Cache *cache) {
    /*while (true) {
        cache->id = rand() % 1001;
        
        bool found = false;
        for (Cache *c : cache_cluster) {
            if (c->id == cache->id) {
                found = true;
                break;
            }
        }
        
        if (!found) break;
    }*/
    
    cache_cluster.push_back(cache);
}

//
// Checks to see if anything on the cache cluster has the value
//
int Bus::checkCacheCluster(uint32_t address, int id) {
    for (size_t i = 0; i<cache_cluster.size(); i++) {
        Cache *c = cache_cluster.at(i);
        if (c->id == id) continue;
        
        if (c->hasAddress(address)) {
            return i;
        }
    }

    return -1;
}

//
// Invalidate all the caches at a particular address
//
void Bus::invalidateCaches(uint32_t address, int id) {
    for (size_t i = 0; i<cache_cluster.size(); i++) {
        Cache *c = cache_cluster.at(i);
        if (c->id == id) continue;
        c->invalidate(address);
    }
}

//
// Pulls data from a shared cache cluster
//
std::vector<uint32_t> Bus::getCacheData(uint32_t address, int size, int pos) {
    Cache *c = cache_cluster.at(pos);
    return c->getLineData(address);
}

