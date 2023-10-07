#ifndef PE_H
#define PE_H

#include <iostream>
#include "../mem/cache-mem.cpp"
#include "../mem/instrucction_mem.cpp"
#include "random-code-generator.cpp"
#include "../package.h"
#include "../logManagement.cpp"

class PE{
    private:
        logger& log = logger::getInstance();
        int PC = 0;
        generateRandomCode codeGenerator;
        instrucctionMemory INSTRUCTION_MEMORY;

    public:
        int processor_id;
        Cache CACHE;

        PE(int processor_id, instrucctionMemory& instructionMemory){
            this->processor_id = processor_id;
            INSTRUCTION_MEMORY = instructionMemory;
            // log.logMessage("PE" + std::to_string(processor_id) + " started");
            //CACHE.print(processor_id);
        }

        Package getNextInstruccion(bool nextInstr){
        Package temp(processor_id, 0, 0, 1);
        if(nextInstr){
            std::string instr = INSTRUCTION_MEMORY.getInstruction(PC);
            //std::cerr << "\nPE"<< processor_id << ", PC="<< PC << ", instr: " << instr << std::endl;
        
            temp.address = static_cast<int>((std::bitset<64>(instr.substr(4, 8)).to_ulong()));
            temp.request = static_cast<int>((std::bitset<64>(instr.substr(2, 2)).to_ulong()));
            PC++;
        }
        log.logMessage("PE" + std::to_string(processor_id) + " getNextInstruccion" + " | address " + std::to_string(temp.address) + " | request " + std::to_string(temp.request) );
        return temp;
        }
};

class PEManager {
private:
    PE* pe1;
    PE* pe2;
    PE* pe3;

    PEManager() : pe1(nullptr), pe2(nullptr), pe3(nullptr) {}

public:
    static PEManager& getInstance() {
        static PEManager instance;
        return instance;
    }

    void registerPE1(PE* pe) {
        pe1 = pe;
    }

    void registerPE2(PE* pe) {
        pe2 = pe;
    }

    void registerPE3(PE* pe) {
        pe3 = pe;
    }

    PE& getPE1() {
        if (pe1 == nullptr) {
            std::cerr << "PE1 is not registered." << std::endl;
            // Handle the case where PE1 is not registered (throw an exception or return a default PE)
        }
        return *pe1;
    }

    PE& getPE2() {
        if (pe2 == nullptr) {
            std::cerr << "PE2 is not registered." << std::endl;
            // Handle the case where PE2 is not registered (throw an exception or return a default PE)
        }
        return *pe2;
    }
    PE& getPE3() {
        if (pe3 == nullptr) {
            std::cerr << "PE3 is not registered." << std::endl;
            // Handle the case where PE2 is not registered (throw an exception or return a default PE)
        }
        return *pe3;
    }
};


#endif 


// Instr 0 / 0000 =  null
// Instr 1 / 0001 =  write 
// Instr 2 / 0010 =  read 
// Instr 3 / 0011 =  incr     