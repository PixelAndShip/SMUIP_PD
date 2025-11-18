#pragma once
#include "OutputSimStates.h"
#include "GST.h"
#include <iostream>
class Output {
public:



    void printToTXT(OutputSimStates* AllStates, GST UsedGS) {

    };


    void printOutputSimState(const OutputSimState& state) {
        std::cout << "currentTime: " << state.currentTime << std::endl;

        std::cout << "usedGS: ";
        for (const auto& gs : state.usedGS)
            std::cout << gs << " ";
        std::cout << std::endl;

        std::cout << "generatedA1WaitTime: " << state.generatedA1WaitTime << std::endl;
        std::cout << "savedA1WaitTime: " << state.savedA1WaitTime << std::endl;

        std::cout << "generatedK1WaitTime: " << state.generatedK1WaitTime << std::endl;
        std::cout << "savedK1WaitTime: " << state.savedK1WaitTime << std::endl;

        std::cout << "K1: ";
        for (const auto& val : state.K1)
            std::cout << val << " ";
        std::cout << std::endl;

        std::cout << "processingK1: " << (state.processingK1 ? "true" : "false") << std::endl;

        std::cout << "generatedK2WaitTime: " << state.generatedK2WaitTime << std::endl;
        std::cout << "savedK2WaitTime: " << state.savedK2WaitTime << std::endl;

        std::cout << "K2: ";
        for (const auto& val : state.K2)
            std::cout << val << " ";
        std::cout << std::endl;

        std::cout << "processingK2: " << (state.processingK2 ? "true" : "false") << std::endl;

        std::cout << "R1: " << state.R1 << std::endl;
        std::cout << "processedRequests: " << state.processedRequests << std::endl;
        std::cout << std::endl;
    };

};