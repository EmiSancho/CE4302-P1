#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include "../state_enum.cpp"
#include "../mem/cache-entry.cpp"
//#include "../logManagement.cpp"

class Cache{
private:
    //logger& log = logger::getInstance();
public:
    int processor_id;
    CacheEntry e1, e2, e3, e4;

    Cache()
        : e1(1,StateEnum::Invalid,"0",-1), e2(2, StateEnum::Invalid,"0",-1), e3(3, StateEnum::Invalid,"0",-1), e4(4, StateEnum::Invalid,"0",-1), processor_id (0){
    }

    void print(int id){
        std::cout << "PE "<< id << ", cache content:" << std::endl;
        e1.print();
        e2.print();
        e3.print();
        e4.print();
    }
    
    bool hasEmptyEntry() const {
        return (e1.isEmpty() || e2.isEmpty() || e3.isEmpty() || e4.isEmpty());
    }
    // const std::string& addr
    bool exists(const std::string addr) const {
        return (e1.exist(addr) || e2.exist(addr) || e3.exist(addr) || e4.exist(addr));
    }

    CacheEntry getEntry(std::string addr){
        if (exists(addr)){
            if (e1.getAddrs() == addr){
                return e1;
            }else if (e2.getAddrs() == addr){
                return e2;
            }else if (e3.getAddrs() == addr){
                return e3;
            }else if (e4.getAddrs() == addr){
                return e4;
            }else {
                std::cout << "Invalid address direction." << std::endl;
            }
        }
        return e1;  // Not a good practice
    }

    int getNextEmptyEntry(){
        if (e1.isEmpty()) {
            return (e1.getID());
        } else if (e2.isEmpty()) {
            return e2.getID();
        } else if (e3.isEmpty()) {
            return e3.getID();
        } else if (e4.isEmpty()) {
            return e4.getID();
        } else {
            return 0;
        }
    }
    // FIFO
    int replacementPolicy(){
        CacheEntry temp = CacheEntry(1,StateEnum::Invalid,"0",-1);
        updateValue(e1.getID(), e2.getStatus(), e2.getAddrs(), e2.getData());
        updateValue(e2.getID(), e3.getStatus(), e3.getAddrs(), e3.getData());
        updateValue(e3.getID(), e4.getStatus(), e4.getAddrs(), e4.getData());
        return e4.getID();       
    }

    // const std::string& addr
    void updateValue(int entryID, const StateEnum& status, const std::string addr, int data) {
        switch (entryID) {
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
                std::cout << "Invalid entry ID." << std::endl;
        }
        //log.logCacheUpdate(processor_id, );
    }
    // const std::string& addr
    void loadValue(const StateEnum& status, const std::string addr, int data) {
        int entryID = 0;
        //Verificar si existe un entry vacio
            //Si existe un entry vacio, hago el update a ese entry
            //Sino, debo buscar el entry mas antiguo
        if (hasEmptyEntry()){
            entryID = getNextEmptyEntry();
        }// Cache llena, se reemplaza un entry mediante FIFO para nueva entrada
        else{
            entryID = replacementPolicy();
        }
        updateValue(entryID, status, addr, data);
    }

};

#endif 