#pragma once
#include <vector>
#include <string>
#include "A1.h"
#include "K1.h"
#include "R1.h"
#include "K2.h"
class SimState {
public:
	int currentTime = 0;

	std::string usedGS = "";

	A1 a1 = A1();

	K1 k1 = K1();

	K2 k2 = K2();

	R1 r1 = R1();

	int processedRequests = 0;
	SimState() {

	}
	SimState(int lSavedA1,int lSavedK1, int lSavedK2,int procK1, int procK2, int procR):processedRequests(procR) {
		a1.savedA1WaitTime = lSavedA1;
		k1.savedK1WaitTime = lSavedK1;
		k1.processingK1 = procK1;
		k2.savedK2WaitTime = lSavedK2;
		k2.processingK2 = procK2;

	}

	SimState(int savedA1,int savedK1,int savedK2,int lR1,int procR): 
		processedRequests(procR) {

		a1.savedA1WaitTime = savedA1;
		k1.savedK1WaitTime = savedK1;
		r1.stR1 = lR1;
		k2.savedK2WaitTime = savedK2;
	}
};