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
    
    // SECTION("1. Escritura en la direccion 04 cuando la no existe ninguna cache") {
    //     std::cout << "Caso 1 \n" << std::endl;
    //     // peLocal escribe en la direccion 04 con valor 55
    //     mesi.writeMESI(pe1.processor_id, "04", 80);
    //     pe1.CACHE.print(pe1.processor_id);
    //     memory.print();
    //     // Verificar que el dato en e1 es 80 y que el estado de la cache es M
    //     REQUIRE(pe1.CACHE.e1.getData() == 80);
    //     REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Modified);
    // }

    // SECTION("2. Escritura en la direccion 04 cuando la direccion ya existe en mi cache y el estado es Modificado") {
    //     std::cout << "Caso 2 \n" << std::endl;
    //     // peLocal escribe en la direccion 04 con valor 80
    //     mesi.writeMESI(pe3.processor_id, "04", 74, pe3, pe1, pe2);
    //     pe3.CACHE.print();
    //     memory.print();
    //     mesi.writeMESI(pe3.processor_id, "04", 80, pe3, pe1, pe2);
    //     pe3.CACHE.print();
    //     // Verificar que el dato en e1 es 78 y que el estado de la cache es M
    //     REQUIRE(pe3.CACHE.e1.getData() == 80);
    //     REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Modified);
    // }

     SECTION("3. Escritura en la direccion 04 cuando la direccion ya existe en mi cache y el estado es Exclusivo") {
        std::cout << "Caso 3 \n" << std::endl;
        // peLocal escribe en la direccion 04 con valor 80
        mesi.writeMESI(pe3.processor_id, "04", 70, pe3, pe1, pe2);
        pe3.CACHE.print();
        mesi.writeMESI(pe2.processor_id, "04", 74, pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        mesi.writeMESI(pe3.processor_id, "04", 80, pe3, pe1, pe2);
        pe2.CACHE.print();
        pe3.CACHE.print();
        memory.print();
        // Verificar que el dato en e1 es 78 y que el estado de la cache es M
        REQUIRE(pe3.CACHE.e1.getData() == 80);
        REQUIRE(memory.read("04") == 80);
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Exclusive);
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Shared);
    }

    // SECTION("4. Escritura en la direccion 04 cuando la direccion existe en la cache local y el estado es Compartido") {
    //    std::cout << "Caso 4 \n" << std::endl;
    //     // peLocal escribe en la direccion 04 con valor 78
    //     mesi.writeMESI(pe3.processor_id, "04", 78, pe3, pe1, pe2);
    //     pe3.CACHE.print();
    //     mesi.readMESI(pe2.processor_id, "04", pe2, pe1, pe3);
    //     pe2.CACHE.print();
    //     memory.print();
    //     mesi.writeMESI(pe3.processor_id, "04", 66, pe3, pe1, pe2);
    //     pe3.CACHE.print();
    //     pe2.CACHE.print();
    //     memory.print();
    //     // Verificar que el dato del entry e1 del pe2 es 66
    //     REQUIRE(pe3.CACHE.e1.getData() == 66);
    //     // Verificar que el dato de memoria es 66
    //     REQUIRE(memory.read("04") == 66);
    //     // Verificar que el estado del entry e1 del pe3 es Exclusivo
    //     REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Exclusive);
    //     // Verificar que el estado del entry e1 del pe2 es invalido
    //     REQUIRE(pe2.CACHE.getEntry("04").getStatus() == StateEnum::Invalid);
    // }

   

    SECTION("5. Escritura en la direccion 04 cuando la direccion ya existe en mi cache y el estado es Invalido") {
        // peLocal escribe en la direccion 04 con valor 80
         std::cout << "Caso 5 \n" << std::endl;
        mesi.writeMESI(pe3.processor_id, "04", 70, pe3, pe1, pe2);
        pe3.CACHE.print();
        mesi.writeMESI(pe2.processor_id, "04", 74, pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        mesi.writeMESI(pe3.processor_id, "04", 80, pe3, pe1, pe2);
        pe2.CACHE.print();
        pe3.CACHE.print();
        memory.print();
        // Verificar que el dato en e1 es 78 y que el estado de la cache es M
        REQUIRE(pe3.CACHE.e1.getData() == 80);
        REQUIRE(memory.read("04") == 80);
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Exclusive);
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Shared);
    }

    // SECTION("6. Escritura en la direccion 04 cuando la direccion no existe en la cache local y si en una externa con estado Modificado") {
    //     std::cout << "Caso 6 \n" << std::endl;
    //     // peLocal escribe en la direccion 04 con valor 78
    //     mesi.writeMESI(pe3.processor_id, "04", 78, pe3, pe1, pe2);
    //     pe3.CACHE.print();
    //     mesi.writeMESI(pe2.processor_id, "04",95, pe2, pe1, pe3);
    //     pe2.CACHE.print();
    //     memory.print();
    //     // Verificar que el dato del entry e1 del pe2 es 95
    //     REQUIRE(pe2.CACHE.e1.getData() == 95);
    //     // Verificar que el dato de memoria es 66
    //     REQUIRE(memory.read("04") == 95);
    //     // Verificar que el estado del entry e1 del pe2 es exclusivo
    //     REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Exclusive);
    //     // Verificar que el estado del entry e1 del pe3 es invalido
    //     REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Invalid);
    // }
    //     SECTION("7. Escritura en la direccion 04 cuando la direccion no existe en la cache local y si en una externa con estado Exclusivo") {
    //     std::cout <<  "Caso 7 \n"<< std::endl;
    //     // peLocal escribe en la direccion 04 con valor 78
    //     mesi.writeMESI(pe3.processor_id, "04", 78, pe3, pe1, pe2);
    //     pe3.CACHE.print();
    //     mesi.writeMESI(pe2.processor_id, "04",95, pe2, pe1, pe3);
    //     pe2.CACHE.print();
    //     memory.print();
    //     mesi.writeMESI(pe1.processor_id, "04", 14, pe1, pe2, pe3);
    //     pe1.CACHE.print();
    //     memory.print();
    //     // Verificar que el dato del entry e1 del pe2 es 95
    //     REQUIRE(pe1.CACHE.e1.getData() == 14);
    //     // Verificar que el dato de memoria es 66
    //     REQUIRE(memory.read("04") == 14);
    //     // Verificar que el estado del entry e1 del pe2 es exclusivo
    //     REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Exclusive);
    //     // Verificar que el estado del entry e1 del pe2 es invalido
    //     REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Invalid);
    //     // Verificar que el estado del entry e1 del pe3 es invalido
    //     REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Invalid);
    // }

    SECTION("8. Escritura en la direccion 04 cuando la direccion no existe en la cache local y si en una externa con estado Compartido") {
        std::cout <<  "Caso 8 \n"<< std::endl;
        // peLocal escribe en la direccion 04 con valor 78
        mesi.writeMESI(pe1.processor_id, "04", 78, pe1, pe2, pe3);
        pe1.CACHE.print();
        mesi.readMESI(pe2.processor_id, "04", pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        mesi.writeMESI(pe3.processor_id, "04", 14, pe3, pe1, pe2);
        pe3.CACHE.print();
        memory.print();
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe3.CACHE.e1.getData() == 14);
        // Verificar que el dato de memoria es 66
        REQUIRE(memory.read("04") == 14);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Exclusive);
        // Verificar que el estado del entry e1 del pe2 es invalido
        REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Invalid);
        // Verificar que el estado del entry e1 del pe3 es invalido
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Invalid);
    }

        SECTION("9. Escritura en la direccion 04 cuando la direccion no existe en la cache local y la cache local esta llena") {
        std::cout <<  "Caso 9 \n"<< std::endl;
        // peLocal escribe en la direccion 04 con valor 78
        mesi.writeMESI(pe1.processor_id, "00", 10, pe1, pe2, pe3);
        mesi.writeMESI(pe1.processor_id, "04", 20, pe1, pe2, pe3);
        mesi.writeMESI(pe1.processor_id, "08", 30, pe1, pe2, pe3);
        mesi.writeMESI(pe1.processor_id, "12", 40, pe1, pe2, pe3);
        pe1.CACHE.print();

        mesi.writeMESI(pe1.processor_id, "16", 50, pe1, pe2, pe3);
        pe1.CACHE.print();
        memory.print();
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe3.CACHE.e1.getData() == 14);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Exclusive);
        // Verificar que el estado del entry e1 del pe2 es invalido
        REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Invalid);
        // Verificar que el estado del entry e1 del pe3 es invalido
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Invalid);
    }

    // Escritura en dirección cuando no existe en local, la caché local está llena 
    // y el entry por reemplazar estaba en estado S junto con caché externa.
    SECTION("10. Escritura en direccion 44 y no existe en la cache local, cache esta llena y direccion 44 esta en S con externo") {
        std::cout << "Caso 10 \n" << std::endl;
        // pe1 se llena de datos en los 4 entrys
        mesi.writeMESI(pe1.processor_id, "08", 10, pe1, pe2, pe3);
        mesi.writeMESI(pe1.processor_id, "20", 20, pe1, pe2, pe3);
        mesi.writeMESI(pe1.processor_id, "28", 30, pe1, pe2, pe3);
        mesi.writeMESI(pe1.processor_id, "04", 40, pe1, pe2, pe3);
        pe1.CACHE.print();
        // pe2 y pe1 tienen la direccion 
        mesi.readMESI(pe2.processor_id, "28", pe2, pe1, pe3);
        memory.print();
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe2.CACHE.e1.getData() == 95);
        // Verificar que el dato de memoria es 66
        REQUIRE(memory.read("04") == 95);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Exclusive);
        // Verificar que el estado del entry e1 del pe3 es invalido
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Invalid);
    }


    // SECTION("11. Lectura de la direccion 04 cuando la direccion no esta en cache local pero existe en cache externa") {
    //     std::cout << "Caso 11\n" << std::endl;
    //     // peLocal escribe en la direccion 04 con valor 78
    //     mesi.writeMESI(pe3.processor_id, "04", 78, pe3, pe1, pe2);
    //     pe3.CACHE.print();
    //     pe1.CACHE.print();
    //     pe2.CACHE.print();
    //     mesi.readMESI(pe2.processor_id, "04", pe2, pe1, pe3);
    //     pe2.CACHE.print();
    //     memory.print();
    //     // Verificar que el dato en e1 es 80 y que el estado de la cache es M
    //     REQUIRE(pe2.CACHE.e1.getData() == 78);
    //     REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Shared);
    //     REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Shared);
    // }

    /*
    SECTION("2. Test readMESI with shared state on both external PE") {
        // Memory en direccion 00 con valor 55
        mesi.writeMESI(pe1.processor_id, "08", 10);
        pe1.CACHE.print(pe1.processor_id);
        memory.print();

        // Verificar que el dato en e1 es 80 y que el estado de la cache es M
        REQUIRE(pe1.CACHE.e1.getData() == 80);
        REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Modified);


        // Verificar que resultado es 55 y que el estado de la cache local es S
        REQUIRE(result == 55);
        REQUIRE(peLocal.CACHE.e1.getStatus() == StateEnum::Shared);
    }
    /*
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