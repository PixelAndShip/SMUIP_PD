#pragma once
#include "Queue.h"
#include "Channel.h"
class SimState {
public:
    int iteration = 0;
    Channel A1;
    Channel K1;
    Queue R1;
    Channel K2;
    std::vector<int> UsedGS = { 1 };
    int processedRequestsCount = 0;
    SimState() : A1(), K1(), R1(), K2() {

    }

    SimState(int iter, int procReqC) : iteration(iter), processedRequestsCount(procReqC) {};
    virtual ~SimState() {
        
    };
    
};