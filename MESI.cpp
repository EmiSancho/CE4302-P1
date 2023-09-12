#include <iostream>
#include <vector>

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

// Bus Interconnect
// Guardar un resumen total de transacciones en el bus en un log!!!!!!!!!
// Debo acceder a la caché no solo por línea sino también con processor_id??????????
class Bus {
public:
    std::vector<CacheLine>& cache_lines;

    // Transacciones en el bus

    // Devolver dato, estado y dirección
    void ReadRequest(int processor_id, int address) {

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
int main() {

    int processor_id = 0;
    int address = 42;
    Bus bus;
    bus.ReadRequest(processor_id, address);

    return 0;
}