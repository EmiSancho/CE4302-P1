#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include "../utils.hpp"
#include "../package.h"
#include "../state_enum.cpp"

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

    bool GetRequest(Package& packet) {
        std::lock_guard<std::mutex> lock(mutex);
        if (requestQueue.empty()) {
            return false;
        }

        packet = requestQueue.front();
        requestQueue.pop();
        return true;
    }
};

void ProducerThread(RequestManager& requestManager, Package& packet) {

    requestManager.AddRequest(packet);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void ConsumerThread(RequestManager& requestManager) {
    while (true) {
    //    RequestPacket& packet;

    //     if (requestManager.GetRequest(packet)) {
    //         // Procesa el request
    //         // std::cout << "Received: Processor ID " << packet->processor_id
    //         //           << ", Address " << packet->address
    //         //           << ", Request " << packet->request
    //         //           << ", State " << packet->state << std::endl;
    //     }

        // // Liberar memoria
        // delete packet;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

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