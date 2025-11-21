#pragma once
#include <vector>
#include <string>
#include "A1.h"
#include "K1.h"
#include "R1.h"
class SimState {
public:
	int currentTime = 0;

	std::string usedGS = "";

	A1 a1 = A1();

	K1 k1 = K1();

	int generatedK2WaitTime = 0;
	int savedK2WaitTime = 0;
	int K2 = -1;
	bool processingK2 = false;
	std::string stringK2 = "";
	std::string stringK2WT = "";

	R1 r1 = R1();

	int processedRequests = 0;
	SimState() {

	}
	SimState(int lSavedA1,int lSavedK1, int lSavedK2,int procK1, int procK2, int procR):savedK2WaitTime(lSavedK2),processingK2(procK2), processedRequests(procR) {
		a1.savedA1WaitTime = lSavedA1;
		k1.savedK1WaitTime = lSavedK1;
		k1.processingK1 = procK1;

	}

	SimState(int savedA1,int savedK1,int savedK2,int lR1,int procR): 
		savedK2WaitTime(savedK2),processedRequests(procR) {

		a1.savedA1WaitTime = savedA1;
		k1.savedK1WaitTime = savedK1;
		r1.stR1 = lR1;
	}
};