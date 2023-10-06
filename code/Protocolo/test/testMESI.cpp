#define CATCH_CONFIG_MAIN  // Esto le dice a Catch proporcionar la función main

#include "../../catch.hpp"
#include "../MESI.cpp"

TEST_CASE("Mesi", "[Mesi]") {
    MainMemory& memory = MainMemory::getInstance(); //SINGLETON
    generateRandomCode codeGenerator;

    // Generate random code
    std::vector<std::string> randomCodePE1 = codeGenerator.getRandomCode();
    std::vector<std::string> randomCodePE2 = codeGenerator.getRandomCode(); 
    std::vector<std::string> randomCodePE3 = codeGenerator.getRandomCode();

    //Populate the instruccionMemories 
    instrucctionMemory instMemPE1;
    instMemPE1.loadProgram(randomCodePE1);
    //instMemPE1.printMemory(1);

    instrucctionMemory instMemPE2;
    instMemPE2.loadProgram(randomCodePE2);
    // instMemPE2.printMemory(2);

    instrucctionMemory instMemPE3;
    instMemPE3.loadProgram(randomCodePE3);
    // instMemPE3.printMemory(3);

    PEManager& peManager = PEManager::getInstance();
    PE pe1(1, instMemPE1); peManager.registerPE1(&pe1);
    PE pe2(2, instMemPE2); peManager.registerPE2(&pe2);
    PE pe3(3, instMemPE3); peManager.registerPE3(&pe3);

    Mesi mesi;

    pe1.CACHE.print(pe1.processor_id);
    
    SECTION("1. Test writeMESI with data 55 on address 00") {
        // peLocal escribe en la direccion 00 con valor 55
        pe1.CACHE.print(pe1.processor_id);
        pe2.CACHE.print(pe2.processor_id);
        pe3.CACHE.print(pe3.processor_id);
        printf("Soy un print: \n");
        mesi.writeMESI(pe1.processor_id, "04", 80);

        // Verificar que el dato en e1 es 55 y que el estado de la cache local es M
        REQUIRE(pe1.CACHE.e1.getData() == 60);
        printf("Estado de la cache local: %d\n", pe1.CACHE.e1.getStatus());
        REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Modified);
    }
    /*
    SECTION("2. Test readMESI with shared state on both external PE") {
        // Memory en direccion 00 con valor 55
        memory.write("00", 55);
        // peExternal 1 con entry 2 con direccion 00 en estado S
        peExternal1.CACHE.e2.setAddrs("00");
        peExternal1.CACHE.e2.setStatus(StateEnum::Shared);
        peExternal1.CACHE.e2.setData(55);
        // peExternal 2 con entry 2 con direccion 00 en estado S
        peExternal2.CACHE.e3.setAddrs("00");
        peExternal2.CACHE.e3.setStatus(StateEnum::Shared);
        peExternal2.CACHE.e3.setData(55);

        // peLocal lee en la misma direccion
        int result = mesi.readMESI("00", memory, peLocal, peExternal1, peExternal2);

        // Verificar que resultado es 55 y que el estado de la cache local es S
        REQUIRE(result == 55);
        REQUIRE(peLocal.CACHE.e1.getStatus() == StateEnum::Shared);
    }

    SECTION("3. Test writeMESI in P1 with all entrys already with data") {
        // Llenar los entrys de la cache local con datos
        peLocal.CACHE.loadValue(StateEnum::Shared, "00", 10);
        peLocal.CACHE.loadValue(StateEnum::Exclusive, "04", 20);
        peLocal.CACHE.loadValue(StateEnum::Modified, "08", 30);
        peLocal.CACHE.loadValue(StateEnum::Shared, "0C", 40);
        // Agregar otro dato y por politica FIFO se elimina el dato en e1
        peLocal.CACHE.loadValue(StateEnum::Exclusive, "10", 50);
        int result = mesi.readMESI("0C", memory, peLocal, peExternal1, peExternal2);
        int result2 = peLocal.CACHE.e1.getData();

        // Verificar que resultado es 50
        REQUIRE(result == 50);
        REQUIRE(result2 == 50);
    }

    SECTION("4. Test writeMESI in peExternal1 and the other have the data in Shared on address 00") {
        memory.write("00", 70);
        // Read the same value on peLocal and peExternal2
        mesi.readMESI("00", memory, peLocal, peExternal1, peExternal2);
        mesi.readMESI("00", memory, peExternal2, peExternal1, peLocal);

        // Write the data to peExternal1
        mesi.writeMESI("00", 80, memory, peExternal1, peLocal, peExternal2);

        // Verify that the data was written correctly and the state is Exclusive on peExternal1
        REQUIRE(peExternal1.CACHE.e1.getData() == 80);
        REQUIRE(peLocal.CACHE.e1.getStatus() == StateEnum::Invalid);
        REQUIRE(peExternal2.CACHE.e1.getStatus() == StateEnum::Invalid);
        REQUIRE(peExternal1.CACHE.e1.getStatus() == StateEnum::Exclusive);
}

    SECTION("7. Test readMESI in P1 with no data in cache", "[MESI]") {
        // Read the data from the local cache
        int result = mesi.readMESI("0C", memory, peLocal, peExternal1, peExternal2);

        // Verify that the result is -1 (invalid)
        REQUIRE(result == -1);
}

    SECTION("8. Test readMESI in P1 with data in cache", "[MESI]") {
        // Fill the local cache with data
        peLocal.CACHE.loadValue(StateEnum::Shared, "0C", 40);

        // Read the data from the local cache
        int result = mesi.readMESI("0C", memory, peLocal, peExternal1, peExternal2);

        // Verify that the result is 40 (data in cache)
        REQUIRE(result == 40);
    }*/

}