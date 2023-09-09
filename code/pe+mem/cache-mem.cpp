#include <iostream>
#include <bitset>

class Cache {
private:
    uint16_t memory[8] = {0};

public:
    
    Cache() {}

    // Loads a given program into memory
    void loadProgram(uint16_t program[8]) {
        for (int i = 0; i < 8; i++) {
            memory[i] = program[i];
        }
    }

    // Return the instruction at memory[pc]
    uint16_t getInstruction(int pc) {
        if (pc >= 0 && pc < 8) {
            return memory[pc];
        } else {
            std::cerr << "Error: Invalid program counter." << std::endl;
            return 0;
        }
    }

    // Prints memory's content
    void printMemory() {
        std::cout << "Memory Content:" << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << memory[i] << std::endl;
        }
    }
};


