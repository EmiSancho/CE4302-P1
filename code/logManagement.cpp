#ifndef LOGMANAGEMENT_H
#define LOGMANAGEMENT_H


//#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "package.h"

class logger{
    public: 
        static logger& getInstance(){
            static logger instance;
            return instance;
        }

        void logMessage(std::string message){
            logMessages.push_back(message);
        }

        void logPackage(const Package& package){
            logMessages.push_back(package.toString());
        }

        void logRequest(){

        }

        void writeLog(){
            if (logMessages.empty()){
                std::cout << "Empty log" << std::endl;
                return;    
            }

            std::ofstream logFile("log", std::ios::out | std::ios::trunc);
            if (logFile.is_open()) {
                for (const std::string& message : logMessages) {
                    logFile << message << "\n";
                }
                logFile.close();
                std::cout << "Log has been written" << std::endl;
            } else {
                std::cerr << "Unable to write log file" << std::endl;
            }
        }


    private:
        logger(){};
        logger(const logger&) = delete;
        logger& operator=(const logger&) = delete;
        std::vector<std::string> logMessages;
        
}

#endif 