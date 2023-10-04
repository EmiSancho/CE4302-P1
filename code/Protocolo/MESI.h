#pragma once

#include <string>
#include "../pe+mem/cache-mem.cpp"
#include "../mem/main_mem.cpp"
#include "../pe+mem/pe.cpp"

class Mesi {
private:
    
public:
    Mesi();
    int readMESI(int origen_id, std::string address, MainMemory memory, PE peLocal, PE peExternal1, PE peExternal2);
    void writeMESI(std::string address, int data, MainMemory memory, PE peLocal, PE peExternal1, PE peExternal2);
};