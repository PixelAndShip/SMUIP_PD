#pragma once
#include "Queue.h"
#include "Channel.h"
class SimState {
public:
    int iteration = 0;
    Queue A1;
    Channel K1;
    Queue R1;
    Channel K2;
    int processedRequestsCount = 0;
    SimState() {

    };
    SimState(int iter, int procReqC) : iteration(iter), processedRequestsCount(procReqC) {};
    virtual ~SimState() {
         
    };
    
};