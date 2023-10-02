// utils.hpp

#ifndef UTILS_HPP
#define UTILS_HPP

#pragma once

#include <string>

class MESI {
public:
    void WriteRequest(int processor_id, int address, int data);
    void ReadRequest(int processor_id, int address);
    void BusResponse(int processor_id, int address, int state, int data);
};
class LogManagement {
public:
    void agregarTexto(const std::string& texto);
};

#endif // UTILS_HPP