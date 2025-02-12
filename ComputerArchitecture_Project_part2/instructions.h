// Decode instruction
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include<stdint.h>
#include"globalvar.h"
using namespace std;

void printControlLines();
uint8_t getOpcode(const std::string& inst);
uint8_t getrd(const std::string& inst);
uint8_t getfun3(const std::string& inst);
uint8_t getrs1(const std::string& inst);
uint8_t getrs2(const std::string& inst);
uint8_t getfun7(const std::string& inst);
uint16_t getimm11_0(const std::string& inst);
void decodeRType(const std::string& inst);
void decodeRType_Word(const std::string& inst);
void  decodeIType(const std::string& inst);
void decodeSType(const std::string& inst);
void decodeSBType(const std::string& inst); 
void decodeUJType(const std::string& inst); 
void decodeUType(const std::string& inst); 
void decodeFRType(const std::string& inst); 
void decodeFSType(const std::string& inst); 
void decodeFIType(const std::string& inst); 




#endif
