#ifndef MAINMEMORY_H
#define MAINMEMORY_H


#include <iostream>
#include "mem_entry.cpp"
#include "../logManagement.cpp"

class MainMemory{
private:
    logger& log = logger::getInstance();
    MemoryEntry e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16;

    MainMemory():
        e1("00",0), e2("04",0), e3("08",0), e4("12",0), e5("16",0), e6("20",0), e7("24",0), e8("28",0),
        e9("32",0), e10("36",0), e11("40",0), e12("44",0), e13("48",0), e14("52",0), e15("56",0), e16("60",0){
            //log.logMessage("Main Memory initialized");
    }
    
public:
    

    static MainMemory& getInstance() {
        static MainMemory instance; // Static instance created only once
        return instance;
    }


    void print(){
        std::cout << "Memory Content:" << std::endl;
        e1.print();
        e2.print();
        e3.print();
        e4.print();
        e5.print();
        e6.print();
        e7.print();
        e8.print();
        e9.print();
        e10.print();
        e11.print();
        e12.print();
        e13.print();
        e14.print();
        e15.print();
        e16.print();
    }

    int read(const std::string& addr){
        if (addr == "00"){
            log.logMemRead(addr, e1.getData());
            return e1.getData();
        }else if(addr == "04"){
            log.logMemRead(addr, e2.getData());
            return e2.getData();
        }else if(addr == "08"){
            log.logMemRead(addr, e3.getData());
            return e3.getData();
        }else if(addr == "12"){
            log.logMemRead(addr, e4.getData());
            return e4.getData();
        }else if(addr == "16"){
            log.logMemRead(addr, e5.getData());
            return e5.getData();
        }else if(addr == "20"){
            log.logMemRead(addr, e6.getData());
            return e6.getData();
        }else if(addr == "24"){
            log.logMemRead(addr, e7.getData());
            return e7.getData();
        }else if(addr == "28"){
            log.logMemRead(addr, e8.getData());
            return e8.getData();
        }else if(addr == "32"){
            log.logMemRead(addr, e9.getData());
            return e9.getData();
        }else if(addr == "36"){
            log.logMemRead(addr, e10.getData());
            return e10.getData();
        }else if(addr == "40"){
            log.logMemRead(addr, e11.getData());
            return e11.getData();
        }else if(addr == "44"){
            log.logMemRead(addr, e12.getData());
            return e12.getData();
        }else if(addr == "48"){
            log.logMemRead(addr, e13.getData());
            return e13.getData();
        }else if(addr == "52"){
            log.logMemRead(addr, e14.getData());
            return e14.getData();
        }else if(addr == "56"){
            log.logMemRead(addr, e15.getData());
            return e15.getData();
        }else if(addr == "60"){
            log.logMemRead(addr, e16.getData());
            return e16.getData();
        }else{
            log.logMessage("Tried to read from memory");
            std::cout << "Invalid memory address." << std::endl;
            return -1;
        }
    }

    void write(const std::string& addr, int data) {
        log.logMemWrite(addr,data);
        if (addr == "00"){
            e1.setData(data);
        }else if(addr == "04"){
            e2.setData(data);
        }else if(addr == "08"){
            e3.setData(data);
        }else if(addr == "12"){
            e4.setData(data);
        }else if(addr == "16"){
            e5.setData(data);
        }else if(addr == "20"){
            e6.setData(data);
        }else if(addr == "24"){
            e7.setData(data);
        }else if(addr == "28"){
            e8.setData(data);
        }else if(addr == "32"){
            e9.setData(data);
        }else if(addr == "36"){
            e10.setData(data);
        }else if(addr == "40"){
            e11.setData(data);
        }else if(addr == "44"){
            e12.setData(data);
        }else if(addr == "48"){
            e13.setData(data);
        }else if(addr == "52"){
            e14.setData(data);
        }else if(addr == "56"){
            e15.setData(data);
        }else if(addr == "60"){
            e16.setData(data);
        }else{
            log.logMessage("Tried to write to memory");
            std::cout << "Invalid memory address." << std::endl;
        }
    }

};


#endif 