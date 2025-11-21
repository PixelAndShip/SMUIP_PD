#pragma once
#include "SimStates.h"
#include "GST.h"
#include <iostream>
#include <fstream>
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


    void printOutputSimState(const SimState& state,GST gst) {

        
    };

    void printToExcelCSV(const std::vector<SimState*>& states, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        
        file << "currentTime,usedGS,stringA1WT,stringK1,stringK1WT,stringR1,stringK2,stringK2WT,processedRequests\n";

       
        for (const auto& state : states) {
            file << state->currentTime << ",";
            
            file << "\"" << state->usedGS << "\",";
            file << "\"" << state->a1.stringA1WT << "\",";
            file << "\"" << state->k1.stringK1 << "\",";
            file << "\"" << state->k1.stringK1WT << "\",";
            file << "\"" << state->r1.stringR1 << "\",";
            file << "\"" << state->stringK2 << "\",";
            file << "\"" << state->stringK2WT << "\",";
            file << state->processedRequests << "\n";
        }
        file.close();
        std::cout << "Excel CSV output saved to: " << filename << std::endl;
    }


};