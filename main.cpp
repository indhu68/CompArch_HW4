#include <iostream>
#include <vector>
#include <map>
#include "instructions.h"
#include<bitset>
#include<string>
#include<ctime>
#include<stdint.h>
#include<tuple>
#include "globalvar.h"
#define RAM_SIZE 0x13FF
#include<mutex>
#include<thread>
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
    string output[256];
    string output1[256];
    int count1 =0;
    int count2 =0;
    vector<int>registers(10,0);
    int PC;
    uint32_t ram[RAM_SIZE];
    int clockCycle = 0;
    uint32_t instructions;
    std::mutex clockCycleMutex;
    std::mutex ramCountMutex;
     void incrementClockCycle();
string intToBinaryString(uint16_t value) {
    // Convert the integer value to a 16-bit binary string.
    string binaryStr = bitset<16>(value).to_string();

    // Find the first occurrence of '1' in the binary string.
    size_t firstOneIndex = binaryStr.find('1');

    // Check if '1' is found in the string.
    if (firstOneIndex != string::npos) {
        // If '1' is found, return the substring starting from the first '1'.
        return binaryStr.substr(firstOneIndex);
    }

    // If the binary string contains only '0's (i.e., value is zero), return "0".
    return "0";
}
class Bus {
public:
    Bus(RAM& sharedMemory) : sharedMemory(sharedMemory) {}

    std::string read(uint32_t address) {
        std::lock_guard<std::mutex> guard(busMutex);
        return sharedMemory.read(address);
    }

    void write(uint32_t address, const std::string& value) {
        std::lock_guard<std::mutex> guard(busMutex);
        sharedMemory.write(address, value);
    }
    void decode(const std::string& input) {
        
         uint8_t opcode = getOpcode(input);
       

        switch (opcode) {
            case 51:  // R-type
                 decodeRType(input);
                break;
            case 59: //R-type Word
		          decodeRType_Word(input);
		         break;
            case 19:  // I-type
                decodeIType(input);
                break;	
            case 27:  // I-type
                decodeIType(input);
                break;	
            case 3:  // I-type
               decodeIType(input);
                break;	
            case 35:  // S-type
               decodeSType(input);
                break;
            case 99:  // SB-type
                decodeSBType(input);
                break;	
            case 103:  // UJ-type
               decodeUJType(input);
                break;	
            case 111:  // UJ-type
                decodeUJType(input);
                break;
            case 55:  // U-type
                decodeUType(input);
                break;	
            case 23:  // U-type
                decodeUType(input);
                break;
             case 83: //FR-type
	            decodeFRType(input);
	            break;
             case 39: //FS-type
	            decodeFSType(input);
	            break;
             case 7: //FI-type
	            decodeFIType(input);
	            break;

}
    }

    int execute(const std::string& input, Bus& bus) {
        uint32_t rs1 = getrs1(input);
        uint32_t rs2 = getrs2(input);
        uint32_t rd = getrd(input);
        uint32_t fun7 = getfun7(input);
        uint32_t func3 = getfun3(input);
        uint32_t opcode = getOpcode(input);
        if (func3 == 2 && opcode == 3) { //lw
        int address = (rs1 == 0) ? 1024 : (rs1 == 1) ? 2048 : 3072;
        std::cout << "destination::" << rd << "\n";
        registers[rd] = address;
        
       
    } else if (func3 == 0 && fun7 == 0 && opcode == 51) { //add
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers[rd] = registers[rs1] + registers[rs2];
            incrementClockCycle();
            
            std::cout << "Clock cycle :" << clockCycle << " Stall" << "\n";
        }
    } else if (func3 == 2 && opcode == 7) { //flw
        if (rs1 >= 0 && rs1 < 10) {
            // Simulate type conversion from integer to float
            registers[rd] = registers[rs1] + getimm11_0(input);
            incrementClockCycle();
        }
    } else if (opcode == 83 && fun7 == 0) { //fadd.s
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers[rd] = registers[rs1] + registers[rs2];
            output[count1] = to_string(count1+1) + "  " + to_string(registers[rs1]) + " + " + to_string(registers[rs2]) + " = " + std::to_string(registers[rd]);
            count1 += 1;
            incrementClockCycle();
            cout << "Clock cycle :" << clockCycle << " Stall" << "\n";

        }
    }else if (opcode ==83 && fun7 ==4){//fsub.s  
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            registers[rd] = registers[rs1] - registers[rs2];
            output1[count2] = to_string(count2+1) + "  " + to_string(registers[rs1]) + " - " + to_string(registers[rs2]) + " = " + std::to_string(registers[rd]);
            count2 += 1;
            incrementClockCycle();
            cout << "Clock cycle :" << clockCycle << " Stall" << "\n";

        }
    }else if (opcode == 39) { //fsw
        int address = registers[rs1];
        int a = static_cast<float>(registers[rs2]) + fun7;
        string a_str =to_string(a);
        bus.write(address, a_str);
        incrementClockCycle();
       

    } else if (func3 == 0 && opcode == 19) {
        if (rs1 >= 0 && rs1 < 10) {
            registers[rd] = registers[rs1] + getimm11_0(input);
            
        }
       
    } else if (opcode == 99) {//BLT
        if (rs1 >= 0 && rs1 < 10 && rs2 >= 0 && rs2 < 10) {
            if (registers[rs1] < registers[rs2]) {
                cout << " t0 values is " << registers[rs1] << " and t1 value is " << registers[rs2] << "  " << "\n";
                incrementClockCycle();
                cout << "Clock cycle :" << clockCycle << " Stall" << "\n";
                
                return 1;
            } else {
                cout << " t0 values is " << registers[rs1] << " and  t1 value is " << registers[rs2] << "\n";
                
                return 0;
            }
        }
    }
    return 2;
}

private:
    RAM& sharedMemory;
    std::mutex busMutex;
};
RAM::RAM(uint32_t size) : memory(size) {}
string RAM::read(uint32_t address) const {
    return memory[address];
}
void RAM::write(uint32_t address, const std::string& value) {
        memory[address] = value;
}

   RAM memory(5120);
   void incrementClockCycle() {
    std::lock_guard<std::mutex> guard(clockCycleMutex);
    clockCycle++;
}

void incrementRAMCount() {
    std::lock_guard<std::mutex> guard(ramCountMutex);
    RAM_COUNT++;
}

//mutex sharedVariableMutex; 
void CPU(Bus& bus, uint32_t startAddress, uint32_t programSize, const std::string& cpuName){
     cout << cpuName << " starting execution." << endl;
     
    bool continueExecution = true;
    int instructionsExecuted = 0;
    vector<string> localOutput;  // Local output for this CPU
    vector<string> localOutput1; // Local output1 for this CPU
    while (continueExecution) {
        for (int i = startAddress; i < (startAddress+programSize); ++i) {
            string instruction = bus.read(i);
            for (int j = 1; j < 4; j++) {
                cout << "\n";
                //std::lock_guard<std::mutex> guard(sharedVariableMutex);
                incrementClockCycle(); 
                cout << "Clock Cycle : " << clockCycle << "  ";
                if (j == 1) {
                    
                    string instruction = bus.read(i);
                    cout << "FETCH INSTRUCTION: " << instruction << "\n";
                    //std::lock_guard<std::mutex> guard(sharedVariableMutex);
                    incrementRAMCount(); 
                    instructions = instructions + 2;
                }
                else if (j == 2) {
                    cout << "DECODE INSTRUCTION: " << instruction << "\n";
                    bus.decode(instruction);
                }
                else if (j == 3) {
                    cout << "EXECUTE INSTRUCTION: " << instruction << "\n";
                    int n = bus.execute(instruction, bus);
                    if (n == 0) {
                        continueExecution = false;
                        break;
                    }}
                    if (continueExecution) {
                instructionsExecuted++;
            }
                }
            
}
        }

   cout << cpuName << " completed execution." << std::endl
              << "Clock cycles: " << clockCycle << std::endl
              << "Instructions executed: " << instructionsExecuted << std::endl
              << "CPI: " << static_cast<float>(clockCycle) / instructionsExecuted << std::endl
              << "Total number of RAM Read/Write Latency: " << RAM_COUNT << std::endl;
}
/*void CPU2(Bus& bus, uint32_t startAddress, uint32_t programSize){
     cout << "CPU2 starting execution." << endl;
    bool continueExecution = true;
    int instructions = 0;

    while (continueExecution) {
        for (int i = startAddress; i < (startAddress+programSize); ++i) {
            string instruction = bus.read(i);
            for (int j = 1; j < 4; j++) {
                cout << "\n";
                //std::lock_guard<std::mutex> guard(sharedVariableMutex);
                clockCycle += 1;
                cout << "Clock Cycle : " << clockCycle << "  ";
                if (j == 1) {
                    string instruction = bus.read(i);
                    cout << "FETCH INSTRUCTION: " << instruction << "\n";
                    RAM_COUNT +=1;
                    instructions = instructions + 1;
                }
                else if (j == 2) {
                    cout << "DECODE INSTRUCTION: " << instruction << "\n";
                    bus.decode(instruction);
                }
                else if (j == 3) {
                    cout << "EXECUTE INSTRUCTION: " << instruction << "\n";
                    int n = bus.execute(instruction, bus);
                    if (n == 0) {
                        continueExecution = false;
                        break;
                    }
                    else {
                        continue;
                    }
                }
            }

        }
    }
    //std::lock_guard<std::mutex> guard(busMutex);
    cout << "\nClockcycles: " << clockCycle
        << "\nInstructions executed: " << instructions-300
        << "\nCPI: " << static_cast<float>(clockCycle) / instructions // Ensuring floating point division
        << "\n";
    cout << "Total number of RAM Read/Write Latency: "<< RAM_COUNT << "\n";
    cout << "CPU2 completed execution." << endl;
}*/
int main() {
     try{
     // Initialize shared memory and bus
    RAM memory(5120); // Assuming RAM size is 5120
    Bus bus(memory);
    for (int j = ARRAY_A_START; j < ARRAY_A_END + 1; j++) {
        string value = intToBinaryString(static_cast<uint16_t>(j));
        bus.write(j, value);

    }

    for (int k = ARRAY_B_START; k < ARRAY_B_END + 1; ++k) {
        string value = intToBinaryString(static_cast<uint16_t>(k));
        bus.write(k, value);
    }

      const std::vector<string> instr1 = { 
        "00000000000000000010000100000011",
        "00000000000000001010000110000011",
        "00000000000000010000000100110011",
        "00000000000000011000000110110011",
        "00000000000000010010001100000111",
        "00000000000000011010001110000111",
        "00000000011000111000010001010011",
        "00000000000000010010001000000011",
        "00000000000000100000001000110011",
        "00000000100000100010000000100111",
        "00000000010000000000000000010011",
        "01000000000001001000000010010011",
        "00000000000100000100000001100011",
    };
    const std::vector<string> instr2 = { 
        "00000000000000000010000100000011",
        "00000000000000001010000110000011",
        "00000000000000010000000100110011",
        "00000000000000011000000110110011",
        "00000000000000010010001100000111",
        "00000000000000011010001110000111",
        "00001000011000111000010001010011",
        "00000000000000010010001000000011",
        "00000000000000100000001000110011",
        "00000000100000100010000000100111",
        "00000000010000000000000000010011",
        "01000000000001001000000010010011",
        "00000000000100000100000001100011",
    };
   

    int startAddressCPU1 =0 ;
    int startAddressCPU2 = 1024;
    uint32_t instrCPU1Size = instr1.size(); // Size of CPU1's instruction set
    uint32_t instrCPU2Size = instr2.size(); // Size of CPU2's instruction set
    // Load instructions for CPU1
    for (uint32_t i = 0; i < instr1.size(); ++i) {
        bus.write(startAddressCPU1 + i, instr1[i]);
    }

    // Load instructions for CPU2 in a different region
    uint32_t offset = 1024; 
    for (uint32_t i = 0; i < instr2.size(); ++i) {
        bus.write(startAddressCPU2 + i, instr2[i]);
    }
 
    thread cpu1Thread(CPU, std::ref(bus), startAddressCPU1, instrCPU1Size, "CPU1");
    thread cpu2Thread(CPU, std::ref(bus), startAddressCPU2, instrCPU2Size, "CPU2");
    // Wait for threads to complete
    cpu1Thread.join();
    cpu2Thread.join();


    
      }catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}