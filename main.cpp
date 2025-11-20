#include "OutputSimStates.h"
#include <string>
#include <vector>
#include "GST.h"
#include "Output.h"

GST GSTable;
Output OP;





void generateWaitTime(OutputSimState* nextIteration, int type,int currentID) {
	GSTable.currentNumberId += 1;
	nextIteration->usedGS += std::to_string(GSTable.currentNumberId)+" ";
	if ((GSTable.currentNumberId - 1) < GSTable.randomNumbers.size()) {
		switch (type) {
		case 1:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.00) {
				nextIteration->generatedA1WaitTime = currentID+ 4;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.66) {
				nextIteration->generatedA1WaitTime = currentID + 3;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.33) {
				nextIteration->generatedA1WaitTime = currentID + 2;
			}
			nextIteration->savedA1WaitTime = nextIteration->generatedA1WaitTime;
			break;
		case 2:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.00) {
				nextIteration->generatedK1WaitTime = currentID + 4;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.66) {
				nextIteration->generatedK1WaitTime = currentID + 3;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.33) {
				nextIteration->generatedK1WaitTime = currentID + 2;
			}
			nextIteration->savedK1WaitTime = nextIteration->generatedK1WaitTime;
			break;
		case 3:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.0) {
				nextIteration->generatedK2WaitTime = currentID + 8;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.8) {
				nextIteration->generatedK2WaitTime = currentID + 7;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.6) {
				nextIteration->generatedK2WaitTime = currentID + 6;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.4) {
				nextIteration->generatedK2WaitTime = currentID + 5;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.2) {
				nextIteration->generatedK2WaitTime = currentID + 4;
			}
			nextIteration->savedK2WaitTime = nextIteration->generatedK2WaitTime;
			break;
		}


	}


}




void manageNextIteration(OutputSimState* lastIteration, OutputSimState* nextIteration, int sNIID) {
	nextIteration->R1 = lastIteration->R1;

	// 1. Empty K2
	if (lastIteration->savedK2WaitTime == sNIID && lastIteration->processingK2) {
		nextIteration->processedRequests += 1;
		nextIteration->processingK2 = false;
		nextIteration->K2 = 0;
		nextIteration->savedK2WaitTime = 0;
		// update log strings...
		nextIteration->stringK2 += "0";
		nextIteration->stringK2WT += "_";
		nextIteration->stringA1WT += "_";
		nextIteration->stringK1 += "_";
		nextIteration->stringK1WT += "_";
		nextIteration->stringR1 += "_";
		nextIteration->usedGS += "_";
	}
	else {
		// If K2 not emptied, carry over states
		nextIteration->savedK2WaitTime = lastIteration->savedK2WaitTime;
		if (lastIteration->processingK2)
			nextIteration->processingK2 = true;
	}

	// 2. If K2 free after empty, move request from R1 if any
	if (!nextIteration->processingK2 && nextIteration->R1 > 0) {
		nextIteration->R1 -= 1;
		nextIteration->K2 = 1;
		generateWaitTime(nextIteration, 3, sNIID);
		nextIteration->savedK2WaitTime = nextIteration->generatedK2WaitTime;
		nextIteration->processingK2 = true;
		nextIteration->stringK2 += "1";
		nextIteration->stringK2WT += std::to_string(nextIteration->generatedK2WaitTime);
		nextIteration->stringA1WT += "_";
		nextIteration->stringK1 += "_";
		nextIteration->stringK1WT += "_";
		nextIteration->stringR1 += std::to_string(nextIteration->R1);
	}

	// 3. Empty K1 and process possible move to K2/queue, generate K2 waittime if transferred to K2
	if (lastIteration->savedK1WaitTime == sNIID) {
		nextIteration->K1 = 0;
		nextIteration->processingK1 = false;
		nextIteration->savedK1WaitTime = 0;
		nextIteration->stringK1 += "0";
		nextIteration->stringK1WT += "_";
		nextIteration->R1 += 1;
		nextIteration->stringR1 += std::to_string(nextIteration->R1);
		nextIteration->stringK2 += "_";
		nextIteration->stringK2WT += "_";
		// Try to move to K2 if K2 now empty and not already processed this iteration
		if (!nextIteration->processingK2 && nextIteration->R1 > 0) {
			nextIteration->processingK2 = true;
			nextIteration->K2 = 1;
			generateWaitTime(nextIteration, 3, sNIID);
			nextIteration->savedK2WaitTime = nextIteration->generatedK2WaitTime;
			nextIteration->stringK2 += "1";
			nextIteration->stringK2WT += std::to_string(nextIteration->generatedK2WaitTime);
			nextIteration->stringR1 += "_";
			nextIteration->stringR1 += std::to_string(nextIteration->R1);
			nextIteration->stringA1WT += "_";
			nextIteration->stringK1 += "_";
			nextIteration->stringK1WT += "_";
		}
	}
	else if (lastIteration->savedK1WaitTime != sNIID) {
		nextIteration->savedK1WaitTime = lastIteration->savedK1WaitTime;
		if (lastIteration->processingK1)
			nextIteration->processingK1 = true;
	}

	// 4. Handle A1 to K1 only if K1 empty
	if (lastIteration->savedA1WaitTime == sNIID) {
		nextIteration->savedA1WaitTime = 0;
		if (!nextIteration->processingK1) {
			nextIteration->processingK1 = true;
			nextIteration->K1 = 1;
			generateWaitTime(nextIteration, 2, sNIID);
			nextIteration->savedK1WaitTime = nextIteration->generatedK1WaitTime;
			nextIteration->stringK1 += "1";
			nextIteration->stringK1WT += std::to_string(nextIteration->generatedK1WaitTime);
			nextIteration->stringR1 += "_";
			nextIteration->stringR1 += std::to_string(nextIteration->R1);
			nextIteration->stringK2 += "_";
			nextIteration->stringK2WT += "_";
		}
		generateWaitTime(nextIteration, 1, sNIID);
		nextIteration->savedA1WaitTime = nextIteration->generatedA1WaitTime;
		nextIteration->stringA1WT += std::to_string(nextIteration->generatedA1WaitTime);
	}
	else if (lastIteration->savedA1WaitTime != sNIID) {
		nextIteration->savedA1WaitTime = lastIteration->savedA1WaitTime;
	}
}






int getNextIterationNumber(OutputSimState* lastIteration) {
	int nums[] = { lastIteration->savedA1WaitTime,lastIteration->savedK1WaitTime,lastIteration->savedK2WaitTime };
	
	int n = sizeof(nums) / sizeof(nums[0]);
	
	int smallestNextIterationID = *std::max_element(nums,nums+n);
	std::cout << smallestNextIterationID;
	for (int num : nums) {
		if (num < smallestNextIterationID&&num!=0) {
			smallestNextIterationID = num;
		}
	}
	std::cout << smallestNextIterationID;
	return smallestNextIterationID;
}
OutputSimState* generateIteration(OutputSimState* lastIteration) {

	OutputSimState* newIteration = new OutputSimState(lastIteration->savedA1WaitTime,lastIteration->savedK1WaitTime,lastIteration->savedK2WaitTime,lastIteration->processingK1,lastIteration->processingK2,lastIteration->processedRequests);
	int smallestNextIterationID = getNextIterationNumber(lastIteration);
	newIteration->currentTime = smallestNextIterationID;
	manageNextIteration(lastIteration, newIteration, smallestNextIterationID);
	return newIteration;
}

void manageSim() {
	OutputSimStates* OSS = new OutputSimStates();
	OutputSimState* firstIteration = new OutputSimState();
	firstIteration->savedA1WaitTime = 2;
	firstIteration->generatedA1WaitTime = 2;
	GSTable.currentNumberId += 1;
	firstIteration->usedGS = "1";
	OP.printOutputSimState(*firstIteration, GSTable);
	OSS->SS.push_back(firstIteration);
	OutputSimState* newIteration = generateIteration(firstIteration);
	
	OP.printOutputSimState(*newIteration,GSTable);
	OSS->SS.push_back(newIteration);
	while (OSS->SS.back()->processedRequests != 4) {
		
		newIteration = generateIteration(newIteration);
		OSS->SS.push_back(newIteration);
		OP.printOutputSimState(*newIteration,GSTable);
	}
	OP.printToExcelCSV(OSS->SS, "U_4_61.csv");
}




int main() {
	manageSim();


}