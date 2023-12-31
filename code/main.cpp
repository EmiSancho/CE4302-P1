#include <iostream>
#include "./code/pe+mem/random-code-generator.cpp"
#include "./code/pe+mem/pe.cpp"
#include "busInterconnect.cpp"

int main() {
    const int PES = 3;

    // Generate random code
    generateRandomCode codeGenerator;
    std::vector<std::string> randomCodePE1 = codeGenerator.getRandomCode();

    //Populate the instruccionMemories 
    instrucctionMemory instMemPE1;
    instMemPE1.loadProgram(randomCodePE1);
    //instMemPE1.printMemory();

   
   //Initialize the PEs
    PE PE1(1, instMemPE1); 

    //Initializing busInterconnect 
    BusInterconnect bus;
    std::vector<std::thread> threads;

    // Thread per PE
    for (int i = 0; i < PES; ++i) {
        threads.emplace_back(PEThread, i, std::ref(bus), 5);
    }

    return 0;
}

