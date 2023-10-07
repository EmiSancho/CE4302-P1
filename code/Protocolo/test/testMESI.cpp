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
    
    SECTION("1. Escritura en la direccion 04 cuando la no existe ninguna cache") {
        std::cout << "Caso 1 \n" << std::endl;
        // peLocal escribe en la direccion 04 con valor 55
        mesi.writeMESI("04", 80, pe1, pe2, pe3);
        pe1.CACHE.print();
        memory.print();
        // Verificar que el dato en e1 es 80 y que el estado de la cache es M
        REQUIRE(pe1.CACHE.e1.getData() == 80);
        REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Modified);
    }

    SECTION("2. Escritura en la direccion 04 cuando la direccion ya existe en mi cache y el estado es Modificado") {
        std::cout << "Caso 2 \n" << std::endl;
        // peLocal escribe en la direccion 04 con valor 80
        mesi.writeMESI("04", 74, pe3, pe1, pe2);
        pe3.CACHE.print();
        memory.print();
        mesi.writeMESI("04", 80, pe3, pe1, pe2);
        pe3.CACHE.print();
        // Verificar que el dato en e1 es 78 y que el estado de la cache es M
        REQUIRE(pe3.CACHE.e1.getData() == 80);
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Modified);
    }

     SECTION("3. Escritura en la direccion 04 cuando la direccion ya existe en mi cache y el estado es Exclusivo") {
        std::cout << "Caso 3 \n" << std::endl;
        // peLocal escribe en la direccion 04 con valor 80
        mesi.writeMESI("04", 70, pe3, pe1, pe2);
        pe3.CACHE.print();
        mesi.writeMESI("04", 74, pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        mesi.writeMESI("04", 80, pe2, pe1, pe3);
        pe2.CACHE.print();
        pe3.CACHE.print();
        memory.print();
        // Verificar que el dato en e1 es 78 y que el estado de la cache es M
        REQUIRE(pe2.CACHE.e1.getData() == 80);
        REQUIRE(memory.read("04") == 74);
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Modified);
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Invalid);
    }

    SECTION("4. Escritura en la direccion 04 cuando la direccion existe en la cache local y el estado es Compartido") {
       std::cout << "Caso 4 \n" << std::endl;
        // peLocal escribe en la direccion 04 con valor 78
        mesi.writeMESI("04", 78, pe3, pe1, pe2);
        pe3.CACHE.print();
        mesi.readMESI("04", pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        mesi.writeMESI("04", 66, pe3, pe1, pe2);
        pe3.CACHE.print();
        pe2.CACHE.print();
        memory.print();
        // Verificar que el dato del entry e1 del pe2 es 66
        REQUIRE(pe3.CACHE.e1.getData() == 66);
        // Verificar que el dato de memoria es 66
        REQUIRE(memory.read("04") == 66);
        // Verificar que el estado del entry e1 del pe3 es Exclusivo
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Exclusive);
        // Verificar que el estado del entry e1 del pe2 es invalido
        REQUIRE(pe2.CACHE.getEntry("04").getStatus() == StateEnum::Invalid);
    }

    SECTION("5. Escritura en la direccion 04 cuando la direccion ya existe en mi cache y el estado es Invalido") {
        // peLocal escribe en la direccion 04 con valor 80
        std::cout << "Caso 5 \n" << std::endl;
        mesi.writeMESI("04", 70, pe3, pe1, pe2);
        pe3.CACHE.print();
        mesi.writeMESI("04", 74, pe2, pe1, pe3);
        pe2.CACHE.print();
        pe3.CACHE.print();
        memory.print();
        mesi.writeMESI("04", 80, pe3, pe1, pe2);
        pe2.CACHE.print();
        pe3.CACHE.print();
        memory.print();
        // Verificar que el dato en e1 es 78 y que el estado de la cache es M
        REQUIRE(pe3.CACHE.e1.getData() == 80);
        REQUIRE(memory.read("04") == 80);
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Exclusive);
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Invalid);
    }

    SECTION("6. Escritura en la direccion 04 cuando la direccion no existe en la cache local y si en una externa con estado Modificado") {
        std::cout << "Caso 6 \n" << std::endl;
        // peLocal escribe en la direccion 04 con valor 78
        mesi.writeMESI("04", 78, pe3, pe1, pe2);
        pe3.CACHE.print();
        mesi.writeMESI("04",95, pe2, pe1, pe3);
        pe2.CACHE.print();
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
    
    SECTION("7. Escritura en la direccion 04 cuando la direccion no existe en la cache local y si en una externa con estado Exclusivo") {
        std::cout <<  "Caso 7 \n"<< std::endl;
        // peLocal escribe en la direccion 04 con valor 78
        mesi.writeMESI("04", 78, pe3, pe1, pe2);
        pe3.CACHE.print();
        mesi.writeMESI("04",95, pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        mesi.writeMESI("04", 14, pe1, pe2, pe3);
        pe1.CACHE.print();
        memory.print();
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe1.CACHE.e1.getData() == 14);
        // Verificar que el dato de memoria es 66
        REQUIRE(memory.read("04") == 14);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Exclusive);
        // Verificar que el estado del entry e1 del pe2 es invalido
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Invalid);
        // Verificar que el estado del entry e1 del pe3 es invalido
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Invalid);
    }

    SECTION("8. Escritura en la direccion 04 cuando la direccion no existe en la cache local y si en una externa con estado Compartido") {
        std::cout <<  "Caso 8 \n"<< std::endl;
        // peLocal escribe en la direccion 04 con valor 78
        mesi.writeMESI("04", 78, pe1, pe2, pe3);
        pe1.CACHE.print();
        mesi.readMESI("04", pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        mesi.writeMESI("04", 14, pe3, pe1, pe2);
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
        mesi.writeMESI("00", 10, pe1, pe2, pe3);
        mesi.writeMESI("04", 20, pe1, pe2, pe3);
        mesi.writeMESI("08", 30, pe1, pe2, pe3);
        mesi.writeMESI("12", 40, pe1, pe2, pe3);
        pe1.CACHE.print();
        mesi.writeMESI("16", 50, pe1, pe2, pe3);
        pe1.CACHE.print();
        memory.print();
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe1.CACHE.e1.getData() == 20);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe1.CACHE.e1.getStatus() == StateEnum::Modified);
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe1.CACHE.e2.getData() == 30);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe1.CACHE.e2.getStatus() == StateEnum::Modified);
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe1.CACHE.e3.getData() == 40);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe1.CACHE.e3.getStatus() == StateEnum::Modified);
        // Verificar que el dato del entry e1 del pe2 es 95
        REQUIRE(pe1.CACHE.e4.getData() == 50);
        // Verificar que el estado del entry e1 del pe2 es exclusivo
        REQUIRE(pe1.CACHE.e4.getStatus() == StateEnum::Modified);
    }

    SECTION("10. Escritura en direccion 44 y no existe en la cache local, cache esta llena y direccion 44 esta en S con externo") {
        std::cout << "Caso 10 \n" << std::endl;
        // pe1 se llena de datos en los 4 entrys
        mesi.writeMESI("08", 10, pe1, pe2, pe3);
        mesi.writeMESI("20", 20, pe1, pe2, pe3);
        mesi.writeMESI("28", 30, pe1, pe2, pe3);
        mesi.writeMESI("04", 40, pe1, pe2, pe3);
        // pe2 y pe1 tienen la direccion 28 en estado S
        mesi.readMESI("08", pe2, pe1, pe3);
        pe1.CACHE.print();
        pe2.CACHE.print();
        memory.print();
        // Agregar otro dato y por politica FIFO se elimina el dato en e1
        mesi.writeMESI("44", 50, pe1, pe2, pe3);
        pe1.CACHE.print();
        // Verificar que el dato del entry en direccion 44 del pe1 es 50
        REQUIRE(pe1.CACHE.getEntry("44").getData() == 50);
        // Verificar que el estado del entry en direccion 44 del pe1 es M
        REQUIRE(pe1.CACHE.getEntry("44").getStatus() == StateEnum::Modified);
        // Verificar que el estado del entry e1 del pe1 es Shared
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Shared);
    }

    SECTION("11. Lectura de la direccion 04 cuando la direccion no esta en cache local pero existe en cache externa") {
        std::cout << "Caso 11\n" << std::endl;
        // peLocal escribe en la direccion 04 con valor 78
        mesi.writeMESI("04", 78, pe3, pe1, pe2);
        pe3.CACHE.print();
        pe1.CACHE.print();
        pe2.CACHE.print();
        mesi.readMESI("04", pe2, pe1, pe3);
        pe2.CACHE.print();
        memory.print();
        // Verificar que el dato en e1 es 80 y que el estado de la cache es M
        REQUIRE(pe2.CACHE.e1.getData() == 78);
        REQUIRE(pe3.CACHE.e1.getStatus() == StateEnum::Shared);
        REQUIRE(pe2.CACHE.e1.getStatus() == StateEnum::Shared);
    }

    SECTION("12. Lectura de la direccion 60 y no existe en la cache local ni en externa") {
        std::cout << "Caso 12 \n" << std::endl;
        // Se escribe un dato en memoria en la direccion 60
        memory.write("60", 120);
        // pe3 lee la direccion 60
        mesi.readMESI("60", pe3, pe1, pe2);
        pe3.CACHE.print();
        memory.print();
        // Verificar que el dato en direccion 60 de memoria es 120
        REQUIRE(memory.read("60") == 120);
        // Verificar que el estado del entry en direccion 60 del pe3 es E
        REQUIRE(pe3.CACHE.getEntry("60").getStatus() == StateEnum::Exclusive);
        // Verificar que el dato que leyo el pe3 es 120
        REQUIRE(pe3.CACHE.getEntry("60").getData() == 120);
    }

     SECTION("13. Lectura de la dirección cuando la dirección está en caché local con estado M") {
        std::cout << "Caso 13 \n" << std::endl;
        // pe2 escribe en la direccion 52 con valor 78
        mesi.writeMESI("52", 78, pe2, pe1, pe3);
        // pe2 lee la direccion 52
        mesi.readMESI("52", pe2, pe1, pe3);
        pe2.CACHE.print();
        // Verificar que el estado del entry en direccion 52 del pe2 es M
        REQUIRE(pe2.CACHE.getEntry("52").getStatus() == StateEnum::Modified);
        // Verificar que el dato que leyo el pe2 es 78
        REQUIRE(pe2.CACHE.getEntry("52").getData() == 78);
    }

     SECTION("14. Lectura de la dirección cuando la dirección está en caché local con estado E") {
        std::cout << "Caso 14 \n" << std::endl;
        // pe2 y pe1 leen la direccion 00, estan en estado S
        mesi.readMESI("00", pe2, pe1, pe3);
        mesi.readMESI("00", pe1, pe2, pe3);
        pe2.CACHE.print();
        pe1.CACHE.print();
        // pe2 escribe un 38 en direccion 00, queda como E y pe1 como I
        mesi.writeMESI("00", 38, pe2, pe1, pe3);
        pe2.CACHE.print();
        // pe2 lee la direccion 00, pasaria a M
        mesi.readMESI("00", pe2, pe1, pe3);
        // Verificar que el estado del entry en direccion 00 del pe2 es E
        REQUIRE(pe2.CACHE.getEntry("00").getStatus() == StateEnum::Exclusive);
        // Verificar que el estado del entry en direccion 00 del pe1 es I
        REQUIRE(pe1.CACHE.getEntry("00").getStatus() == StateEnum::Invalid);
        // Verificar que el dato que leyo el pe2 es 38
        REQUIRE(pe2.CACHE.getEntry("00").getData() == 38);
    }

     SECTION("15. Lectura de la direccion cuando la direccion esta en cache local con estado S") {
        std::cout << "Caso 15 \n" << std::endl;
        // pe2 y pe1 leen la direccion 00, estan en estado S
        memory.print();
        mesi.readMESI("00", pe2, pe1, pe3);
        mesi.readMESI("00", pe1, pe2, pe3);
        pe2.CACHE.print();
        pe1.CACHE.print();
        // pe2 lee de nuevo, se mantiene en S
        mesi.readMESI("00", pe2, pe1, pe3);
        // Verificar que el estado del entry en direccion 00 del pe2 es S
        REQUIRE(pe2.CACHE.getEntry("00").getStatus() == StateEnum::Shared);
        // Verificar que el estado del entry en direccion 00 del pe1 es S
        REQUIRE(pe1.CACHE.getEntry("00").getStatus() == StateEnum::Shared);
        // Verificar que el dato que leyo el pe2 es 0
        REQUIRE(pe2.CACHE.getEntry("00").getData() == 38);
    }

     SECTION("16. Lectura de la dirección cuando la dirección está en cache local con estado I") {
        std::cout << "Caso 16 \n" << std::endl;
        //pe2 y pe1 leen la direccion 00, estan en estado S
        mesi.readMESI("00", pe2, pe1, pe3);
        mesi.readMESI("00", pe1, pe2, pe3);
        pe2.CACHE.print();
        pe1.CACHE.print();
        // pe2 escribe un 38 en direccion 00, queda como E y pe1 como I
        mesi.writeMESI("00", 38, pe2, pe1, pe3);
        pe2.CACHE.print();
        // pe2 lee la direccion 00, pasaria a M
        mesi.readMESI("00", pe1, pe2, pe3);
        pe1.CACHE.print();
        // Verificar que el estado del entry en direccion 00 del pe2 es E
        REQUIRE(pe2.CACHE.getEntry("00").getStatus() == StateEnum::Shared);
        // Verificar que el estado del entry en direccion 00 del pe1 es I
        REQUIRE(pe1.CACHE.getEntry("00").getStatus() == StateEnum::Shared);
        // Verificar que el dato que leyo el pe2 es 38
        REQUIRE(pe2.CACHE.getEntry("00").getData() == 38);
        // Verificar que el dato que leyo el pe1 es 38
        REQUIRE(pe1.CACHE.getEntry("00").getData() == 38);
    }

    

}