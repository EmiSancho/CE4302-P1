#include <iostream>
#include <bitset>
#include <vector>


class instrucctionMemory {
private:
    std::string memory[8] = {"000000000000"};

public:
    instrucctionMemory() {}

    // Loads a given program into memory
    void loadProgram(const std::vector<std::string>& program) {
        for (int i = 0;  i < program.size(); ++i) {
            memory[i] = program[i];
        }
    }

    // Return the instruction at memory[pc]
    std::string getInstruction(int pc) {
        if (pc >= 0 && pc < 8) {
            return memory[pc];
        } else {
            std::cerr << "Error: Invalid program counter." << std::endl;
            return "0";
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


