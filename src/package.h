#ifndef PACKAGE_H
#define PACKAGE_H

// Class definition and other code go here
#include "state_enum.cpp"
#include <iostream>
#include <sstream>

class Package {
public:
    int processor_id;
    int address;
    int request;
    int protocol; // Protocol: 1 MESI, 2 MOESI

    Package(int pid, int addr, int req, int prt)
        : processor_id(pid), address(addr), request(req), protocol(prt) {}
    
    void print(){
        std::cerr << "PE id: " << processor_id << " | address: " << address << " | request: " << request << " | protocol: " << protocol << std::endl;
    };

    std::string toString() const{
        std::stringstream ss;
        ss << "PE" << processor_id << " | address: " << address << " | request: " << request << " | protocol: " << protocol << std::endl;
        return ss.str(); 
    }
};

#endif // PACKAGE_H
