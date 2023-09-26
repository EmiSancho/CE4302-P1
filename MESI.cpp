#include <iostream>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
//#include "utils.hpp"

// Variable global modo para cuando es moesi o mesi
// Prueba 3 pe con hilos distintos con request

/*
1. Invalid (I):
Lectura (Read): Leer desde la memoria principal y traer a la caché en estado Exclusive (E) o Shared (S).
Escritura (Write): Escribir en la caché en estado Modified (M) y marcar el bloque como modificado.

2. Modified (M):
Lectura (Read): Utilizar el dato en caché.
Escritura (Write): Actualizar el dato en caché y mantener el estado como Modified (M).

3. Exclusive (E):
Lectura (Read): Utilizar el dato en caché.
Escritura (Write): Escribir en la caché y cambiar el estado a Modified (M).

4. Shared (S):
Lectura (Read): Utilizar el dato en caché.
Escritura (Write): Escribir en la caché y cambiar el estado a Modified (M) si no es una escritura en cascada.
*/

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

// Bus Interconnect
// Guardar un resumen total de transacciones en el bus en un log!!!!!!!!!
// Debo acceder a la caché no solo por línea sino también con processor_id??????????
class MESI {
private:

public:
    std::vector<CacheLine>& cache_lines;

    // Transacciones en el bus
    // Devolver dato, estado y dirección
    void ReadRequest(int processor_id, int address) {

        // Si devuelve true, verificar estado
                // Obtener cual entry tiene el address
                // Obtener estado entry
                    //Si esta en M, E, S entonces devuelvo el valor local

                    //Si esta en I, tengo que buscar el valor en las otras caches
                        //Alguna de las caches externas tiene que tener el address con estado M o E
                            //Si esta en estado E, paso los estados de las caches a S y tomo el dato de memoria
                            //Si esta en estado M, escribo en memoria en el address y luego paso los estados de las caches a S y tomo el dato de memoria
            // Si devuelve false
                //Verifico si la direccion existe en las caches externas
                    //Si existe, verifico el estado
                        //Si el estado esta en E
                            //Cambio el estado a S en ambas caches y leo el dato de memoria
                        //Si el estado enta en M
                            //Escribo en memoria en el address y luego paso los estados de ambas caches a S y tomo el dato de memoria
                        //Si el estado esta en S
                            //Leo el dato address directamente de memoria
                    //Si no existe, leo el dato de memoria y paso a estado E
                //Si la direccion no existe en las caches externas
                    // Leo el dato en memoria y paso al estado E

        CacheLine& line = cache_lines[address];

        switch (line.state) {
            case Modified:
                // Utilizar el dato en caché.


                break;
            case Exclusive:

                break;
            case Shared:

                break;
            case Invalid:
                // La línea de caché no está en la caché local del procesador
                break;
        }
}
    void WriteRequest(int processor_id, int address, int data) {

        CacheLine& line = cache_lines[address];

        switch (line.state) {
            case Modified:
                // El procesador ya tiene la línea en estado modificado,
                // simplemente actualiza los datos en la caché y marca la línea como modificada.
                line.data = data;
                line.state = Modified;
                break;
            case Exclusive:
                // El procesador ya tiene la línea en estado exclusivo,
                // simplemente actualiza los datos en la caché y marca la línea como modificada.
                line.data = data;
                line.state = Modified;
                break;
            case Shared:
                // El procesador ya tiene la línea en estado compartido,
                // invalida todas las copias en otras cachés y actualiza los datos en la caché local.
                for (auto& cache_line : cache_lines) {
                    if (cache_line.state == Shared) {
                        cache_line.state = Invalid;
                    }
                }
                line.data = data;
                line.state = Modified;
                break;
            case Invalid:
                // La línea de caché no está en la caché local del procesador
                break;
        }
}
    void BusResponse(int processor_id, int address, MESIState state, int data) {

        CacheLine& line = cache_lines[address];

        switch (state) {
            case Modified:

                break;
            case Exclusive:

                break;
            case Shared:

                break;
            case Invalid:

                break;
        }
    }
};

// Protocolo MESI para las caché de los PE restantes
class MESI2 {
    //Acceder al estado de las caché restantes
    //Debo saber el estado de la caché del PE seleccionado
    //CacheLine& line = cache_lines[address];

    private:

    public:
        std::vector<CacheLine>& cache_lines;

        // Transacciones en el bus
        // Devolver dato, estado y dirección
        void ChangeState(int processor_id, int address, MESIState state) {

            CacheLine& line = cache_lines[address];

            switch (line.state) {
                case Modified:

                    break;
                case Exclusive:

                    break;
                case Shared:

                    break;
                case Invalid:
                    // La línea de caché no está en la caché local del procesador
                    break;
            }

        }
};

int main() {

    std::thread thread1(ThreadFunction, 1);
    std::thread thread2(ThreadFunction, 2);
    std::thread thread3(ThreadFunction, 3);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    int processor_id = 0;
    int address = 42;
    //Bus bus;
    //bus.ReadRequest(processor_id, address);

    return 0;
}