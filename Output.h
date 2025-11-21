#pragma once
#include "SimStates.h"
#include "GST.h"
#include <iostream>
#include <fstream>
class Output {
public:



    void printToTXT(SimStates* AllStates, GST UsedGS) {

    };


    void printOutputSimState(const SimState& state,GST gst) {
        std::cout << "currentTime: " << state.currentTime << std::endl;

        std::cout << "usedGS: ";
        std::cout << state.usedGS;
        std::cout << std::endl;

        std::cout << "generatedA1WaitTime: " << state.a1.generatedA1WaitTime << std::endl;
        std::cout << "savedA1WaitTime: " << state.a1.savedA1WaitTime << std::endl;

        std::cout << "generatedK1WaitTime: " << state.k1.generatedK1WaitTime << std::endl;
        std::cout << "savedK1WaitTime: " << state.k1.savedK1WaitTime << std::endl;

        std::cout << "K1: ";
        std::cout << state.k1.stK1;
        std::cout << std::endl;

        std::cout << "processingK1: " << (state.k1.processingK1 ? "true" : "false") << std::endl;

        std::cout << "generatedK2WaitTime: " << state.generatedK2WaitTime << std::endl;
        std::cout << "savedK2WaitTime: " << state.savedK2WaitTime << std::endl;

        std::cout << "K2: ";
        std::cout << state.K2;
        std::cout << std::endl;

        std::cout << "processingK2: " << (state.processingK2 ? "true" : "false") << std::endl;

        std::cout << "R1: " << state.r1.stR1 << std::endl;
        std::cout << "processedRequests: " << state.processedRequests << std::endl;
        std::cout << std::endl;
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