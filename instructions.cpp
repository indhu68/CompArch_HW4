

#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include "instructions.h"
#include<tuple>
#include<stdint.h>
#include"globalvar.h"
using namespace std;
enum ControlLines {
    ALU_OP,
    REG_DEST,
    REG_WRITE,
    ALU_SRC,
    JUMP,
    BRANCH,
    MEM_READ,
    MEM_WRITE,
    MEM_TO_REG,
    FLOAT_ADD,
    FLOAT_SUB,
    F_ALU_OP,
    F_REG_WRITE,
    F_MEM_WRITE,
    NUM_CONTROLS
    
};


   void printControlLines(const string& type, const string& instruction, const vector<bool>& controls) {
    cout << "Instruction Type: " << type << "\n"
         << instruction << "\n"
         << "ALU op : " << controls[ALU_OP] << "\n"
         << "Reg dest : " << controls[REG_DEST] << "\n"
         << "Reg write : " << controls[REG_WRITE] << "\n"
         << "ALU src : " << controls[ALU_SRC] << "\n"
         << "Jump : " << controls[JUMP] << "\n"
         << "Branch : " << controls[BRANCH] << "\n"
         << "Memory read : " << controls[MEM_READ] << "\n"
         << "Memory write : " << controls[MEM_WRITE] << "\n"
         << "Float ADD : " << controls[FLOAT_ADD] << "\n"
         << "Float SUB : " << controls[FLOAT_SUB] << "\n"         
         << "Float ALU OP : " << controls[F_ALU_OP] << "\n"
         << "Float Reg Write : " << controls[F_REG_WRITE] << "\n"
         << "Float Mem Write : " << controls[F_MEM_WRITE] << "\n"
         << "Memory to register : " << controls[MEM_TO_REG] << "\n\n";
         
    //return std::make_tuple(RISC_V_inst, dest, src1, src2);   
}
uint8_t getOpcode(const std::string& inst) {
    string opcodeStr = inst.substr(inst.length() - 7, 7); 
    return std::stoi(opcodeStr, nullptr, 2); 
}

uint8_t getrd(const std::string& inst) {
    std::string rdStr = inst.substr(inst.length() - 12, 5); // Extract bits [11:7] for rd
    return std::stoul(rdStr, nullptr, 2);
}

uint8_t getfun3(const std::string& inst) {
 std::string fun3Str = inst.substr(17, 3); // Extract bits [14:12] for the funct3 field
    return std::stoul(fun3Str, nullptr, 2);// Convert binary string to unsigned 8-bit integer
}

uint8_t getrs1 (const std::string& inst) {
    std::string rs1Str = inst.substr(inst.length() - 20, 5); // Extract bits [19:15] for rs1
    return std::stoul(rs1Str, nullptr, 2); // Convert binary string to unsigned integer
}

uint8_t getrs2(const std::string& inst) {
    std::string rs2Str = inst.substr(inst.length() - 25, 5); // Extract bits [24:20] for rs2
    return std::stoul(rs2Str, nullptr, 2); // Convert binary string to unsigned integer and cast to uint8_t
}

uint8_t getfun7(const std::string& inst) {
    std::string fun7Str = inst.substr(0, 7); // Extract the first 7 bits for the funct7 field
    return std::stoul(fun7Str, nullptr, 2); // Convert binary string to unsigned 8-bit integer
}

uint16_t getimm11_0(const std::string& inst) {
   std::string immStr = inst.substr(0, 12); // Extract the first 12 bits for the immediate value
    return std::stoul(immStr, nullptr, 2); // Convert binary string to unsigned integer
}



void decodeRType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    controls[ALU_OP] = 1;
    controls[REG_DEST] = 1;
    controls[REG_WRITE] = 1;

    uint8_t funct3 = getfun3(input);
    uint8_t funct7 = getfun7(input);
    uint8_t rd = getrd(input);
    uint8_t rs1 = getrs1(input);
    uint8_t rs2 =  getrs2(input);
    string RISC_V;
    uint16_t imm =0;
    string instruction;
    
    switch (funct3) {
        case 0:
            switch (funct7) {
                case 0:
                    instruction = "ADD r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "ADD";
                    break;
                case 32:
                    instruction = "SUB r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SUB";
                    break;
                case 1:
                    instruction = "MUL r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "MUL";
                    break;
            }
            break;
       case 1:
            
               switch(funct7){
                   case 1:
			instruction = "MULH r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    break;
                case 0:
                    instruction = "SLL r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SLL";
                    break;
                
   		}
	case 2:
		switch(funct7){
		    case 1:
			instruction = "MULHSU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "MULHSU";
                    break;
		    case 0:
			instruction = "SLT r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "SLT";
                    break;
		    }
	case 3:
		switch(funct7){
		    case 1:
			instruction = "MULHSU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "MULHSU";
                    break;
		    case 0:
			instruction = "SLTU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "SLTU";
                    break;
			}
	case 4:
		switch(funct7){
		    case 1:
			instruction = "DIV r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "DIV";
                    break;
		    case 0:
			instruction = "XOR r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "XOR";
                    break;
			}
	case 5:
		switch(funct7){
		    case 1:
			instruction = "OR r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "OR";
                    break;
		    case 0:
			instruction = "REM r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "REM";
                    break;
			}
	case 7:
		switch(funct7){
		    case 1:
			instruction = "AND r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "AND";
                    break;
		    case 0:
			instruction = "REMU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "REMU";
                    break;
			}
	
	case 6:
		switch(funct7){
		    case 1:
			instruction = "SRL r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "SRL";
                    break;
		    case 0:
			instruction = "DIVU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "DIVU";
                    break;
		    case 0b0100000:
			instruction = "SRA r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "SRA";
                    break;
			}
	break;
	default :
		cout<<"Error"<<endl;
}


    printControlLines("R-Type", instruction, controls);
   
}
void decodeRType_Word(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    controls[ALU_OP] = 1;
    controls[REG_DEST] = 1;
    controls[REG_WRITE] = 1;

    uint8_t funct3 = getfun3( input);
    uint8_t funct7 = getfun7(input);
    uint8_t rd = getrd(input);
    uint8_t rs1 =getrs1(input);
    uint8_t rs2 =  getrs2(input);
    string RISC_V;
    string instruction;
    uint16_t imm =0;
    switch (funct3) {
        case 0:
            switch (funct7) {
                case 0:
                    instruction = "ADDW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "ADDW";
                    break;
                case 32:
                    instruction = "SUBW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SUBW";
                    break;
                case 1:
                    instruction = "MULW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "MULW";
                    break;
            }
            break;
       case 1:
            
               switch(funct7){
                   
                case 0:
                    instruction = "SLLW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SLLW";
                    break;
                
   		}
	
	case 4:
		switch(funct7){
		    case 1:
			instruction = "DIVW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "DIVW";
            break;
			}
	case 5:
		switch(funct7){
		    case 0:
			instruction = "SRLW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "SRLW";
            break;
		    case 1:
			instruction = "DIVUW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "DIVUW";        
            break;
		    case 32:
			instruction = "SRAW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "SRAW";
            break;

			}
	case 6:
		switch(funct7){
		    case 1:
			instruction = "REMW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "REMW";
            break;
			}
	
	case 7:
		switch(funct7){
		    case 1:
			instruction = "REMUW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "REMUW";
            break;
		   
			}
	break;
	default :
		cout<<"Error"<<endl;
}


    printControlLines("R-Type", instruction, controls);
   
}
void decodeIType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t opcode = getOpcode(input);
    uint8_t funct3 = getfun3(input);
    uint8_t funct7 = getfun7(input);
    uint8_t rd = getrd(input);
    uint8_t rs1 = getrs1(input);
    int16_t imm = getimm11_0(input);  // signed immediate
    string RISC_V;
    string instruction;
    controls[ALU_OP] = 1;
    controls[REG_WRITE] = 1;
    controls[REG_DEST] = 1;
    uint8_t rs2 =0;
    if (opcode == 19) {  // I-type ALU
        controls[ALU_SRC] = 1;
        switch (funct3) {
            case 0:
                instruction = "ADDI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ADDI";
                break;
	
            case 2:
                instruction = "SLTI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "SLTI";
                break;
            case 3:
                instruction = "SLTIU r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "SLTIU";
                break;
            case 4:
                instruction = "XORI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "XORI";
                break;
            case 6:
                instruction = "ORI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ORI";
                break;
            case 7:
                instruction = "ANDI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ANDI";
                break;
            case 1:
                instruction = "SLLI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "SLLI";
                break;
            case 5:
		switch(funct7){
			case 0:
                		instruction = "SRLI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRLI";
                		break;
			case 32:
                		instruction = "SRAI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRAI";
                		break;
			}
	     default :
		cout<<"Error"<<endl;
}
        printControlLines("I-Type", instruction, controls);
       
    }
else if (opcode == 27) { 
        controls[ALU_SRC] = 1;
        switch (funct3) {
            case 0:
                instruction = "ADDIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ADDIW";
                break;
	
            case 1:
		switch(funct7){
			case 0:
                		instruction = "SLLIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SLLIW";
                		break;}
            
            case 5:
		switch(funct7){
			case 0:
                		instruction = "SRLIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRLIW";
                		break;
			case 32:
                		instruction = "SRAIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRAWIW";
                		break;
			}
	     default :
		cout<<"Error"<<endl;
		printControlLines("I-Type", instruction, controls);
	
}
}
else if (opcode == 3) {  // Load instructions
	 controls[ALU_OP] = 1;
	controls[MEM_READ] = 1;
        controls[ALU_SRC] = 1;
        switch (funct3) {
            case 0:
                instruction = "LB r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LB";
                break;
             case 1:
                instruction = "LH r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LH";
                break; 
             case 2:
                instruction = "LW r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LW";
                break;           
             case 4:
                instruction = "LBU r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LBU";
                break;           
             case 5:
                instruction = "LHU r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LHU";
                break;           
	     default :
		cout<<"Error"<<endl;         

}
 printControlLines("I-Type", instruction, controls);
 
}}
void decodeSType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t funct3 = getfun3(input);
    uint8_t rs1 = getrs1(input);
    uint8_t rs2 =  getrs2(input);
    uint8_t rd =0;
    // Constructing the 12-bit signed immediate for S-type
    uint16_t imm = getimm11_0(input);
    string RISC_V;
    string instruction;
    controls[ALU_OP] = 1;
    controls[MEM_WRITE] = 1;  // Set for all store instructions
    controls[ALU_SRC] = 1;   // To compute effective address

    switch (funct3) {
        case 0:
            instruction = "SB r" + to_string(rs2) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            RISC_V = "SB";
            break;
        case 1:
            instruction = "SH r" + to_string(rs2) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            RISC_V = "SH";
            break;
        case 2:
            instruction = "SW r" + to_string(rs2) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            RISC_V = "SW";
            break;
        
    }

    printControlLines("S-Type", instruction, controls);
    
}
void decodeSBType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    
    uint8_t funct3 = getfun3( input);
    uint8_t rs1 = getrs1(input);
    uint8_t rs2 =  getrs2(input);
    uint16_t imm =0;
    uint8_t rd =0;
    controls[ALU_OP] = 1;  // Assuming ALU_OP = 1 signifies branch comparison
    controls[BRANCH] = 1; // Set the control signal for branching
    string RISC_V;
    string instruction;

    switch (funct3) {
        case 1:
            instruction = "BEQ r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BEQ";
            break;
        case 2:
            instruction = "BNE r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BNE";
            break;
        case 4:
            instruction = "BLT r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BLT";
            break;
        case 5:
            instruction = "BGE r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BGE";
            break;
        case 6:
            instruction = "BLTU r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BLTU";
            break;
        case 7:
            instruction = "BGEU r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BGEU";
            break;
	default:
		cout<<"Error"<<endl;
    }

    printControlLines("SB-Type", instruction, controls);
   
    
}
void decodeUJType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    uint8_t rd = getrd(input);
    uint8_t rs1 = getrs1(input);
    uint8_t rs2 =0;
    string RISC_V;
    string instruction;
    uint16_t imm =0;
    uint32_t opcode = getOpcode(input);
    if(opcode == 103) {
        uint32_t funct3 = getfun3(input);
        if(funct3 == 0) {
            instruction = "JALR r" + to_string(rd) + ", r" + to_string(rs1) + ", imm";
            RISC_V = "JALR";
            controls[ALU_OP] = 1;
            controls[ALU_SRC] = 1;
            controls[REG_WRITE] = 1;
            controls[JUMP] = 1;
        }
        printControlLines("UJ-Type", instruction, controls);
        
    } else if(opcode == 111) {
        instruction = "JAL r" + to_string(rd) + ", imm";
        RISC_V = "JAL";
        controls[ALU_SRC] = 1;
        controls[REG_WRITE] = 1;
        controls[JUMP] = 1;
    }

    printControlLines("UJ-Type", instruction, controls);
   
}
void decodeUType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    uint8_t rd = getrd(input);
    uint8_t funct3 = getfun3(input);
    uint8_t rs1 =0, rs2 =0;
    string RISC_V;
    string instruction;
    uint32_t opcode = getOpcode(input);

    if(opcode == 55 && funct3 == 0) {
        instruction = "LUI r" + to_string(rd) + ", imm";
        RISC_V = "LUI";
        controls[REG_DEST] = 1;
        controls[REG_WRITE] = 1;
        printControlLines("U-Type", instruction, controls);
        
    } else if(opcode == 23 && funct3 == 0) {
        instruction = "AUIPC r" + to_string(rd) + ", imm";
        RISC_V = "AUIPC";
        controls[ALU_OP] = 1;
        controls[ALU_SRC] = 1;
        controls[REG_DEST] = 1;
        controls[REG_WRITE] = 1;
    }

    printControlLines("U-Type", instruction, controls);
 
}
void decodeFRType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    uint8_t opcode = getOpcode(input);
    uint8_t funct7 = getfun7(input);
    uint8_t rd = getrd(input);
    uint8_t rs1 = getrs1(input);
    uint8_t rs2 =  getrs2(input);
    uint16_t imm =0;
    string RISC_V;    
    string instruction;
    if (opcode == 83) { // Floating-point operations
        switch (funct7) {
            case 0: // FADD.S
                instruction = "FADD.S f" + std::to_string(rd) + ", f" + std::to_string(rs1) + ", f" + std::to_string(rs2);
                RISC_V = "FADD";
                controls[FLOAT_ADD] = 1;
                controls[REG_WRITE] = 0;
                break;
            case 4: //FSUB.s
                instruction = "FSUB.S f" + std::to_string(rd) + ", f" + std::to_string(rs1) + ", f" + std::to_string(rs2);
                RISC_V = "FSUB";
                controls[FLOAT_SUB] = 1;
                controls[REG_WRITE] = 0;
                break;
        }
                
    }
    printControlLines("FR-Type", instruction, controls);
  
}
void decodeFSType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t opcode = getOpcode(input);
    uint8_t funct3 = getfun3(input);
    uint8_t rs1 = getrs1(input);
    uint8_t rs2 = getrs2(input);
    uint16_t imm = (uint16_t)getimm11_0(input); // S-Type immediate
    // Sign extension
    int8_t rd =0;
    string RISC_V;
    string instruction;
   if (opcode == 39) { 
        switch (funct3) { 
            case 2: 
                instruction = "FSW f" + std::to_string(rs2) + ", " + std::to_string(imm) + "(r" + std::to_string(rs1) + ")";
                RISC_V = "FSW";
                controls[F_MEM_WRITE] = 1;
                controls[ALU_SRC] = 1;   
                controls[MEM_TO_REG] = 0;  
                controls[REG_WRITE] = 0;  
                break;
           
        }
    }
   printControlLines("FS-Type", instruction, controls);
 
}
void decodeFIType(const std::string& input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t opcode = getOpcode(input);
    uint8_t funct3 = getfun3(input);
    uint8_t rd = getrd(input);
    uint8_t rs1 = getrs1(input);
    uint16_t imm = getimm11_0(input); // I-Type immediate (sign-extended)
    uint8_t rs2 =0;
    string RISC_V;
    string instruction;
    if (opcode == 7) {
    switch(funct3){
        case 2 :
            instruction = "FLW f" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            controls[MEM_READ] = 1;
            controls[ALU_SRC] = 1;
            controls[F_REG_WRITE] = 1;
            RISC_V = "FLW";
            break;
    }
}
   printControlLines("FI-Type", instruction, controls);
   
}


