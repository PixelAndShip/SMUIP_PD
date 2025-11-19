#include "OutputSimStates.h"
#include <string>
#include <vector>
#include "GST.h"
#include "Output.h"

GST GSTable;
Output OP;





void generateWaitTime(OutputSimState* nextIteration, int type) {
	GSTable.currentNumberId += 1;
	nextIteration->usedGS = GSTable.currentNumberId;
	if ((GSTable.currentNumberId - 1) < GSTable.randomNumbers.size()) {
		switch (type) {
		case 1:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.00) {
				nextIteration->generatedA1WaitTime = GSTable.currentNumberId+ 4;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.66) {
				nextIteration->generatedA1WaitTime = GSTable.currentNumberId + 3;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.33) {
				nextIteration->generatedA1WaitTime = GSTable.currentNumberId + 2;
			}
			nextIteration->savedA1WaitTime = nextIteration->generatedA1WaitTime;
			break;
		case 2:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.00) {
				nextIteration->generatedK1WaitTime = GSTable.currentNumberId + 4;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.66) {
				nextIteration->generatedK1WaitTime = GSTable.currentNumberId + 3;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.33) {
				nextIteration->generatedK1WaitTime = GSTable.currentNumberId + 2;
			}
			nextIteration->savedK1WaitTime = nextIteration->generatedK1WaitTime;
			break;
		case 3:
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 1.0) {
				nextIteration->generatedK2WaitTime = GSTable.currentNumberId + 8;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.8) {
				nextIteration->generatedK2WaitTime = GSTable.currentNumberId + 7;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.6) {
				nextIteration->generatedK2WaitTime = GSTable.currentNumberId + 6;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.4) {
				nextIteration->generatedK2WaitTime = GSTable.currentNumberId + 5;
			}
			if (GSTable.randomNumbers[GSTable.currentNumberId - 1] <= 0.2) {
				nextIteration->generatedK2WaitTime = GSTable.currentNumberId + 4;
			}
			nextIteration->savedK2WaitTime = nextIteration->generatedK2WaitTime;
			break;
		}


	}


}




void manageNextIteration(OutputSimState* lastIteration, OutputSimState* nextIteration,int sNIID){ 
	if (lastIteration->savedK2WaitTime != sNIID) {
		nextIteration->savedK2WaitTime = lastIteration->savedK2WaitTime;
		if (lastIteration->processingK2 == true) {
			nextIteration->processingK2 = true;
		}
		
	}
	else if (lastIteration->savedK2WaitTime == sNIID) {
		if (lastIteration->processingK2 == true) {
			nextIteration->processedRequests += 1;
			nextIteration->processingK2 = false;
			nextIteration->K2 = 0;
			nextIteration->savedK2WaitTime = 0;
			return;
		}
	}
	
	nextIteration->R1 = lastIteration->R1;
	if (nextIteration->processingK2 == false) {

		if (lastIteration->R1 != 0) {
			nextIteration->R1 -= 1;
			nextIteration->K2 = 1;
			generateWaitTime(nextIteration, 3);
			nextIteration->savedK2WaitTime = nextIteration->generatedK2WaitTime;
			nextIteration->processingK2 = true;
			return;
		}
	}
	
	if (lastIteration->savedK1WaitTime != sNIID) {
		nextIteration->savedK1WaitTime = lastIteration->savedK1WaitTime;
		if (lastIteration->processingK1 == true) {
			nextIteration->processingK1 = true;
		}
		

	}
	else if (lastIteration->savedK1WaitTime==sNIID) {
		nextIteration->processingK1 = false;
		nextIteration->K1 = 0;
		nextIteration->savedK1WaitTime = 0;
		if (nextIteration->processingK2 == false) {
			nextIteration->processingK2 = true;
			generateWaitTime(nextIteration, 3);
			nextIteration->savedK2WaitTime = nextIteration->generatedK2WaitTime;
			nextIteration->K2 = 1;
			return;
		}
		else {
			nextIteration->R1 += 1;
		}
	}

	if (lastIteration->savedA1WaitTime != sNIID) {
		nextIteration->savedA1WaitTime = lastIteration->savedA1WaitTime;
	}
	else if (lastIteration->savedA1WaitTime == sNIID) {
		nextIteration->savedA1WaitTime = 0;
		if (nextIteration->processingK1 == false) {
			nextIteration->processingK1 = true;
			nextIteration->K1 = 1;
			generateWaitTime(nextIteration, 2);
			nextIteration->savedK1WaitTime = nextIteration->generatedK1WaitTime;
			
		}
		generateWaitTime(nextIteration, 1);
		nextIteration->savedA1WaitTime = nextIteration->generatedA1WaitTime;
		return;
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

	OutputSimState* newIteration = new OutputSimState(lastIteration->savedA1WaitTime,lastIteration->savedK1WaitTime,lastIteration->savedK2WaitTime,lastIteration->processedRequests);
	int smallestNextIterationID = getNextIterationNumber(lastIteration);
	newIteration->currentTime = smallestNextIterationID;
	manageNextIteration(lastIteration, newIteration, smallestNextIterationID);
	return newIteration;
}

void manageSim() {
	OutputSimStates* OSS = new OutputSimStates();
	OutputSimState* firstIteration = new OutputSimState();
	firstIteration->savedA1WaitTime = 2;
	OP.printOutputSimState(*firstIteration, GSTable);
	OutputSimState* newIteration = generateIteration(firstIteration);
	OP.printOutputSimState(*newIteration,GSTable);
	OSS->SS.push_back(newIteration);
	while (OSS->SS.back()->processedRequests != 4) {
		
		newIteration = generateIteration(newIteration);
		OSS->SS.push_back(newIteration);
		OP.printOutputSimState(*newIteration,GSTable);
	}
}




int main() {
	manageSim();


}