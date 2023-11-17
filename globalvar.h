#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <string>
#include<cstdint>
using namespace std;
// External variables
extern int INSTR_START;
extern int INSTR_END;
extern int ARRAY_A_START;
extern int ARRAY_A_END;
extern int ARRAY_B_START;
extern int ARRAY_B_END;
extern int ARRAY_C_START;
extern int ARRAY_C_END;
extern const int RAM_SIZE;
extern int clockCycle;
extern string output[256];
extern string output1[256];
/*class CPU {
public:
    // CPU-specific methods
    int execute();

};*/
// RAM class declaration
class RAM {
public:
    RAM(uint32_t size); // Constructor
    std::string read(uint32_t address) const;
    void write(uint32_t address, const std::string& data);
    

private:
    
    
    std::vector<std::string> memory; 
};


extern RAM memory;

#endif
