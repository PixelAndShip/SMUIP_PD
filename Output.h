#pragma once
#include "OutputSimStates.h"
#include "GST.h"
#include <iostream>
#include <fstream>
class Output {
public:



    void printToTXT(OutputSimStates* AllStates, GST UsedGS) {

    };


    void printOutputSimState(const OutputSimState& state,GST gst) {
        std::cout << "currentTime: " << state.currentTime << std::endl;

        std::cout << "usedGS: ";
        std::cout << state.usedGS;
        std::cout << std::endl;

        std::cout << "generatedA1WaitTime: " << state.generatedA1WaitTime << std::endl;
        std::cout << "savedA1WaitTime: " << state.savedA1WaitTime << std::endl;

        std::cout << "generatedK1WaitTime: " << state.generatedK1WaitTime << std::endl;
        std::cout << "savedK1WaitTime: " << state.savedK1WaitTime << std::endl;

        std::cout << "K1: ";
        std::cout << state.K1;
        std::cout << std::endl;

        std::cout << "processingK1: " << (state.processingK1 ? "true" : "false") << std::endl;

        std::cout << "generatedK2WaitTime: " << state.generatedK2WaitTime << std::endl;
        std::cout << "savedK2WaitTime: " << state.savedK2WaitTime << std::endl;

        std::cout << "K2: ";
        std::cout << state.K2;
        std::cout << std::endl;

        std::cout << "processingK2: " << (state.processingK2 ? "true" : "false") << std::endl;

        std::cout << "R1: " << state.R1 << std::endl;
        std::cout << "processedRequests: " << state.processedRequests << std::endl;
        std::cout << std::endl;
    };

    void printToExcelCSV(const std::vector<OutputSimState*>& states, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        // Write CSV header (excluding saved* columns)
        file << "currentTime,usedGS,generatedA1WaitTime,generatedK1WaitTime,K1,processingK1,generatedK2WaitTime,K2,processingK2,R1,processedRequests\n";

        // Write each state's data except saved ones
        for (const auto& state : states) {
            file << state->currentTime << ",";
            // Quote usedGS because it contains spaces
            file << "\"" << state->usedGS << "\",";
            file << state->generatedA1WaitTime << ",";
            file << state->generatedK1WaitTime << ",";
            file << state->K1 << ",";
            file << (state->processingK1 ? "true" : "false") << ",";
            file << state->generatedK2WaitTime << ",";
            file << state->K2 << ",";
            file << (state->processingK2 ? "true" : "false") << ",";
            file << state->R1 << ",";
            file << state->processedRequests << "\n";
        }
        file.close();
        std::cout << "Excel CSV output saved to: " << filename << std::endl;
    };

};