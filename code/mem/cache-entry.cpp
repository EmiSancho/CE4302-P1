#include <iostream>
#include "../state_enum.cpp"

class CacheEntry{
private: 
    int ID;
    StateEnum status;
    std::string addrs;
    int data; 

public:
    // Constructor to initialize an Entry
    CacheEntry(int ID, const StateEnum status, const std::string addrs, const int data)
        : ID(ID), status(status), addrs(addrs), data(data) {
    }   


    bool isEmpty() const { return (data == -1) ? true : false; }
    bool exist(std::string addr) const { return (addrs == addr) ? true : false; }

    void setStatus(const StateEnum newStatus) {
        status = newStatus;
    }

    void setAddrs(const std::string newAddrs) {
        addrs = newAddrs;
    }

    void setData(const int newData) {
        data = newData;
    }

    StateEnum getStatus() const {
        return status;
    }

    std::string getAddrs() const {
        return addrs;
    }

    int getData() const {
        return data;
    }

    int getID(){
        return ID;
    }

    void print(){
        std::cout <<  status << " | " << "0x" <<addrs << " | " << data << std::endl;
    }
};