#ifndef GENERATERANDOMCODE_H
#define GENERATERANDOMCODE_H


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include "../logManagement.cpp"

class generateRandomCode {
public:
    int INSTRUC_AMOUNT = 8; // N
    int INSTRUC_MAX = 3;    // M Read / Write
    int REGISTER_MAX = 16;  // R
    

    generateRandomCode() {
        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    std::vector<std::string> getRandomCode() {
        std::vector<int> randomAddress = getRandomAddress();
        std::vector<int> randomInstructions = getRandomInstruc();
        std::vector<std::string> code;

        if (randomAddress.size() != randomInstructions.size()) {
            // Handle the case where vectors have different sizes
            std::cerr << "Vectors have different sizes." << std::endl;
            return std::vector<std::string>();
        }

        for (size_t i = 0; i < randomAddress.size(); ++i) {
            // Convert integers to binary strings
            std::string addressBinary = std::bitset<8>(randomAddress[i]).to_string();
            std::string instructionBinary = std::bitset<4>(randomInstructions[i]).to_string();

            // Concatenate binary strings
            std::string concatenatedBinary = instructionBinary + addressBinary;
            code.push_back(concatenatedBinary);
        }
        log.logMessage("RandomCodeGenerated ", code);
        return code; 
    }

private:
    logger& log = logger::getInstance(); // Create an instance of Logger
    void printVector(const std::string& name, std::vector<int> vector){
        std::cout << name << std::endl;
        for (int value : vector) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> getRandomAddress() {
        std::vector<int> randomAddress(INSTRUC_AMOUNT);

        // Generate N random addresees between 0 and R
        for (int i = 0; i < INSTRUC_AMOUNT; ++i) {
            randomAddress[i] = std::rand() % REGISTER_MAX * 4 ;
        }
        //printVector("Random Address:", randomAddress );
        return randomAddress;
    }

    std::vector<int> getRandomInstruc() {
        std::vector<int> randomInstructions(INSTRUC_AMOUNT);

        // Generate N random instructions between 1and M
        for (int i = 0; i < INSTRUC_AMOUNT; ++i) {
            randomInstructions[i] = (std::rand() % INSTRUC_MAX) + 1 ;
        }

        // Check for missing instructions
        std::vector<bool> instructionFound(INSTRUC_MAX + 1, false);
        for (int instr : randomInstructions) {
            instructionFound[instr] = true;
        }

        // Replace duplicates with missing instructions if necessary
        for (int i = 1; i <= INSTRUC_MAX; ++i) {
            if (!instructionFound[i]) {
                for (int j = 0; j < INSTRUC_AMOUNT; ++j) {
                    if (randomInstructions[j] != i) {
                        randomInstructions[j] = i;
                        instructionFound[i] = true;
                        break;
                    }
                }
            }
        }

        //printVector("Random Instructions:", randomInstructions );
        return randomInstructions;
    }
};


#endif 
