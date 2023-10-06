#include <iostream>
#include "mem_entry.cpp"


class MainMemory{
public:
    MemoryEntry e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16;

    MainMemory():
        e1("00",0), e2("04",0), e3("08",0), e4("12",0), e5("16",0), e6("20",0), e7("24",0), e8("28",0),
        e9("32",0), e10("36",0), e11("40",0), e12("44",0), e13("48",0), e14("52",0), e15("56",0), e16("60",0){
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
            return e1.getData();
        }else if(addr == "04"){
            return e2.getData();
        }else if(addr == "08"){
            return e3.getData();
        }else if(addr == "12"){
            return e4.getData();
        }else if(addr == "16"){
            return e5.getData();
        }else if(addr == "20"){
            return e6.getData();
        }else if(addr == "24"){
            return e7.getData();
        }else if(addr == "28"){
            return e8.getData();
        }else if(addr == "32"){
            return e9.getData();
        }else if(addr == "36"){
            return e10.getData();
        }else if(addr == "40"){
            return e11.getData();
        }else if(addr == "44"){
            return e12.getData();
        }else if(addr == "48"){
            return e13.getData();
        }else if(addr == "52"){
            return e14.getData();
        }else if(addr == "56"){
            return e15.getData();
        }else if(addr == "60"){
            return e16.getData();
        }else{
            std::cout << "Invalid memory address." << std::endl;
            return -1;
        }
    }

    void write(const std::string& addr, int data) {
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
            std::cout << "Invalid memory address." << std::endl;
        }
    }

};