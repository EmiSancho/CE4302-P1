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

//#include "MESI.cpp"

// Cola de solicitudes de los PE
class RequestManager {
private:
    std::queue<Package>  requestQueue;
    std::mutex mutex;

public:

    void AddRequest(Package& packet) {
        std::lock_guard<std::mutex> lock(mutex);
        requestQueue.push(packet);
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
            return false;
        }
        return true;
    }

    void ConsumerThread(RequestManager& requestManager) {
    
    //instancio MESI

    // dependiendo del request del paquete 
    // 1 readMesi 2 WriteMesi 
    
        while (existRequest()) {
            Package packet = GetRequest();
            switch(packet.protocol){
                case 1: // MESI
                    Mesi mesi; 
                    switch (packet.request)
                    {
                    case 1: // readMesi
                    
                        // instanciar la main memory en el main de forma global  
                        // PElocal el pe que hacer el request

                        mesi.readMESI();
                        break;
                    
                    case 2: //writeMesi
                        mesi.WriteRequest(packet.processor_id, packet.address, 7);
                        break;

                    default:
                        std::cout << "Invalid request choice." << std::endl;
                        break;
                    }   
                    break; 

                case 2: //MOESI
                    break;

                default:
                    std::cout << "Invalid protocol choice." << std::endl;
                    break;
            }

            

                
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
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