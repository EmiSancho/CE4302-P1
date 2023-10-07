
#ifndef MEMORYENTRY_H
#define MEMORYENTRY_H

#include <iostream>

class MemoryEntry{
private: 
    std::string addrs;
    int data; 

public:
    // Constructor to initialize an Entry
    MemoryEntry(const std::string& addrs, const int data): addrs(addrs), data(data) {
    }

    void setAddrs(const std::string& newAddrs) {
        addrs = newAddrs;
    }

    void setData(const int newData) {
        data = newData;
    }

    std::string getAddrs() const {
        return addrs;
    }

    int getData() const {
        return data;
    }

    void print(){
        std::cout << "0x" <<addrs << " | " << data << std::endl;
    }
};

#endif 