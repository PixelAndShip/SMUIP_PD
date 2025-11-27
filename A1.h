#pragma once
#include <string>
// Serves as a request source 'A1' state encapsulator in SimState
class A1 {
public:
	int generatedA1WaitTime = 0;// Temporary SimState generated WT, used to change savedA1Waittime and stringA1WT
	int savedA1WaitTime = 0; // Check if A1 is to generate a request
	std::string stringA1WT = ""; // Outputable SimState A1WT 

};
