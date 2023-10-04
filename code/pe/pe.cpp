#include <iostream>
#include "../mem/cache-mem.cpp"
#include "../mem/instrucction_mem.cpp"
#include "random-code-generator.cpp"
#include "../package.h"

class PE{
private:
    int PC = 0;
    generateRandomCode codeGenerator;
    instrucctionMemory INSTRUCTION_MEMORY;

public:
    int processor_id;
    Cache CACHE;
    PE(int processor_id, instrucctionMemory& instructionMemory){
        this->processor_id = processor_id;
        INSTRUCTION_MEMORY = instructionMemory;
        //CACHE.print(processor_id);
    }

    Package getNextInstruccion(bool nextInstr){
    Package temp(processor_id, 0, 0, 1);
       if(nextInstr){
        std::string instr = INSTRUCTION_MEMORY.getInstruction(PC);
        std::cerr << "\nPE"<< processor_id << ", PC="<< PC << ", instr: " << instr << std::endl;
      
        temp.address = static_cast<int>((std::bitset<64>(instr.substr(4, 8)).to_ulong()));
        temp.request = static_cast<int>((std::bitset<64>(instr.substr(2, 2)).to_ulong()));
        PC++;
       }
       return temp;
    }
};

// Instr 0 / 0000 =  null
// Instr 1 / 0001 =  write 
// Instr 2 / 0010 =  read 
// Instr 3 / 0011 =  incr     