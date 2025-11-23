#pragma once
#include "SimStates.h"
#include "GST.h"
#include <iostream>
#include <fstream>
#include <windows.h>
class Output {
public:



    void printToTXT(SimStates* AllStates, GST UsedGS) {

    };

    void launchPrint() {
        std::cout << "                     __               __        ___" << std::endl;
        std::cout << "| |   | |           / / _            / /__     /   |" << std::endl;
        std::cout << "| |   | |          / /_| |_  ______ /  __ \\   /_/| |" << std::endl;  
        std::cout << "| |___| |         /____   _|        \\ \\__\\ \\     | |" << std::endl;  
        std::cout << "|_______| _______      |_|           \\_____/     |_|" << std::endl; 

    }


    void printOutputSimStates(SimStates* OSS,GST gst) {
        
        
        bool end = false;
        int currentId = 0;
        std::vector<SimState*> SS = OSS->SS;

        SimState* lastIteration = new SimState();
        
        bool K1 = false;
       
        bool K2 = false;
       
        if (SS.size() == 0) {
            std::cout << "ERROR: No simulated states!"<<std::endl;
            return;
        }
        for (int id = 0;id <= SS.back()->currentTime;id++) {
            bool gotMatchIt = false;
            for (SimState* currentIteration : SS) {
                if (currentIteration->currentTime == id) {
                    lastIteration = currentIteration;
                    gotMatchIt = true;
                    break;
                }
            }
            if (gotMatchIt) {
                gotMatchIt = false;
                std::cout << "id:" << id<<"|";
                std::cout << "A1WT:" << lastIteration->a1.stringA1WT << "--->";
                std::cout << "(K1:" << lastIteration->k1.stringK1 << " " << lastIteration->k1.stringK1WT << ")--->";
                std::cout << "R1:" << lastIteration->r1.stR1 << "--->";
                std::cout << "(K2:" << lastIteration->k2.stringK2 << " " << lastIteration->k2.stringK2WT << ")--->";
                std::cout << "Na:" << lastIteration->processedRequests;
                
            }
            else {
                
                std::cout << "id:" << id << "|";
                std::cout << "A1WT:" << "[]" << "--->";
                std::cout << "(K1:" << lastIteration->k1.stringK1 << " " << "[]" << ")--->";
                std::cout << "R1:" << lastIteration->r1.stR1 << "--->";
                std::cout << "(K2:" << lastIteration->k2.stringK2 << " " << "[]" << ")--->";
                std::cout << "Na:" << lastIteration->processedRequests;

            }
            std::cout << std::endl<<std::endl;

        }
        /*
        id:0_A1WT:0_(K1:1/0_K1WT:0)_R1:0_(K2:1/0_K2WT:0)_Na:0
        */
        delete lastIteration;
    };

    void printToExcelCSV(const std::vector<SimState*>& states, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        
        file << "tj,n,A1WT,K1,K1WT,R1,K2,K2WT,Napk\n";

       
        for (SimState* state : states) {
            file << state->currentTime << ",";
            
            file << "\"" << state->usedGS << "\",";
            file << "\"" << state->a1.stringA1WT << "\",";
            file << "\"" << state->k1.stringK1 << "\",";
            file << "\"" << state->k1.stringK1WT << "\",";
            file << "\"" << state->r1.stringR1 << "\",";
            file << "\"" << state->k2.stringK2 << "\",";
            file << "\"" << state->k2.stringK2WT << "\",";
            file << state->processedRequests << "\n";
        }
        file.close();
        std::cout << "Excel CSV output saved to: " << filename << std::endl;
    }


};