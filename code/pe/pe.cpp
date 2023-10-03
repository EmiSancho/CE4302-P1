#include <iostream>
#include "cache-mem.cpp"
#include "instrucctionMemory.cpp"

class PE{
private:
    int PC = 0;
    // generateRandomCode codeGenerator;
    //instrucctionMemory INSTRUCTION_MEMORY;

public:
    int processor_id;
    Cache CACHE;
    PE(int processor_id, instrucctionMemory instructionMemory) {
        this->processor_id = processor_id;
        CACHE.print();
    }

    void executeProgram(){
        int data = 1;
        for (int i = 0; i < 4; ++i) {
        //std::string instruction = INSTRUCTION_MEMORY.getInstruction(PC);
        
        //sents a mgs to the interconect (instr, addrs)
        //gets a response (estado, addrs, data)

        //CACHE.loadValue(StateEnum::Modified,instruction.substr(5), data);

        PC++;
        data++; 
        }
    CACHE.print();

    }
};

// Instr 0 / 0000 =  null
// Instr 1 / 0001 =  write 
// Instr 2 / 0010 =  read 
// Instr 3 / 0011 =  incr     