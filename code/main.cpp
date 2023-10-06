#include <iostream>
#include "./pe/pe.cpp"
#include "./interconnect/bus.cpp"
#include <thread>


int main() {
    const int PES = 3;
    MainMemory& memory = MainMemory::getInstance(); //SINGLETON
    memory.write("04",4);
    //memory.print();

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
    // instMemPE2.printMemory(2);

    instrucctionMemory instMemPE3;
    instMemPE3.loadProgram(randomCodePE3);
    // instMemPE3.printMemory(3);

   //Initialize the PEs
    PEManager& peManager = PEManager::getInstance();
    PE PE1(1, instMemPE1); peManager.registerPE1(&PE1);
    PE PE2(2, instMemPE2); peManager.registerPE2(&PE2);
    PE PE3(3, instMemPE3); peManager.registerPE3(&PE3);

    int max = 2;
    memory.print();
    std::thread thread1([&PE1, max]() {
        RequestManager bus;
        bool p1_nextInstr = true;
        Package package1(0,0,0,0);
        for (int i = 0; i < max; ++i) {
            package1 = PE1.getNextInstruccion(p1_nextInstr);
            bus.AddRequest(package1);
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        }
        bus.ConsumerThread();
    });

    

    // std::thread thread2([&PE2, max]() {
    //     RequestManager bus;
    //     bool p1_nextInstr = true;
    //     Package package2(0,0,0,0);
    //     for (int i = 0; i < max; ++i) {
    //         package2 = PE2.getNextInstruccion(p1_nextInstr);
    //         bus.AddRequest(package2);
    //     }
    // });

    // std::thread thread3([&PE3, max]() {
    //     for (int i = 0; i < max; ++i) {
    //         PE3.executeProgram(true);
    //     }
    // });

    // // Join the threads to wait for them to complete
    thread1.join();
    //thread2.join();
    // thread3.join();

    //int max = 0;
    // Package package(0,0,0,0);
    // package = PE1.getNextInstruccion(p1_nextInstr);
    //package.print();
    
    // while (max < 2){
    //     package = PE1.getNextInstruccion(p1_nextInstr);
    //     package.print();
    //     //PE2.executeProgram(p1_nextInstr);
    //     max++; 
    // }
    
    //Initializing busInterconnect 
    //RequestManager bus;
    //std::vector<std::thread> threads;
    //bus.AddRequest(package);
    // Thread per PE
    // for (int i = 0; i < PES; ++i) {
    //     threads.emplace_back(PEThread, i, std::ref(bus), 5);
    // }

    return 0;
}

