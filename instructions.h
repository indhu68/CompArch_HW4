// Decode instruction
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <iostream>
#include <bitset>
#include <string>
#include <vector>

#include <tuple>
using namespace std;

void printControlLines();
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeRType(uint32_t input);
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeRType_Word(uint32_t input);
tuple<std::string, uint8_t, uint8_t, uint8_t,uint16_t> decodeIType(uint32_t input);
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeSType(uint32_t input);
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeSBType(uint32_t input); 
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeUJType(uint32_t input, uint32_t opcode); 
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeUType(uint32_t input, uint32_t opcode); 
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeFRType(uint32_t input); 
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t>decodeFSType(uint32_t input); 
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeFIType(uint32_t input); 


#endif
