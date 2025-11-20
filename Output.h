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

        // Write CSV header with only requested fields
        file << "currentTime,usedGS,stringA1WT,stringK1,stringK1WT,stringR1,stringK2,stringK2WT,processedRequests\n";

        // Write each state's selected data
        for (const auto& state : states) {
            file << state->currentTime << ",";
            // Quote strings that may contain spaces
            file << "\"" << state->usedGS << "\",";
            file << "\"" << state->stringA1WT << "\",";
            file << "\"" << state->stringK1 << "\",";
            file << "\"" << state->stringK1WT << "\",";
            file << "\"" << state->stringR1 << "\",";
            file << "\"" << state->stringK2 << "\",";
            file << "\"" << state->stringK2WT << "\",";
            file << state->processedRequests << "\n";
        }
        file.close();
        std::cout << "Excel CSV output saved to: " << filename << std::endl;
    }


};