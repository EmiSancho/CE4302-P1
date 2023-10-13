#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include "../package.h"
#include "../state_enum.cpp"
#include "../Protocolo/MESI.cpp"
#include "../Protocolo/MOESI.cpp"
#include "../logManagement.cpp"
#include "../mem/main_mem.cpp"
#include <chrono>

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
    Moesi moesi;

    RequestManager(){
    }

    void printRequestQueue(){
        std::cerr << "RequestQueue:" << std::endl;
        std::queue<Package>  q = requestQueue;
        while(!q.empty()){
            Package p = q.front();
            p.print();
            q.pop();
        }
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
        int max = 0;
        int wA = 0;
        int rA = 0;
        int i = 0;
        bool protocol = false;
        //if (existRequest()) {
        // Tiempo de inicio para medir el tiempo de ejecucion
        auto start = std::chrono::high_resolution_clock::now();

        while (existRequest()) {
        //while (max < 24) {
            Package packet = GetRequest();
            std::cerr << "ConsumerThread Executing"<< std::endl;
            
            // To avoid wrong address as string 
            std::string address = (packet.address < 10) ? "0" + std::to_string(packet.address) : std::to_string(packet.address);
            packet.print();

            switch(packet.protocol){
                case 1: // MESI
                    protocol = true;                                           
                    switch (packet.request)
                    {
                    case 1: // readMesi
                        std::cerr << "readMESI"<< std::endl;
                        
                        if(packet.processor_id == 1){
                            std::cerr << "result 1: "<< result<< std::endl;
                            //result = mesi.readMESI(1,std::to_string(packet.address));
                            result = mesi.readMESI(address, pe1, pe2, pe3);  
                        }
                        if(packet.processor_id == 2){
                            std::cerr << "result 2: "<< result<< std::endl;
                            //result = mesi.readMESI(2, std::to_string(packet.address));
                            result = mesi.readMESI(address, pe2, pe1, pe3);
                        }
                        if(packet.processor_id == 3){
                            std::cerr << "result 3: "<< result<< std::endl;
                            //result = mesi.readMESI(3, std::to_string(packet.address));
                            result = mesi.readMESI(address, pe3, pe1, pe2);
                        }
                        std::cerr << "result: "<< result<< std::endl;
                        //memory.print();
                        
                        break;
                    
                    case 2: //writeMesi
                        std::cerr << "writeMESI"<< std::endl;
                        if(packet.processor_id == 1){
                            mesi.writeMESI(address, packet.data, pe1, pe2, pe3);
                        }
                        if(packet.processor_id == 2){
                            mesi.writeMESI(address, packet.data, pe2, pe1, pe3);
                        }
                        if(packet.processor_id == 3){
                            mesi.writeMESI(address, packet.data, pe3, pe1, pe2);
                        }
                        //memory.print();
                        break;

                    case 3: // Increment
                        std::cerr << "Increment"<< std::endl;
                        if(packet.processor_id == 1){
                            mesi.incrementMESI(address, pe1, pe2, pe3);
                        }
                        if(packet.processor_id == 2){
                            mesi.incrementMESI(address, pe2, pe1, pe3);
                        }
                        if(packet.processor_id == 3){
                            mesi.incrementMESI(address, pe3, pe1, pe2);
                        }
                        //memory.print();
                        break;

                    default:
                        std::cout << "Invalid request choice." << std::endl;
                        break;
                    }   
                    break;

                case 2: //MOESI
                    protocol = false;
                    switch (packet.request){
                        case 1: // readMoesi
                            std::cerr << "readMOESI"<< std::endl;
                            
                            if(packet.processor_id == 1){
                                std::cerr << "result 1: "<< result<< std::endl;
                                //result = mesi.readMESI(1,address);
                                result = moesi.readMOESI(address, pe1, pe2, pe3);  
                            }
                            if(packet.processor_id == 2){
                                std::cerr << "result 2: "<< result<< std::endl;
                                //result = mesi.readMESI(2, std::to_string(packet.address));
                                result = moesi.readMOESI(address, pe2, pe1, pe3);
                            }
                            if(packet.processor_id == 3){
                                std::cerr << "result 3: "<< result<< std::endl;
                                //result = mesi.readMESI(3, std::to_string(packet.address));
                                result = moesi.readMOESI(address, pe3, pe1, pe2);
                            }
                            std::cerr << "result: "<< result<< std::endl;
                            //memory.print();
                            
                            break;
                        
                        case 2: //writeMoesi
                            std::cerr << "writeMESI"<< std::endl;
                            if(packet.processor_id == 1){
                                moesi.writeMOESI(address,packet.data, pe1, pe2, pe3);
                            }
                            if(packet.processor_id == 2){
                                moesi.writeMOESI(address, packet.data, pe2, pe1, pe3);
                            }
                            if(packet.processor_id == 3){
                                moesi.writeMOESI(address, packet.data, pe3, pe1, pe2);
                            }
                            //memory.print();
                            break;

                        case 3: // Increment moesi
                            std::cerr << "Increment"<< std::endl;
                            if(packet.processor_id == 1){
                                moesi.incrementMOESI(address, pe1, pe2, pe3);
                            }
                            if(packet.processor_id == 2){
                                moesi.incrementMOESI(address, pe2, pe1, pe3);
                            }
                            if(packet.processor_id == 3){
                                moesi.incrementMOESI(address, pe3, pe1, pe2);
                            }
                            //memory.print();
                            break;

                        default:
                            std::cout << "Invalid request choice." << std::endl;
                            break;
                    }   
                    break;

                default:
                    std::cout << "Invalid protocol choice." << std::endl;
                    break;
            }


            PEManager::getInstance().showCaches();
            memory.print();
            
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));
        max++; // DELETE ME 
        }
        if (protocol) {
            rA = mesi.returnReadAccessMemory();
            wA = mesi.returnWriteAccessMemory();
            i = mesi.returnInvalidations();
            log.logMessage("rA " + std::to_string(rA) + " | wA " + std::to_string(wA) + " | i " + std::to_string(i));
        } else {
            rA = moesi.returnReadAccessMemory();
            wA = moesi.returnWriteAccessMemory();
            i = moesi.returnInvalidations();
            log.logMessage("rA " + std::to_string(rA) + " | wA " + std::to_string(wA) + " | i " + std::to_string(i));
        }


        // Tiempo de finalizacion para medir el tiempo de ejecucion
        auto end = std::chrono::high_resolution_clock::now();

        // Calcula la duración del tiempo de ejecucion en nanosegundos
        std::chrono::duration<double> execution_time = end - start;

        // Convierte la duración a milisegundos
        double execution_time_milliseconds = execution_time.count() * 1000;

        // Se agrega al log para que se muestre en la interfaz
        log.logMessage("t " + std::to_string(execution_time_milliseconds));

        std::cout << "Tiempo de ejecucion: " << execution_time_milliseconds << " milisegundos." << std::endl;
        //memory.print();
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