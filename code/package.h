#ifndef PACKAGE_H
#define PACKAGE_H

// Class definition and other code go here
#include "state_enum.cpp"
#include <iostream>

class Package {
public:
    int processor_id;
    int address;
    int request;
    int protocol; // Protocol: 1 MESi, 2 MOESi

    Package(int pid, int addr, int req, int prt)
        : processor_id(pid), address(addr), request(req), protocol(prt) {}
    
    void print(){
        std::cerr << "PE id: " << processor_id << std::endl;
        std::cerr << "address: " << address << std::endl;
        std::cerr << "request: " << request << std::endl;
        std::cerr << "protocol: " << protocol << std::endl;
    };
};

#endif // PACKAGE_H
