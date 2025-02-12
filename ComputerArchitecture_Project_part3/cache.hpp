#pragma once

#include <cstdint>

#include "bus.hpp"

class Bus;

//
// TODO: Not sure if we need this yet, but whatever
//
enum class CacheState {
    Invalid,
    Exclusive,
    Shared,
    Modified
};

struct CacheEntry {
    uint8_t *data;
    uint32_t tag = 0;
    bool valid = false;
    CacheState state = CacheState::Invalid;
};

class Cache {
public:
    explicit Cache(int size, int line_size, int assoc = 1);
    void setBus(Bus *bus);
    void print();
    bool hasAddress(uint32_t address);
    void invalidate(uint32_t address);
    uint32_t getData(uint32_t address, int size);
    std::vector<uint32_t> getLineData(uint32_t address);
    bool setData(uint32_t address, uint32_t data, int size);
    
    int id = 0;
private:
    CacheEntry **cache;
    Bus *bus;
    int blocks = 0;
    int line_size = 0;
    
    int tag_width = 0;
    int offset_width = 0;
    int set_width = 0;
};

