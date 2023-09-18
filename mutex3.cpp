#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

std::mutex mtx;
std::queue<int> modificationRequests;
std::condition_variable cv;

int sharedVariable = 0;

void ModifyVariable(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        // Esperar hasta que haya una solicitud en la cola
        cv.wait(lock, []{ return !modificationRequests.empty(); });

        // Procesar la solicitud
        // Obtiene el primer elemento de la cola
        int request = modificationRequests.front();
        modificationRequests.pop();

        // Realizar la modificación en la variable compartida
        sharedVariable += request;

        std::cout << "Thread " << id << " modifica la variable a " << sharedVariable << std::endl;

        // Simulamos un tiempo de procesamiento
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        lock.unlock();
    }
}

int main() {
    // Crear tres hilos
    std::thread thread1(ModifyVariable, 1);
    std::thread thread2(ModifyVariable, 2);
    std::thread thread3(ModifyVariable, 3);

    // Simular 10 solicitudes y ponerlas en la cola
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        int request = i + 1;

        std::unique_lock<std::mutex> lock(mtx);
        modificationRequests.push(request);
        lock.unlock();

        // Notificar a un hilo para que procese la solicitud
        cv.notify_one();
    }

    // Esperar a que los hilos terminen
    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}