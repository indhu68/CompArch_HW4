#include <iostream>

#include "bus.hpp"
#include "cache.hpp"

int main(int argc, char **argv) {
    Bus *bus = new Bus;
    Cache *c1 = new Cache(64, 16);
    Cache *c2 = new Cache(64, 16);
    Cache *c3 = new Cache(64, 16);
    Cache *c4 = new Cache(64, 16);
    c1->id = 1;
    c2->id = 2;
    c3->id = 3;
    c4->id = 4;
    c1->setBus(bus);
    c2->setBus(bus);
    c3->setBus(bus);
    c4->setBus(bus);
    std::cout << "=======================================" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    
    // Test 1
    // Read: Read -> Invalid -> Exclusive
    // Host: Cache 1
    std::cout << std::endl << "Address: " << 0x804 << std::endl;
    c1->getData(0x804, 4);
    std::cout << std::endl << "Address: " << 0x964 << std::endl;
    c3->getData(0x964, 4);
    
    // Read: Read -> Invalid -> Shared
    std::cout << std::endl << "Address: " << 0x804 << std::endl;
    c2->getData(0x804, 4);
    std::cout << std::endl << "Address: " << 0x804 << std::endl;
    c3->getData(0x804, 4);
    
    puts("");
    
    //
    // Write -> Invalid -> Modified
    std::cout << std::endl << "Address: " << 0x932 << std::endl;
    c1->setData(0x932, 10, 4);
    
    // Write -> Invalid -> Modified
    std::cout << std::endl << "Address: " << 0x932 << std::endl;
    c2->setData(0x932, 12, 4);
    
    // Write -> Exclusive -> Modified
    std::cout << std::endl << "Address: " << 0x964 << std::endl;
    c3->setData(0x964, 10, 4);
    
    // Write -> Shared -> Modified
    std::cout << std::endl << "Address: " << 0x804 << std::endl;
    c3->setData(0x804, 0x0A0A, 4);
    
    // Write -> Modified -> Modified
    std::cout << std::endl << "Address: " << 0x804 << std::endl;
    c3->setData(0x804, 0x0E0E, 4);
    
    // Read -> Modified
    std::cout << std::endl << "Address: " << 0x804 << std::endl;
    c3->getData(0x804, 4);
    
    // Final print
    std::cout << std::endl;
    std::cout << "=C1=========================" << std::endl;
    c1->print();
    std::cout << std::endl;
    std::cout << "=C2=========================" << std::endl;
    c2->print();
    std::cout << std::endl;
    std::cout << "=C3=========================" << std::endl;
    c3->print();
    std::cout << std::endl;
    std::cout << "=C4=========================" << std::endl;
    c4->print();
    std::cout << std::endl;

    return 0;
}

