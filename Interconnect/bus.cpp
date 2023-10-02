#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include "utils.hpp"
//#include "MESI.cpp"

//Writeback policy!!!!!!!!!!!

// Variable global modo para cuando es moesi o mesi
// Prueba 3 pe con hilos distintos con request

// Estados MESI
enum MESIState {
    Modified,
    Exclusive,
    Shared,
    Invalid
};

class CacheLine {
public:
    int data;
    MESIState state;
    // Inicialización de una caché vacía
    CacheLine() : data(0), state(Invalid) {}
};

// Estructura para los requests de los PE
class RequestPacket {
public:
    int processor_id;
    int address;
    int request;
    int state;

    RequestPacket(int pid, int addr, int req, int st)
        : processor_id(pid), address(addr), request(req), state(st) {}
};

// Cola de solicitudes de los PE
class RequestManager {
private:
    std::queue<RequestPacket> requestQueue;
    std::mutex mutex;

public:
    void AddRequest(int processor_id, int address, int request, int state) {
        std::lock_guard<std::mutex> lock(mutex);
        RequestPacket packet(processor_id, address, request, state);
        requestQueue.push(packet);
    }

    bool GetRequest(RequestPacket& packet) {
        std::lock_guard<std::mutex> lock(mutex);
        if (requestQueue.empty()) {
            return false;
        }

        packet = requestQueue.front();
        requestQueue.pop();
        return true;
    }
};

void ProducerThread(RequestManager& requestManager, int processor_id, int address, int request, int state) {

    requestManager.AddRequest(processor_id, address, request, state);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void ConsumerThread(RequestManager& requestManager) {
    while (true) {
        RequestPacket* packet = new RequestPacket(-1, -1, -1, -1);

        if (requestManager.GetRequest(*packet)) {
            // Procesa el request
            std::cout << "Received: Processor ID " << packet->processor_id
                      << ", Address " << packet->address
                      << ", Request " << packet->request
                      << ", State " << packet->state << std::endl;
        }

        // Liberar memoria
        delete packet;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

    // Metodo de response cada vez que escribe o no y lee o no
    void ejecutarMetodos() {
        bool readExecuted = false;
        bool writeExecuted = false;

        try {
            readMESI();
            readExecuted = true;
        } catch (...) {
            readExecuted = false;
        }

        try {
            writeMESI();
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

int main() {

    RequestManager requestManager;

    /*
    std::thread thread1(ThreadFunction, 1);
    std::thread thread2(ThreadFunction, 2);
    std::thread thread3(ThreadFunction, 3);
    */

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    MESI mesi;
    MESI2 mesi2;
    int processor_id = 0;
    int address = 42;
    //Bus bus;
    //bus.ReadRequest(processor_id, address);

    return 0;
}