#pragma once
#include <string>
// Serves as a proccessing channel 'K1' state encapsulate in SimState
class K1 {
public:
	int generatedK1WaitTime = 0;// Temporary SimState generated WT, used to change savedK1Waittime and stringK1WT
	int savedK1WaitTime = 0;// Check if K1 is changable
	bool processingK1 = false;// Proccessing request status 
	
	std::string stringK1 = ""; // Outputable request proccessing status
	std::string stringK1WT = ""; // Outputable requests proccessing wait time 
};