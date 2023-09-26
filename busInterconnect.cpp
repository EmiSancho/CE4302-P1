#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

class BusInterconnect {
private:
    std::mutex busMutex;

public:
    void SendData(int peId, int data) {
        std::lock_guard<std::mutex> lock(busMutex);
        std::cout << "PE " << peId << " sent data: " << data << std::endl;
    }

    int ReceiveData(int peId) {
        std::lock_guard<std::mutex> lock(busMutex);
        int receivedData = 100 * (peId + 1);  // Simulando datos recibidos
        std::cout << "PE " << peId << " received data: " << receivedData << std::endl;
        return receivedData;
    }
};

void PEThread(int peId, BusInterconnect& bus, int numIterations) {
    for (int i = 0; i < numIterations; ++i) {
        // Simular operaciones de lectura y escritura
        int data = i * (peId + 1);

        // Enviar datos al bus
        bus.SendData(peId, data);

        // Esperar un breve tiempo antes de recibir los datos
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Leer datos desde el bus
        int receivedData = bus.ReceiveData(peId);

        // Simular un tiempo de procesamiento entre operaciones
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    const int numPEs = 3;
    BusInterconnect bus;

    std::vector<std::thread> threads;

    // Iniciar un hilo para cada PE
    for (int i = 0; i < numPEs; ++i) {
        threads.emplace_back(PEThread, i, std::ref(bus), 5);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
