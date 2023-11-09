#include <iostream>
#include <vector>
#include <map>
#include "instructions.h"
#include<bitset>
#include<string>
#include<ctime>

#define RAM_SIZE 0x13FF

    int inst_count = 0;
    int INSTRUCTION_START = 0x0;
    int INSTRUCTION_END = 0x093;
    int STACK_START = 0x200;
    int STACK_END = 0x2FF;
    int ARRAY_A_START = 0x400;
    int ARRAY_A_END = 0x7FF;
    int ARRAY_B_START = 0x800;
    int ARRAY_B_END = 0xBFF;
    int ARRAY_C_START = 0xC00;
    int ARRAY_C_END = 0xFFF;
    int RAM_COUNT = 0;
    vector<string>output(256);
    int count =0;
    vector<int>registers(10,0);
    int PC;
    uint32_t ram[RAM_SIZE];
    int clockCycle = 0;
    uint32_t instruction;
    std::tuple<std::string, uint8_t,uint8_t, uint8_t,uint16_t> decode(uint32_t input) {
        
        uint8_t opcode = input & 0x7F;
        tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> instr_result;

        switch (opcode) {
            case 0b0110011:  // R-type
                instr_result = decodeRType(input);
                break;
            case 0b0111011: //R-type Word
		         instr_result = decodeRType_Word(input);
		         break;
            case 0b0010011:  // I-type
                instr_result = decodeIType(input);
                break;	
            case 0b0011011:  // I-type
                instr_result = decodeIType(input);
                break;	
            case 0b0000011:  // I-type
                instr_result = decodeIType(input);
                break;	
            case 0b0100011:  // S-type
                instr_result = decodeSType(input);
                break;
            case 0b1100011:  // SB-type
                instr_result = decodeSBType(input);
                break;	
            case 0b1100111:  // UJ-type
                instr_result = decodeUJType(input,opcode);
                break;	
            case 0b1101111:  // UJ-type
                instr_result = decodeUJType(input,opcode);
                break;
            case 0b0110111:  // U-type
                instr_result = decodeUType(input,opcode);
                break;	
            case 0b0010111:  // U-type
                instr_result = decodeUType(input,opcode);
                break;
             case 0b1010011: //FR-type
	            instr_result = decodeFRType(input);
	            break;
             case 0b0100111: //FS-type
	            instr_result = decodeFSType(input);
	            break;
             case 0b0000111: //FI-type
	            instr_result = decodeFIType(input);
	            break;

}
return instr_result;
    }

    std::string execute() {
        string returned_inst;
        uint8_t rs1, rs2, rd;
        uint16_t imm;
        std::tie(returned_inst, rd, rs1, rs2, imm) = decode(instruction);
        if (returned_inst == "FSW"){
            int offset = imm;
            int address = registers[rs1] ;
            registers[address] = static_cast<float>(registers[rs2]) + offset;
            RAM_COUNT += 1;
            clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n";  

        }else if (returned_inst=="FLW"){
             if (rs1 >= 0 && rs1 < 10) {
            int offset = imm;
            ram[rd] = ram[registers[rs1]] + offset;
            RAM_COUNT += 1;
            clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; }
            
        }
        else if (returned_inst == "FADD"){
            if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10){
            registers[rd] = registers[rs1] + registers[rs2];
            output[count] = to_string(count+1) + "  " + to_string(registers[rs1]) + " + " + to_string(registers[rs2]) + " = " + to_string(registers[rd]);
            count += 1;
            }
            
        }
        else if (returned_inst == "ADD"){
            if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10){
            registers[rd] = registers[rs1] + registers[rs2];
            clockCycle += 1;
            cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 
            }
        }
        else if (returned_inst == "ADDI"){
            if (rs1 >= 0 && rs1 < 10) {
            uint16_t imm = imm;
            registers[rd] = registers[rs1] + static_cast<int>(imm);
                
            }
        }
        else if (returned_inst == "BLT"){
            if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2< 10) {
            if (registers[rs1] < registers[rs2]) {
                 cout << " r0 value is " << registers[rs1] << " and r1 value is " << registers[rs2] << "  "<< "\n";
                 clockCycle += 1;
                 cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 
                return "loop";
            } else {
                std::cout << " r0 value is " << registers[rs1] << " and  r1 value is " << registers[rs2] << "\n";
                return "end";
            }
        }
            
        }
        else if (returned_inst == "LW"){
            int address = (rs1 == 0) ? ARRAY_A_START : (rs1 == 1) ? ARRAY_B_START : ARRAY_C_START;
            registers[rd] = address;
            RAM_COUNT += 1;
            clockCycle += 1;
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n"; 
            
        }
        return "continue";
    }
    void run() {
    int i = 0;
    int j = INSTRUCTION_START;
    int t =22;
    
    while (t>0) {
        for (int stage = 1; stage <= 3; stage++) {
            clockCycle += 1;  
            std::cout << "Clock Cycle: " << clockCycle << " \n ";
            if (stage == 1) {
                instruction = ram[j +i];
                RAM_COUNT +=1;
                std::cout << "FETCH INSTRUCTION: " <<instruction << "\n";
                inst_count++;
                i=i+1;
            } else if (stage == 2) {
                cout << "DECODE INSTRUCTION: " <<instruction << "\n";
                 decode(instruction);
            } else if (stage == 3) {
                
                cout << "EXECUTE INSTRUCTION: " <<instruction << "\n";
                string condition = execute();
                if (condition == "loop") {
                    i = 0;
                }
                if (condition == "end") {
                    
                        t=0;
                        break;
                
                }
            }}}}

void initializeRAM(uint32_t ram[],int start, int end) {
    for (int i = start; i <= end; ++i) {
        RAM_COUNT += 1;
        ram[i] = static_cast<int>(rand())/10.0f;
    }
}
// Function to load instructions into RAM
void loadInstructions(uint32_t ram[], const std::vector<uint32_t>& instructions, int instructionAddress) {
    for (const uint32_t& inst : instructions) {
        RAM_COUNT += 1;
        ram[instructionAddress++] = inst;
    }
}

int main() {
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = STACK_START; i <= STACK_END; ++i) {
            ram[i] = 0.0f;
    }
    initializeRAM(ram, ARRAY_A_START, ARRAY_A_END);
    initializeRAM(ram, ARRAY_B_START, ARRAY_B_END);
    const std::vector<uint32_t> instr = { 0b0000000000000000010000100000011
    ,0b0000000000000001010000110000011
  ,0b0000000000000010000000100110011
 ,0b0000000000000011000000110110011
    ,0b0000000000000010010001100000111
  ,0b0000000000000011010001100000111
      ,0b0000000011000111000010001010001
      ,0b0000000000000010010001000000011
          ,0b0000000000000100000001000110011
         ,0b0000000100000100010000000100111
         ,0b0000000000100000000000000010011
        ,0b0000000000001001000000010010011
   ,0b0000000000100000100000001100011
};

    loadInstructions(ram, instr, INSTRUCTION_START);
    run();
    float CPI = static_cast<float>(clockCycle /inst_count) ;
    // Print the total number of ticks taken
    cout << "Total simulation ticks: " << clockCycle <<endl;
    cout << "Total instructions: " << inst_count << endl;
    cout << "Calculated CPI: " << CPI << endl;
        // Print the contents of the RAM arrays
        

    std::cout << "Total number of RAM Read/Write Latency: "<< RAM_COUNT << "\n";
    
     
    std::cout << "Array A" << "\n";
    for(int i = 0; i <256; i++){
    cout << ram[i+ARRAY_A_START] << ", ";
    }
    cout  << "\n";
    cout << "Array B" << "\n";
    for(int i =0; i < 256; i++){
    cout << ram[i+ARRAY_B_START] << ", ";
    }
    cout  << "\n";
    cout << "Array C" << "\n";
    for(int i = 0; i < 256; i++){
        cout << ram[i+ARRAY_C_START] << ", ";
    }
    

    return 0;
}

