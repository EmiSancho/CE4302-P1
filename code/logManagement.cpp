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

        void logMessage(std::string message, std::vector<std::string> vector){
            std::string tmp = message;
            for (int i = 0;  i < vector.size(); ++i) {
                tmp = tmp + vector[i] + " ";
            }
            logMessages.push_back(tmp);
        }

        void logPackage(const Package& package){
            logMessages.push_back(package.toString());
        }

        void logPackage(std::string message, Package& package){
            logMessages.push_back( message + package.toString());
        }

        void logMemRead(const std::string& addr, int data){
            std::string logMessage = "r | " + addr + " | " + std::to_string(data);
            logMessages.push_back(logMessage);
        }
        void logMemWrite(const std::string& addr, int data){
            std::string logMessage = "w | " + addr + " | " + std::to_string(data);
            logMessages.push_back(logMessage);
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
};
#endif