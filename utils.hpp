// utils.hpp

#ifndef UTILS_HPP
#define UTILS_HPP

class MESI {
public:
    void WriteRequest(int processor_id, int address, int data);
    void ReadRequest(int processor_id, int address);
    void BusResponse(int processor_id, int address, int state, int data);
};

class MESI2 {
public:
    void ChangeState(int processor_id, int address, int state);
};

#endif // UTILS_HPP