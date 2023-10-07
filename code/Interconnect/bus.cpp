#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include "../package.h"
#include "../mem/main_mem.cpp"
#include "../protocolo/MESI.cpp"

// #include "../state_enum.cpp"
// 
// #include "../logManagement.cpp"

// Cola de solicitudes de los PE
class RequestManager {
private:
    logger& log = logger::getInstance();
    PE& pe1 = PEManager::getInstance().getPE1();
    PE& pe2 = PEManager::getInstance().getPE2();
    PE& pe3 = PEManager::getInstance().getPE3();
    MainMemory& memory = MainMemory::getInstance(); //SINGLETON
    std::queue<Package>  requestQueue;
    std::mutex mutex;
    

public:
    Mesi mesi; 

    RequestManager(){
        
    }

    void AddRequest(Package& packet) {
        std::lock_guard<std::mutex> lock(mutex);
        requestQueue.push(packet);
        //std::cerr << "Packet Added" << std::endl;
        //packet.print();
        log.logPackage("AddRequest", packet);

    }

    Package GetRequest() {
        std::lock_guard<std::mutex> lock(mutex);
        Package packet = requestQueue.front();
        requestQueue.pop();
        return packet;
    }

    bool existRequest(){
        
        std::lock_guard<std::mutex> lock(mutex);
        if (requestQueue.empty()) {
            //std::cerr << "existRequest() NO"<< std::endl;
            return false;
        }
        //std::cerr << "existRequest() YES"<< std::endl;
        return true;
    }

    //void ConsumerThread(RequestManager& requestManager) {
    void ConsumerThread() {
        //std::cerr << "ConsumerThread Started"<< std::endl;
        // 1 readMesi 2 WriteMesi 
        
        int result = -1;

        if (existRequest()) {
        //while (existRequest()) {
            Package packet = GetRequest();
            packet.print();
            
            switch(packet.protocol){
                case 1: // MESI                                           
                    switch (packet.request)
                    {
                    case 1: // readMesi
                        std::cerr << "readMESI"<< std::endl;
                        
                        if(packet.processor_id == 1){
                            std::cerr << "result 1: "<< result<< std::endl;
                            //result = mesi.readMESI(1,std::to_string(packet.address));
                            result = mesi.readMESI(1,"04");
                           
                           
                        }
                        if(packet.processor_id == 2){
                            std::cerr << "result 2: "<< result<< std::endl;
                            //result = mesi.readMESI(2, std::to_string(packet.address));
                            result = mesi.readMESI(2,"08");
                        }
                        if(packet.processor_id == 3){
                            std::cerr << "result 3: "<< result<< std::endl;
                            //result = mesi.readMESI(3, std::to_string(packet.address));
                            result = mesi.readMESI(3,"12");
                        }
                        std::cerr << "result: "<< result<< std::endl;
                        memory.print();
                        
                        break;
                    
                    case 2: //writeMesi
                        std::cerr << "writeMESI"<< std::endl;
                        if(packet.processor_id == 1){
                            mesi.writeMESI(1, std::to_string(packet.address), 7);
                        }
                        if(packet.processor_id == 2){
                            mesi.writeMESI(2,std::to_string(packet.address), 8);
                        }
                        if(packet.processor_id == 3){
                            mesi.writeMESI(3,std::to_string(packet.address), 9);
                        }
                        memory.print();
                        break;

                    default:
                        std::cout << "Invalid request choice." << std::endl;
                        break;
                    }   
                    break; 

                // case 2: //MOESI
                //     break;

                default:
                    std::cout << "Invalid protocol choice." << std::endl;
                    break;
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        memory.print();
    }

};

    // Metodo de response cada vez que escribe o no y lee o no
    void ejecutarMetodos() {
        bool readExecuted = false;
        bool writeExecuted = false;

        try {
            //readMESI();
            readExecuted = true;
        } catch (...) {
            readExecuted = false;
        }

        try {
            //writeMESI();
            writeExecuted = true;
        } catch (...) {
            writeExecuted = false;
        }

        if (readExecuted) {
            std::cout << "Se hizo lectura" << std::endl;
        } else {
            std::cout << "No se pudo leer." << std::endl;
        }

        if (writeExecuted) {
            std::cout << "Se hizo una escritura." << std::endl;
        } else {
            std::cout << "No se pudo escribir." << std::endl;
        }
}

// int main() {

//     RequestManager requestManager;

//     /*
//     std::thread thread1(ThreadFunction, 1);
//     std::thread thread2(ThreadFunction, 2);
//     std::thread thread3(ThreadFunction, 3);
//     */

//     std::this_thread::sleep_for(std::chrono::milliseconds(50));
//     MESI mesi;
//     MESI2 mesi2;
//     int processor_id = 0;
//     int address = 42;
//     //Bus bus;
//     //bus.ReadRequest(processor_id, address);

//     return 0;
// }