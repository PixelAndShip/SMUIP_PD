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
        
        /*
        currenttime A1WT K1WT K2WT output
        A1 A1enterK1 K1st K1enterR1 R1 R1enterK2 K2st K2exit
           A1exit
        */

        
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