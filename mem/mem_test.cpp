#include <iostream>
#include "main_mem.cpp"

int main() {

    MainMemory memory;
    std::string addrs;
    int data;
    int output;

    memory.print();

    addrs = "34";
    data = 7;
    memory.write(addrs, data);

    addrs = "1C";
    data = 3;
    memory.write(addrs, data);

    addrs = "28";
    data = 4;
    memory.write(addrs, data);

    memory.print();

    addrs = "34";
    output = memory.read(addrs);
    std::cout << output << std::endl;

    addrs = "14";
    output = memory.read(addrs);
    std::cout << output << std::endl;

    addrs = "24";
    output = memory.read(addrs);
    std::cout << output << std::endl;


    return 0;
}