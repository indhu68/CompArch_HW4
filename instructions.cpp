

#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include "instructions.h"
#include<tuple>
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
         << "Float ALU OP : " << controls[F_ALU_OP] << "\n"
         << "Float Reg Write : " << controls[F_REG_WRITE] << "\n"
         << "Float Mem Write : " << controls[F_MEM_WRITE] << "\n"
         << "Memory to register : " << controls[MEM_TO_REG] << "\n\n";
         
    //return std::make_tuple(RISC_V_inst, dest, src1, src2);   
}

tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeRType(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    controls[ALU_OP] = 1;
    controls[REG_DEST] = 1;
    controls[REG_WRITE] = 1;

    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t funct7 = (input >> 25) & 0x7F;
    uint8_t rd = (uint8_t)((input >> 7) & 0x1F);
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    uint8_t rs2 = (uint8_t)((input >> 20) & 0x1F);
    string RISC_V;
    uint16_t imm =0;
    string instruction;
    
    switch (funct3) {
        case 0b000:
            switch (funct7) {
                case 0b0000000:
                    instruction = "ADD r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "ADD";
                    break;
                case 0b0100000:
                    instruction = "SUB r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SUB";
                    break;
                case 0b0000001:
                    instruction = "MUL r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "MUL";
                    break;
            }
            break;
       case 0b001:
            
               switch(funct7){
                   case 0b0000001:
			instruction = "MULH r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    break;
                case 0b0000000:
                    instruction = "SLL r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SLL";
                    break;
                
   		}
	case 0b010:
		switch(funct7){
		    case 0b0000001:
			instruction = "MULHSU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "MULHSU";
                    break;
		    case 0b0000000:
			instruction = "SLT r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "SLT";
                    break;
		    }
	case 0b011:
		switch(funct7){
		    case 0b0000001:
			instruction = "MULHSU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "MULHSU";
                    break;
		    case 0b0000000:
			instruction = "SLTU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "SLTU";
                    break;
			}
	case 0b100:
		switch(funct7){
		    case 0b0000001:
			instruction = "DIV r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "DIV";
                    break;
		    case 0b0000000:
			instruction = "XOR r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "XOR";
                    break;
			}
	case 0b110:
		switch(funct7){
		    case 0b0000001:
			instruction = "OR r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "OR";
                    break;
		    case 0b0000000:
			instruction = "REM r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "REM";
                    break;
			}
	case 0b111:
		switch(funct7){
		    case 0b0000001:
			instruction = "AND r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "AND";
                    break;
		    case 0b0000000:
			instruction = "REMU r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "REMU";
                    break;
			}
	
	case 0b101:
		switch(funct7){
		    case 0b0000001:
			instruction = "SRL r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
			RISC_V = "SRL";
                    break;
		    case 0b0000000:
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
    return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
   
}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeRType_Word(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    controls[ALU_OP] = 1;
    controls[REG_DEST] = 1;
    controls[REG_WRITE] = 1;

    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t funct7 = (input >> 25) & 0x7F;
    uint8_t rd = (uint8_t)((input >> 7) & 0x1F);
    uint8_t rs1 =(uint8_t)( (input >> 15) & 0x1F);
    uint8_t rs2 = (uint8_t)((input >> 20) & 0x1F);
    string RISC_V;
    string instruction;
    uint16_t imm =0;
    switch (funct3) {
        case 0b000:
            switch (funct7) {
                case 0b0000000:
                    instruction = "ADDW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "ADDW";
                    break;
                case 0b0100000:
                    instruction = "SUBW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SUBW";
                    break;
                case 0b0000001:
                    instruction = "MULW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "MULW";
                    break;
            }
            break;
       case 0b001:
            
               switch(funct7){
                   
                case 0b0000000:
                    instruction = "SLLW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
                    RISC_V = "SLLW";
                    break;
                
   		}
	
	case 0b100:
		switch(funct7){
		    case 0b0000001:
			instruction = "DIVW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "DIVW";
            break;
			}
	case 0b101:
		switch(funct7){
		    case 0b0000000:
			instruction = "SRLW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "SRLW";
            break;
		    case 0b0000001:
			instruction = "DIVUW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "DIVUW";        
            break;
		    case 0b0100000:
			instruction = "SRAW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "SRAW";
            break;

			}
	case 0b110:
		switch(funct7){
		    case 0b0000001:
			instruction = "REMW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "REMW";
            break;
			}
	
	case 0b111:
		switch(funct7){
		    case 0b0000001:
			instruction = "REMUW r" + to_string(rd) + " r" + to_string(rs1) + " r" + to_string(rs2);
            RISC_V = "REMUW";
            break;
		   
			}
	break;
	default :
		cout<<"Error"<<endl;
}


    printControlLines("R-Type", instruction, controls);
    return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
   
}
tuple<std::string, uint8_t, uint8_t, uint8_t,uint16_t> decodeIType(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t opcode = input & 0x7F;
    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t funct7 = (input >> 25) & 0x7F;
    uint8_t rd = (uint8_t)((input >> 7) & 0x1F);
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    int16_t imm = static_cast<uint16_t>(input) >> 20;  // signed immediate
    string RISC_V;
    string instruction;
    controls[ALU_OP] = 1;
    controls[REG_WRITE] = 1;
    controls[REG_DEST] = 1;
    uint8_t rs2 =0;
    if (opcode == 0b0010011) {  // I-type ALU
        controls[ALU_SRC] = 1;
        switch (funct3) {
            case 0b000:
                instruction = "ADDI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ADDI";
                break;
	
            case 0b010:
                instruction = "SLTI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "SLTI";
                break;
            case 0b011:
                instruction = "SLTIU r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "SLTIU";
                break;
            case 0b100:
                instruction = "XORI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "XORI";
                break;
            case 0b110:
                instruction = "ORI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ORI";
                break;
            case 0b111:
                instruction = "ANDI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ANDI";
                break;
            case 0b001:
                instruction = "SLLI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "SLLI";
                break;
            case 0b101:
		switch(funct7){
			case 0b0000000:
                		instruction = "SRLI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRLI";
                		break;
			case 0b0100000:
                		instruction = "SRAI r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRAI";
                		break;
			}
	     default :
		cout<<"Error"<<endl;
}
        printControlLines("I-Type", instruction, controls);
        return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
    }
else if (opcode == 0b0011011) { 
        controls[ALU_SRC] = 1;
        switch (funct3) {
            case 0b000:
                instruction = "ADDIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                RISC_V = "ADDIW";
                break;
	
            case 0b001:
		switch(funct7){
			case 0b0000000:
                		instruction = "SLLIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SLLIW";
                		break;}
            
            case 0b101:
		switch(funct7){
			case 0b0000000:
                		instruction = "SRLIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRLIW";
                		break;
			case 0b0100000:
                		instruction = "SRAIW r" + to_string(rd) + ", r" + to_string(rs1) + ", " + to_string(imm);
                		RISC_V = "SRAWIW";
                		break;
			}
	     default :
		cout<<"Error"<<endl;
		printControlLines("I-Type", instruction, controls);
		return std::make_tuple(RISC_V, rd, rs1,rs2, imm);
}
}
else if (opcode == 0b0000011) {  // Load instructions
	 controls[ALU_OP] = 1;
	controls[MEM_READ] = 1;
        controls[ALU_SRC] = 1;
        switch (funct3) {
            case 0b000:
                instruction = "LB r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LB";
                break;
             case 0b001:
                instruction = "LH r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LH";
                break; 
             case 0b010:
                instruction = "LW r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LW";
                break;           
             case 0b100:
                instruction = "LBU r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LBU";
                break;           
             case 0b101:
                instruction = "LHU r" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
                RISC_V = "LHU";
                break;           
	     default :
		cout<<"Error"<<endl;         

}
 printControlLines("I-Type", instruction, controls);
 return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
}}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeSType(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    uint8_t rs2 = (uint8_t)((input >> 20) & 0x1F);
    uint8_t rd =0;
    // Constructing the 12-bit signed immediate for S-type
    int16_t imm = ((input & 0xFE000000) >> 20) | ((input >> 7) & 0x1F);  // 12-bit signed immediate for S-type
    if (input & 0x80000000) {  // Sign extension
        imm |= 0xFFFFF000;
    }
    string RISC_V;
    string instruction;
    controls[ALU_OP] = 1;
    controls[MEM_WRITE] = 1;  // Set for all store instructions
    controls[ALU_SRC] = 1;   // To compute effective address

    switch (funct3) {
        case 0b000:
            instruction = "SB r" + to_string(rs2) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            RISC_V = "SB";
            break;
        case 0b001:
            instruction = "SH r" + to_string(rs2) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            RISC_V = "SH";
            break;
        case 0b010:
            instruction = "SW r" + to_string(rs2) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            RISC_V = "SW";
            break;
        
    }

    printControlLines("S-Type", instruction, controls);
    return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
    
}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeSBType(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    
    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    uint8_t rs2 = (uint8_t)((input >> 20) & 0x1F);
    uint16_t imm =0;
    uint8_t rd =0;
    controls[ALU_OP] = 1;  // Assuming ALU_OP = 1 signifies branch comparison
    controls[BRANCH] = 1; // Set the control signal for branching
    string RISC_V;
    string instruction;

    switch (funct3) {
        case 0b000:
            instruction = "BEQ r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BEQ";
            break;
        case 0b001:
            instruction = "BNE r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BNE";
            break;
        case 0b100:
            instruction = "BLT r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BLT";
            break;
        case 0b101:
            instruction = "BGE r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BGE";
            break;
        case 0b110:
            instruction = "BLTU r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BLTU";
            break;
        case 0b111:
            instruction = "BGEU r" + to_string(rs1) + ", r" + to_string(rs2);
            RISC_V = "BGEU";
            break;
	default:
		cout<<"Error"<<endl;
    }

    printControlLines("SB-Type", instruction, controls);
    return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
    
}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeUJType(uint32_t input, uint32_t opcode) {
    vector<bool> controls(NUM_CONTROLS, 0);
    uint8_t rd = (uint8_t)((input >> 7) & 0x1F);
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    uint8_t rs2 =0;
    string RISC_V;
    string instruction;
    uint16_t imm =0;
    if(opcode == 0b1100111) {
        uint32_t funct3 = (input >> 12) & 0x7;
        if(funct3 == 0b000) {
            instruction = "JALR r" + to_string(rd) + ", r" + to_string(rs1) + ", imm";
            RISC_V = "JALR";
            controls[ALU_OP] = 1;
            controls[ALU_SRC] = 1;
            controls[REG_WRITE] = 1;
            controls[JUMP] = 1;
        }
        printControlLines("UJ-Type", instruction, controls);
        return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
    } else if(opcode == 0b1101111) {
        instruction = "JAL r" + to_string(rd) + ", imm";
        RISC_V = "JAL";
        controls[ALU_SRC] = 1;
        controls[REG_WRITE] = 1;
        controls[JUMP] = 1;
    }

    printControlLines("UJ-Type", instruction, controls);
    return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeUType(uint32_t input, uint32_t opcode) {
    vector<bool> controls(NUM_CONTROLS, 0);
    uint8_t rd = (uint8_t)((input >> 7) & 0x1F);
    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t rs1 =0, rs2 =0;
    string RISC_V;
    string instruction;
    uint16_t imm =0;

    if(opcode == 0b0110111 && funct3 == 0b000) {
        instruction = "LUI r" + to_string(rd) + ", imm";
        RISC_V = "LUI";
        controls[REG_DEST] = 1;
        controls[REG_WRITE] = 1;
        printControlLines("U-Type", instruction, controls);
        return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
    } else if(opcode == 0b0010111 && funct3 == 0b000) {
        instruction = "AUIPC r" + to_string(rd) + ", imm";
        RISC_V = "AUIPC";
        controls[ALU_OP] = 1;
        controls[ALU_SRC] = 1;
        controls[REG_DEST] = 1;
        controls[REG_WRITE] = 1;
    }

    printControlLines("U-Type", instruction, controls);
    return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeFRType(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);
    uint32_t opcode = input & 0x7F;
    uint32_t funct7 = (input >> 25) & 0x7F;
    uint8_t rd = (uint8_t)((input >> 7) & 0x1F);
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    uint8_t rs2 = (uint8_t)((input >> 20) & 0x1F);
    uint16_t imm =0;
    string RISC_V;    
    string instruction;
    if (opcode == 0b1010011) { // Floating-point operations
        switch (funct7) {
            case 0b0000000: // FADD.S
                instruction = "FADD.S f" + std::to_string(rd) + ", f" + std::to_string(rs1) + ", f" + std::to_string(rs2);
                RISC_V = "FADD";
                controls[FLOAT_ADD] = 1;
                controls[REG_WRITE] = 1;
                break;}}
    printControlLines("FR-Type", instruction, controls);
    return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeFSType(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t opcode = input & 0x7F;
    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    uint8_t rs2 = (uint16_t)((input >> 20) & 0x1F);
    int16_t imm = (uint16_t)(((input >> 25) << 5) | ((input >> 7) & 0x1F)); // S-Type immediate
    imm = ((imm & 0x800) ? (0xFFFFF000 | imm) : imm); // Sign extension
    int8_t rd =0;
    string RISC_V;
    string instruction;
   if (opcode == 0b0100111) { 
        switch (funct3) { 
            case 0b010: 
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
   return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
}
tuple<std::string, uint8_t, uint8_t, uint8_t, uint16_t> decodeFIType(uint32_t input) {
    vector<bool> controls(NUM_CONTROLS, 0);

    uint8_t opcode = input & 0x7F;
    uint8_t funct3 = (input >> 12) & 0x7;
    uint8_t rd = (uint8_t)((input >> 7) & 0x1F);
    uint8_t rs1 = (uint8_t)((input >> 15) & 0x1F);
    int16_t imm = static_cast<int16_t>(input) >> 20; // I-Type immediate (sign-extended)
    int8_t rs2 =0;
    string RISC_V;
    string instruction;
    if (opcode == 0b0000111) {
    switch(funct3){
        case 0b010 :
            instruction = "FLW f" + to_string(rd) + ", " + to_string(imm) + "(r" + to_string(rs1) + ")";
            controls[MEM_READ] = 1;
            controls[ALU_SRC] = 1;
            controls[F_REG_WRITE] = 1;
            RISC_V = "FLW";
            break;
    }
}
   printControlLines("FI-Type", instruction, controls);
   return std::make_tuple(RISC_V, rd, rs1, rs2, imm);
   
}


