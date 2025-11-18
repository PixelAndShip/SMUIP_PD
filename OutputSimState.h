#pragma once
#include <vector>
class OutputSimState {
public:
	int currentTime = 0;

	std::vector<int> usedGS = {};

	int generatedA1WaitTime = 0;
	int savedA1WaitTime = 0;

	int generatedK1WaitTime = 0;
	int savedK1WaitTime = 0;
	std::vector<int> K1 = {};
	bool processingK1= false;

	int generatedK2WaitTime = 0;
	int savedK2WaitTime = 0;
	std::vector<int> K2 = {};
	bool processingK2 = false;

	int R1 = 0;

	int processedRequests = 0;
	OutputSimState() {

	}

	OutputSimState(int savedA1,int savedK1,int savedK2,int lR1,int procR): 
		savedA1WaitTime(savedA1),savedK1WaitTime(savedK1),savedK2WaitTime(savedK2), R1(lR1),processedRequests(procR) {

	}
};