#pragma once
#include <vector>
class OutputSimState {
public:
	int currentTime = 0;
	std::vector<int> usedGS = {};
	int generatedA1WaitTime = 0;
	int generatedK1WaitTime = 0;
	int generatedK2WaitTime = 0;
	std::vector<int> R1 = {};
	int processedRequests = 0;
};