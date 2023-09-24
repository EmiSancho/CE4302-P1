#include <iostream>
#include "../state_enum.cpp"
#include "cache_entry.cpp"

class Cache{
public:
    Entry e1, e2, e3, e4;

    Cache()
        : e1(StateEnum::Null,"0",0), e2(StateEnum::Null,"0",0), e3(StateEnum::Null,"0",0), e4(StateEnum::Null,"0",0) {
    }

    void print(){
        std::cout << "Cache Content:" << std::endl;
        e1.print();
        e2.print();
        e3.print();
        e4.print();
    }
    
    bool hasEmptyEntry() const {
        return (e1.isEmpty() || e2.isEmpty() || e3.isEmpty() || e4.isEmpty());
    }

    bool exists(const std::string& addr) const {
        return (e1.exist(addr) || e2.exist(addr) || e3.exist(addr) || e4.exist(addr));
    }

    int getNextEmptyEntry() const {
        if (e1.isEmpty()) {
            return 1;
        } else if (e2.isEmpty()) {
            return 2;
        } else if (e3.isEmpty()) {
            return 3;
        } else if (e4.isEmpty()) {
            return 4;
        } else {
            return 0; // No empty entry found
        }
    }

    void loadValue(int entryNumber, const StateEnum& status, const std::string& addr, int data) {
        switch (entryNumber) {
            case 1:
                e1.setStatus(status);
                e1.setAddrs(addr);
                e1.setData(data);
                break;
            case 2:
                e2.setStatus(status);
                e2.setAddrs(addr);
                e2.setData(data);
                break;
            case 3:
                e3.setStatus(status);
                e3.setAddrs(addr);
                e3.setData(data);
                break;
            case 4:
                e4.setStatus(status);
                e4.setAddrs(addr);
                e4.setData(data);
                break;
            default:
                std::cout << "Invalid entry number." << std::endl;
        }
    }

};