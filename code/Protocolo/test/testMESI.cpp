#define CATCH_CONFIG_MAIN  // Esto le dice a Catch proporcionar la función main

#include "../../catch.hpp"
#include "../MESI.cpp"

TEST_CASE("Mesi", "[Mesi]") {
    Mesi mesi;
    MainMemory memory;
    generateRandomCode codeGenerator;
    // Inicializacion de peLocal, peExternal1, peExternal2, and memory as needed
    // peLocal
    std::vector<std::string> randomCodePeLocal = codeGenerator.getRandomCode();
    instrucctionMemory instMemPeLocal;
    instMemPeLocal.loadProgram(randomCodePeLocal);
    PE peLocal(1, instMemPeLocal);

    // peExternal1
    std::vector<std::string> randomCodePeExternal1 = codeGenerator.getRandomCode();
    instrucctionMemory instMemPeExternal1;
    instMemPeExternal1.loadProgram(randomCodePeExternal1);
    PE peExternal1(2, instMemPeExternal1);

    // peExternal2
    std::vector<std::string> randomCodePeExternal2 = codeGenerator.getRandomCode();
    instrucctionMemory instMemPeExternal2;
    instMemPeExternal2.loadProgram(randomCodePeExternal2);
    PE peExternal2(3, instMemPeExternal2);

    SECTION("Test writeMESI with data 55 on address 00") {
        // peLocal escribe en la direccion 00 con valor 55
        mesi.writeMESI("00", 55, memory, peLocal, peExternal1, peExternal2);

        // Verificar que el dato en e1 es 55 y que el estado de la cache local es M
        REQUIRE(peLocal.CACHE.e1.getData() == 55);
        REQUIRE(peLocal.CACHE.e1.getStatus() == StateEnum::Modified);
    }

    SECTION("Test readMESI with shared state on both external PE") {
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
        int result = mesi.readMESI(1, "00", memory, peLocal, peExternal1, peExternal2);

        // Verificar que resultado es 55 y que el estado de la cache local es S
        REQUIRE(result == 55);
        REQUIRE(peLocal.CACHE.e1.getStatus() == StateEnum::Shared);
    }

}