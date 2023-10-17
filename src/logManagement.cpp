#ifndef LOGMANAGEMENT_H
#define LOGMANAGEMENT_H

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

        void logCacheRead(int idPE, StateEnum status, std::string address, int idEntry, int data){
            std::string logMessage = "";
            switch(status){
                case StateEnum::Modified:
                    logMessage = "PE" + std::to_string(idPE) + " | r | M | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Owned:
                    logMessage = "PE" + std::to_string(idPE) + " | r | O | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Exclusive:
                    logMessage = "PE" + std::to_string(idPE) + " | r | E | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Shared:
                    logMessage = "PE" + std::to_string(idPE) + " | r | S | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Invalid:
                    logMessage = "PE" + std::to_string(idPE) + " | r | I | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
            }
            logMessages.push_back(logMessage);
        }

        void logCacheWrite(int idPE, StateEnum status, std::string address, int idEntry, int data){
            std::string logMessage = "";
            switch(status){
                case StateEnum::Modified:
                    logMessage = "PE" + std::to_string(idPE) + " | w | M | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Owned:
                    logMessage = "PE" + std::to_string(idPE) + " | w | O | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Exclusive:
                    logMessage = "PE" + std::to_string(idPE) + " | w | E | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Shared:
                    logMessage = "PE" + std::to_string(idPE) + " | w | S | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
                case StateEnum::Invalid:
                    logMessage = "PE" + std::to_string(idPE) + " | w | I | " + address + " | " + "Entry" + std::to_string(idEntry) + " | " + std::to_string(data);
                    break;
            }
            logMessages.push_back(logMessage);
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


        // antes de cada updateValue y loadValues
        void writeLog(std::string path){
            if (logMessages.empty()){
                std::cout << "Empty log" << std::endl;
                return;    
            }

            std::ofstream logFile(path, std::ios::out | std::ios::trunc);
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