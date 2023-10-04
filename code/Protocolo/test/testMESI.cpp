#define CATCH_CONFIG_MAIN  // Esto le dice a Catch proporcionar la función main

#include "../catch.hpp"
#include "../pe+mem/cache-mem.cpp"
#include "../mem/main_mem.cpp"
#include "../pe+mem/pe.cpp"
#include "../Protocolo/MESI.h"

TEST_CASE("Mesi", "[Mesi]") {
    Mesi mesi;
    MainMemory memory;
    PE peLocal(1);
    PE peExternal1(2);
    PE peExternal2(3);
    // Initialize peLocal, peExternal1, peExternal2, and memory as needed

    // Estructura de inputs de los metodos:
    // int readMESI(int origen_id, std::string address, MainMemory memory, PE peLocal, PE peExternal1, PE peExternal2);
    // void writeMESI(std::string address, int data, MainMemory memory, PE peLocal, PE peExternal1, PE peExternal2);

    SECTION("Test readMESI with shared state") {
        // Memory en direccion 00 con valor 55
        memory.write("00", 55);
        // peExternal 1 con entry 2 con direccion 00 en estado shared
        peExternal1.CACHE.e2.setAddrs("00");
        peExternal1.CACHE.e2.setStatus(1);
        peExternal1.CACHE.e2.setData(55);
        (0x1000, StateEnum::Shared);

        // Call the readMESI method with the shared block address
        int result = mesi.readMESI(0x1000, peLocal, peExternal1, peExternal2, memory);

        // Verify that the result is 0x55 and the state is still Shared
        REQUIRE(result == 0x55);
        REQUIRE(memory.GetState(0x1000) == StateEnum::Shared);
    }

    
    /*

    SECTION("Test readMESI with invalid address") {
        // Caso de address invalido
        int result = mesi.readMESI(0, peLocal, peExternal1, peExternal2, memory);
        // Verificar que resultado es -1
        REQUIRE(result == -1);
    }
    
    SECTION("Test readMESI with exclusive state") {
        // Set up an exclusive block in memory
        memory.Write(0x2000, 0xAA);
        memory.SetState(0x2000, StateEnum::Exclusive);

        // Call the readMESI method with the exclusive block address
        int result = mesi.readMESI(0x2000, peLocal, peExternal1, peExternal2, memory);

        // Verify that the result is 0xAA and the state is now Shared
        REQUIRE(result == 0xAA);
        REQUIRE(memory.GetState(0x2000) == StateEnum::Shared);
    }

    SECTION("Test writeMESI with invalid address") {
        // Call the writeMESI method with an invalid address
        mesi.writeMESI(0, 0, peLocal, peExternal1, peExternal2, memory);

        // Verify that the memory was not updated
        REQUIRE(memory.Read(0) == 0);
    }

    SECTION("Test writeMESI with shared state") {
        // Set up a shared block in memory
        memory.Write(0x3000, 0x11);
        memory.SetState(0x3000, StateEnum::Shared);

        // Call the writeMESI method with the shared block address
        mesi.writeMESI(0x3000, 0x22, peLocal, peExternal1, peExternal2, memory);

        // Verify that the memory was updated to 0x22 and the state is now Invalid
        REQUIRE(memory.Read(0x3000) == 0x22);
        REQUIRE(memory.GetState(0x3000) == StateEnum::Invalid);
    }

    SECTION("Test writeMESI with exclusive state") {
        // Set up an exclusive block in memory
        memory.Write(0x4000, 0x33);
        memory.SetState(0x4000, StateEnum::Exclusive);

        // Call the writeMESI method with the exclusive block address
        mesi.writeMESI(0x4000, 0x44, peLocal, peExternal1, peExternal2, memory);

        // Verify that the memory was updated to 0x44 and the state is still Exclusive
        REQUIRE(memory.Read(0x4000) == 0x44);
        REQUIRE(memory.GetState(0x4000) == StateEnum::Exclusive);
    }*/


}