#include "OutputSimStates.h"
#include <string>
#include <vector>
#include "GST.h"
#include "Output.h"

GST GSTable;
Output OP;





void generateWaitTime(OutputSimState* nextIteration, int type) {
	GSTable.currentNumberId += 1;

	if ((GSTable.currentNumberId - 1) < GSTable.randomNumbers.size()) {
		switch (type) {
		case 1:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.00) {
				nextIteration->generatedA1WaitTime = 4;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.66) {
				nextIteration->generatedA1WaitTime = 3;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.33) {
				nextIteration->generatedA1WaitTime = 2;
			}
			nextIteration->savedA1WaitTime = nextIteration->generatedA1WaitTime;
			break;
		case 2:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.00) {
				nextIteration->generatedK1WaitTime = 4;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.66) {
				nextIteration->generatedK1WaitTime = 3;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.33) {
				nextIteration->generatedK1WaitTime = 2;
			}
			nextIteration->savedK1WaitTime = nextIteration->generatedK1WaitTime;
			break;
		case 3:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.0) {
				nextIteration->generatedK2WaitTime = 8;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.8) {
				nextIteration->generatedK2WaitTime = 7;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.6) {
				nextIteration->generatedK2WaitTime = 6;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.4) {
				nextIteration->generatedK2WaitTime = 5;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.2) {
				nextIteration->generatedK2WaitTime = 4;
			}
			nextIteration->savedK2WaitTime = nextIteration->generatedK2WaitTime;
			break;
		}


	}


}




void manageNextIteration(OutputSimState* lastIteration, OutputSimState* nextIteration,int sNIID){ 
	if (lastIteration->savedK2WaitTime != sNIID) {
		nextIteration->savedK2WaitTime = lastIteration->savedK2WaitTime;
	}
	else if (lastIteration->savedK2WaitTime == sNIID) {
		nextIteration->K2.push_back(0);
		nextIteration->processingK2 = false;
		nextIteration->processedRequests += 1;
		if (lastIteration->R1 != 0) {
			nextIteration->R1 -= 1;
			generateWaitTime(nextIteration, 3);
			nextIteration->usedGS.push_back(GSTable.currentNumberId);
			nextIteration->K2.push_back(1);
		}
	}

	else if (lastIteration->savedK1WaitTime != sNIID) {
		nextIteration->savedK1WaitTime = lastIteration->savedK1WaitTime;
	}
	else if (lastIteration->savedK1WaitTime == sNIID) {
		nextIteration->K1.push_back(0);
		if (nextIteration->R1 == 0) {
			if (nextIteration->processingK2 == false) {
				generateWaitTime(nextIteration, 3);
				nextIteration->usedGS.push_back(GSTable.currentNumberId);
				nextIteration->K2.push_back(1);
				nextIteration->processingK2 = true;
			}
			else {
				nextIteration->R1 += 1;
			}
		}
		else {
			nextIteration->R1 += 1;
		}
	}

	else if (lastIteration->savedA1WaitTime != sNIID) {
		nextIteration->savedA1WaitTime = lastIteration->savedA1WaitTime;
	}
	else if (lastIteration->savedA1WaitTime == sNIID) {
		if (nextIteration->processingK1 == false) {
			generateWaitTime(nextIteration, 2);
			nextIteration->usedGS.push_back(GSTable.currentNumberId);
			nextIteration->K1.push_back(1);
			nextIteration->processingK1 = true;
		}
	}
	if (lastIteration->savedA1WaitTime == 0) {
		generateWaitTime(nextIteration, 1);
	}

}





int getNextIterationNumber(OutputSimState* lastIteration) {
	int nums[] = { lastIteration->savedA1WaitTime,lastIteration->savedK1WaitTime,lastIteration->savedK2WaitTime };
	int n = sizeof(nums) / sizeof(nums[0]);
	int smallestNextIterationID = *std::min_element(nums,nums+n);
	return smallestNextIterationID;
}
OutputSimState* generateIteration(OutputSimState* lastIteration) {

	OutputSimState* newIteration = new OutputSimState(lastIteration->savedA1WaitTime, lastIteration->savedK1WaitTime, lastIteration->savedK2WaitTime, lastIteration->R1, lastIteration->processedRequests);
	int smallestNextIterationID = getNextIterationNumber(lastIteration);
	newIteration->currentTime = smallestNextIterationID;
	manageNextIteration(lastIteration, newIteration, smallestNextIterationID);
	return newIteration;
}

void manageSim() {
	OutputSimStates* OSS = new OutputSimStates();
	OutputSimState* firstIteration = new OutputSimState();
	OutputSimState* newIteration = generateIteration(firstIteration);
	OP.printOutputSimState(*newIteration);
	OSS->SS.push_back(newIteration);
	while (OSS->SS.back()->processedRequests != 4) {
		
		newIteration = generateIteration(newIteration);
		OSS->SS.push_back(newIteration);
		OP.printOutputSimState(*newIteration);
	}
}




int main() {
	manageSim();


}