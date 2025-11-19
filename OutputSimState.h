#pragma once
#include <vector>
class OutputSimState {
public:
	int currentTime = 0;

	int usedGS = 0;

	int generatedA1WaitTime = 0;
	int savedA1WaitTime = 0;

	int generatedK1WaitTime = 0;
	int savedK1WaitTime = 0;
	int K1 = -1;
	bool processingK1= false;

	int generatedK2WaitTime = 0;
	int savedK2WaitTime = 0;
	int K2 = -1;
	bool processingK2 = false;

	int R1 = 0;

	int processedRequests = 0;
	OutputSimState() {

	}
	OutputSimState(int lSavedA1,int lSavedK1, int lSavedK2): savedA1WaitTime(lSavedA1), savedK1WaitTime(lSavedK1), savedK2WaitTime(lSavedK2) {

	}

	OutputSimState(int savedA1,int savedK1,int savedK2,int lR1,int procR): 
		savedA1WaitTime(savedA1),savedK1WaitTime(savedK1),savedK2WaitTime(savedK2), R1(lR1),processedRequests(procR) {

	}
};