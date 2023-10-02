#include "utils.hpp"
#include <fstream>
#include <iostream>

void LogManagement::agregarTexto(const std::string& texto) {
    std::ofstream archivo("log.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << texto << "\n";
        archivo.close();
        std::cout << "Texto agregado exitosamente.\n";
    } else {
        std::cerr << "No se pudo abrir el archivo.\n";
    }
}