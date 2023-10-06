#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
//#include "../utils.hpp"
#include "../package.h"
#include "../state_enum.cpp"
#include "../protocolo/MESI.cpp"


// Cola de solicitudes de los PE
class RequestManager {
private:
    PE& pe1 = PEManager::getInstance().getPE1();
    PE& pe2 = PEManager::getInstance().getPE2();
    PE& pe3 = PEManager::getInstance().getPE3();
    MainMemory& memory = MainMemory::getInstance(); //SINGLETON
    std::queue<Package>  requestQueue;
    std::mutex mutex;

public:

    void AddRequest(Package& packet) {
        std::lock_guard<std::mutex> lock(mutex);
        requestQueue.push(packet);
        //std::cerr << "Packet Added" << std::endl;
        packet.print();
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
        Mesi mesi; // It has to be outside of the loop
        
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
                            mesi.readMESI(std::to_string(packet.address), memory, pe1,pe2,pe3);
                        }
                        if(packet.processor_id == 2){
                            mesi.readMESI(std::to_string(packet.address), memory, pe2,pe1,pe3);
                        }
                        if(packet.processor_id == 3){
                            mesi.readMESI(std::to_string(packet.address), memory, pe3,pe1,pe2);
                        }
                        break;
                    
                    case 2: //writeMesi
                        std::cerr << "writeMESI"<< std::endl;
                        if(packet.processor_id == 1){
                            mesi.writeMESI(std::to_string(packet.address), 7, memory, pe1,pe2,pe3);
                        }
                        if(packet.processor_id == 2){
                            mesi.writeMESI(std::to_string(packet.address), 8, memory, pe2,pe1,pe3);
                        }
                        if(packet.processor_id == 3){
                            mesi.writeMESI(std::to_string(packet.address), 9, memory, pe3,pe1,pe2);
                        }
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