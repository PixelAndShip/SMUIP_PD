#pragma once
#include <vector>
#include <string>
class OutputSimState {
public:
	int currentTime = 0;

	std::string usedGS = "";

	int generatedA1WaitTime = 0;
	int savedA1WaitTime = 0;
	
	std::string stringA1WT = "";

	int generatedK1WaitTime = 0;
	int savedK1WaitTime = 0;
	int K1 = -1;
	bool processingK1= false;
	std::string stringK1 = "";
	std::string stringK1WT = "";

	int generatedK2WaitTime = 0;
	int savedK2WaitTime = 0;
	int K2 = -1;
	bool processingK2 = false;
	std::string stringK2 = "";
	std::string stringK2WT = "";

	int R1 = 0;
	std::string stringR1 = "";

	int processedRequests = 0;
	OutputSimState() {

	}
	OutputSimState(int lSavedA1,int lSavedK1, int lSavedK2,int procK1, int procK2, int procR): savedA1WaitTime(lSavedA1), savedK1WaitTime(lSavedK1), savedK2WaitTime(lSavedK2),processingK1(procK1),processingK2(procK2), processedRequests(procR) {

	}

	OutputSimState(int savedA1,int savedK1,int savedK2,int lR1,int procR): 
		savedA1WaitTime(savedA1),savedK1WaitTime(savedK1),savedK2WaitTime(savedK2), R1(lR1),processedRequests(procR) {

	}
};