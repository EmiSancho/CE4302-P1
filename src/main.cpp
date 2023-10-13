#include <iostream>
#include "./pe/pe.cpp"
#include "./Interconnect/bus.cpp"
#include <thread>
#include "logManagement.cpp"
#include "./pe/random-code-generator.cpp"

// g++ main.cpp -o main
// ./main


//int main(int argc, char* argv[]) {
int main() {
    //int protocole = std::stoi(argv[1]);
    int protocole = 1;
    logger& log = logger::getInstance(); // Create an instance of Logger
    const int PES = 3;
    MainMemory& memory = MainMemory::getInstance(); //SINGLETON
    // Generate random code
    generateRandomCode codeGenerator;
    std::vector<std::string> randomCodePE1 = codeGenerator.getRandomCode();
    std::vector<std::string> randomCodePE2 = codeGenerator.getRandomCode(); 
    std::vector<std::string> randomCodePE3 = codeGenerator.getRandomCode();
    


    //Populate the instruccionMemories 
    instrucctionMemory instMemPE1;
    instMemPE1.loadProgram(randomCodePE1);
    //instMemPE1.printMemory(1);

    instrucctionMemory instMemPE2;
    instMemPE2.loadProgram(randomCodePE2);
    //instMemPE2.printMemory(2);

    instrucctionMemory instMemPE3;
    instMemPE3.loadProgram(randomCodePE3);
    //instMemPE3.printMemory(3);

   //Initialize the PEs
    PEManager& peManager = PEManager::getInstance();
    PE PE1(1, instMemPE1); peManager.registerPE1(&PE1);
    PE PE2(2, instMemPE2); peManager.registerPE2(&PE2);
    PE PE3(3, instMemPE3); peManager.registerPE3(&PE3);

    int max = 8;

    RequestManager bus;

    std::thread thread1([&PE1, max, &bus,protocole]() {
        bool p1_nextInstr = true;
        Package package(0,0,0,protocole,0);
        for (int i = 0; i < max; ++i) {
            package = PE1.getNextInstruccion(p1_nextInstr);
            bus.AddRequest(package);
        }
    });
    
//     //bus.printRequestQueue();
     

    std::thread thread2([&PE2, max, &bus,protocole]() {
        bool p1_nextInstr = true;
        Package package2(0,0,0,protocole,0);
        for (int i = 0; i < max; ++i) {
            package2 = PE2.getNextInstruccion(p1_nextInstr);
            bus.AddRequest(package2);
        }
    });

    std::thread thread3([&PE3, max, &bus,protocole]() {
        bool p1_nextInstr = true;
        Package package3(0,0,0,protocole,0);
        for (int i = 0; i < max; ++i) {
            package3 = PE3.getNextInstruccion(p1_nextInstr);
            bus.AddRequest(package3);
        }
    });

    thread1.join();
    thread2.join();
    thread3.join();

    bus.printRequestQueue();
    
    bus.ConsumerThread();
    log.writeLog();
    
    return 0;
}

