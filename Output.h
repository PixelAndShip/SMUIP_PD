#pragma once
#include "SimStates.h"
#include "GST.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cctype>
class Output {
public:


    void launchPrint() {
        std::cout << "                    __               __        ___" << std::endl;
        std::cout << "| |   | |           / / _            / /__     /   |" << std::endl;
        std::cout << "| |   | |          / /_| |_  ______ /  __ \\   /_/| |" << std::endl;  
        std::cout << "| |___| |         /____   _|        \\ \\__\\ \\     | |" << std::endl;  
        std::cout << "|_______| _______      |_|           \\_____/     |_|" << std::endl;
        std::cout << "____________________________________________________"<<std::endl;

    }


    void printOutputSimStates(SimStates* OSS,GST gst) {
        
        
        bool end = false;
        int currentId = 0;
        std::vector<SimState*> SS = OSS->SS;

        SimState* currentIteration = new SimState();
        
   
       
        if (SS.size() == 0) {
            std::cout << "ERROR: No simulated states!"<<std::endl;
            return;
        }
        int id = 0;
        for (;id <= SS.back()->currentTime;id++) {
            bool gotMatchIt = false;
            for (SimState* matchingIteration : SS) {
                if (matchingIteration->currentTime == id) {
                    currentIteration = matchingIteration;
                    gotMatchIt = true;
                    break;
                }
            }
            if (gotMatchIt) {
                gotMatchIt = false;
                std::cout << "id:" << id<<"|";
                std::cout << "A1WT:" << currentIteration->a1.stringA1WT << "--->";
                std::cout << "(K1:" << currentIteration->k1.stringK1 << " " << currentIteration->k1.stringK1WT << ")--->";
                std::cout << "R1:" << currentIteration->r1.stringR1 << "--->";
                std::cout << "(K2:" << currentIteration->k2.stringK2 << " " << currentIteration->k2.stringK2WT << ")--->";
                std::cout << "Na:" << currentIteration->processedRequests;
                


            }
            else {
                
                std::cout << "id:" << id << "|";
                std::cout << "A1WT:" << "n" << "--->";
                std::cout << "(K1:" << currentIteration->k1.processingK1 << " " << "n" << ")--->";
                std::cout << "R1:" << currentIteration->r1.stringR1 << "--->";
                std::cout << "(K2:" << currentIteration->k2.processingK2 << " " << "n" << ")--->";
                std::cout << "Na:" << currentIteration->processedRequests;

            }
            manageU_4_61_Tasks(OSS, currentIteration);
            
            std::cout << std::endl<<std::endl;

        }
       
        std::cout << "K1 work load: Total-K1-proccessing-iterations/Total-iterations= " << OSS->K1wl << "/" << (id - 1) << "= " << OSS->K1wl / (id - 1) << std::endl;
        std::cout << "K2 work load: Total-K2-proccessing-iterations/Total-iterations= " << OSS->K2wl << "/" << (id - 1) << "= " << OSS->K2wl / (id - 1) << std::endl;
        std::cout << "R1 average length: Total-R1-requests/Total-iterations= "<<OSS->totalR1<<"/"<<(id-1)<<"= " << OSS->totalR1 / (id - 1) << std::endl;
        if (OSS->R1out > 0) {
            std::cout << "R1 average wait time length 1: Total-R1-Wait-time/R1-exited-requests= " << OSS->totalR1WT<<"/"<<OSS->R1out <<"= " << OSS->totalR1WT / OSS->R1out << std::endl;
        }
        if (OSS->R1in > 0) {
            std::cout << "R1 average wait time length 2: Total-R1-requests/R1-entered-requests= "<<OSS->totalR1<<"/"<<OSS->R1in<<"= " << OSS->totalR1 / OSS->R1in;
        }
        

        /*
        id:0_A1WT:0_(K1:1/0_K1WT:0)_R1:0_(K2:1/0_K2WT:0)_Na:0
        */
        delete currentIteration;
    };

    void manageU_4_61_Tasks(SimStates* OSS,SimState* lastIteration) {
        OSS->K1wl += lastIteration->k1.processingK1;
        
       
        OSS->K2wl += lastIteration->k2.processingK2;
        
        int lastR1 = 0;
        for (int i = lastIteration->r1.stringR1.size()-1;i>=0;i--) {
            
            int intR1State = lastIteration->r1.stringR1[i] - '0';
            if (!isdigit(lastIteration->r1.stringR1[i])) {
                continue;
            }
            else {
                lastR1 = intR1State;
                break;
            }
           
            
            

        }
        
        OSS->totalR1 += lastR1;
        
    }


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