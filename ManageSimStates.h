#pragma once
#include "SimStates.h"
#include "GST.h"
#include "Output.h"
class ManageSimStates {
public:
	Output OP = Output();
	GST GSTable = GST();
	SimStates OSS = SimStates();
	SimState* firstIteration = new SimState();
	SimState* newIteration  = nullptr;

	ManageSimStates() {
		firstIteration->a1.savedA1WaitTime = 2;
		firstIteration->a1.generatedA1WaitTime = 2;
		firstIteration->a1.stringA1WT += "2";
		firstIteration->k1.stringK1 += "n";
		firstIteration->r1.stringR1 += "0";
		firstIteration->k2.stringK2 += "n";
		firstIteration->k2.stringK2WT += "n";
		firstIteration->k1.stringK1WT += "n";
		GSTable.currentNumberId += 1;
		firstIteration->usedGS = "1";

		OSS.SS.push_back(firstIteration);
		newIteration = generateIteration(firstIteration);
		OSS.SS.push_back(newIteration);
	}

	void Simulate_U_4_61() {
		OP.launchPrint();
		//OSS.SS.back()->processedRequests != 4
		while (OSS.SS.back()->processedRequests != 4) {

			newIteration = generateIteration(newIteration);
			OSS.SS.push_back(newIteration);
			
		}
		
	
		OP.printToExcelCSV(OSS.SS, "U_4_61.csv");
		OP.printOutputSimStates(&OSS, GSTable);
	}
	


	void generateWaitTime(SimState* nextIteration, int type, int currentID) {
		GSTable.currentNumberId += 1;
		nextIteration->usedGS += std::to_string(GSTable.currentNumberId) + " ";
		if ((GSTable.currentNumberId - 1) < GSTable.randomNumbers.size()) {
			float randomNumber = GSTable.randomNumbers[GSTable.currentNumberId - 1];
			switch (type) {
			case 1:
				if (randomNumber <= 1.00) {
					nextIteration->a1.generatedA1WaitTime = currentID + 4;
				}
				if (randomNumber <= 0.66) {
					nextIteration->a1.generatedA1WaitTime = currentID + 3;
				}
				if (randomNumber <= 0.33) {
					nextIteration->a1.generatedA1WaitTime = currentID + 2;
				}
				nextIteration->a1.savedA1WaitTime = nextIteration->a1.generatedA1WaitTime;
				break;
			case 2:
				if (randomNumber <= 1.00) {
					nextIteration->k1.generatedK1WaitTime = currentID + 4;
				}
				if (randomNumber <= 0.66) {
					nextIteration->k1.generatedK1WaitTime = currentID + 3;
				}
				if (randomNumber <= 0.33) {
					nextIteration->k1.generatedK1WaitTime = currentID + 2;
				}
				nextIteration->k1.savedK1WaitTime = nextIteration->k1.generatedK1WaitTime;
				break;
			case 3:
				if (randomNumber <= 1.0) {
					nextIteration->k2.generatedK2WaitTime = currentID + 8;
				}
				if (randomNumber <= 0.8) {
					nextIteration->k2.generatedK2WaitTime = currentID + 7;
				}
				if (randomNumber <= 0.6) {
					nextIteration->k2.generatedK2WaitTime = currentID + 6;
				}
				if (randomNumber <= 0.4) {
					nextIteration->k2.generatedK2WaitTime = currentID + 5;
				}
				if (randomNumber <= 0.2) {
					nextIteration->k2.generatedK2WaitTime = currentID + 4;
				}
				nextIteration->k2.savedK2WaitTime = nextIteration->k2.generatedK2WaitTime;
				break;
			}


		}


	}
	int getNextIterationNumber(SimState* lastIteration) {
		int nums[] = { lastIteration->a1.savedA1WaitTime,lastIteration->k1.savedK1WaitTime,lastIteration->k2.savedK2WaitTime };

		int n = sizeof(nums) / sizeof(nums[0]);

		int smallestNextIterationID = *std::max_element(nums, nums + n);
		
		for (int num : nums) {
			if (num < smallestNextIterationID && num != 0) {
				smallestNextIterationID = num;
			}
		}
		
		return smallestNextIterationID;
	}
	SimState* generateIteration(SimState* lastIteration) {

		SimState* newIteration = new SimState(lastIteration->a1.savedA1WaitTime, lastIteration->k1.savedK1WaitTime, lastIteration->k2.savedK2WaitTime, lastIteration->k1.processingK1, lastIteration->k2.processingK2, lastIteration->processedRequests);
		int smallestNextIterationID = getNextIterationNumber(lastIteration);
		newIteration->currentTime = smallestNextIterationID;
		manageNextIteration(lastIteration, newIteration, smallestNextIterationID);
		return newIteration;
	}
	void manageNextIteration(SimState* lastIteration, SimState* nextIteration, int sNIID) {
		nextIteration->r1.stR1 = lastIteration->r1.stR1;
		if (lastIteration->k2.savedK2WaitTime != sNIID) {
			nextIteration->k2.savedK2WaitTime = lastIteration->k2.savedK2WaitTime;
			if (lastIteration->k2.processingK2 == true) {
				nextIteration->k2.processingK2 = true;
			}
		}

		else if (lastIteration->k2.savedK2WaitTime == sNIID) {



			if (lastIteration->k2.processingK2 == true) {
				nextIteration->processedRequests += 1;
				nextIteration->k2.processingK2 = false;
				
				nextIteration->k2.savedK2WaitTime = 0;



				nextIteration->usedGS += "n";
				nextIteration->a1.stringA1WT += "n";
				nextIteration->k1.stringK1 += "n";
				nextIteration->k1.stringK1WT += "n";
				nextIteration->r1.stringR1 += std::to_string(nextIteration->r1.stR1);
				nextIteration->k2.stringK2 += "0";
				nextIteration->k2.stringK2WT += "n";

			}
		}


		if (nextIteration->k2.processingK2 == false) {

			if (nextIteration->r1.stR1 != 0) {
				nextIteration->r1.stR1 -= 1;
				
				generateWaitTime(nextIteration, 3, sNIID);
				nextIteration->k2.savedK2WaitTime = nextIteration->k2.generatedK2WaitTime;
				nextIteration->k2.processingK2 = true;


				nextIteration->a1.stringA1WT += "n";

				nextIteration->k1.stringK1 += "n";
				nextIteration->k1.stringK1WT += "n";
				nextIteration->r1.stringR1 += std::to_string(nextIteration->r1.stR1);
				nextIteration->k2.stringK2 += "1";
				nextIteration->k2.stringK2WT += std::to_string(nextIteration->k2.generatedK2WaitTime);

			}
		}

		if (lastIteration->k1.savedK1WaitTime != sNIID) {
			nextIteration->k1.savedK1WaitTime = lastIteration->k1.savedK1WaitTime;
			if (lastIteration->k1.processingK1 == true) {
				nextIteration->k1.processingK1 = true;

			}



		}
		else if (lastIteration->k1.savedK1WaitTime == sNIID) {
			nextIteration->k1.processingK1 = false;
			
			nextIteration->k1.savedK1WaitTime = 0;


			nextIteration->a1.stringA1WT += "n";
			nextIteration->usedGS += "n";
			nextIteration->k1.stringK1 += "0";
			nextIteration->k1.stringK1WT += "n";
			nextIteration->r1.stringR1 += std::to_string(nextIteration->r1.stR1);
			nextIteration->k2.stringK2 += "n";
			nextIteration->k2.stringK2WT += "n";

			if (nextIteration->k2.processingK2 == false) {
				nextIteration->k2.processingK2 = true;
				
				generateWaitTime(nextIteration, 3, sNIID);

				nextIteration->k2.savedK2WaitTime = nextIteration->k2.generatedK2WaitTime;
				


				nextIteration->a1.stringA1WT += "n";

				nextIteration->k1.stringK1 += "n";
				nextIteration->k1.stringK1WT += "n";
				nextIteration->r1.stringR1 += std::to_string(nextIteration->r1.stR1 + 1);
				nextIteration->k2.stringK2 += "1";
				nextIteration->k2.stringK2WT += std::to_string(nextIteration->k2.generatedK2WaitTime);
			}
			else {
				nextIteration->r1.stR1 += 1;
				nextIteration->r1.stringR1 = std::to_string(nextIteration->r1.stR1);
			}


		}

		if (lastIteration->a1.savedA1WaitTime != sNIID) {
			nextIteration->a1.savedA1WaitTime = lastIteration->a1.savedA1WaitTime;

		}
		else if (lastIteration->a1.savedA1WaitTime == sNIID) {
			nextIteration->a1.savedA1WaitTime = 0;
			if (nextIteration->k1.processingK1 == false) {
				nextIteration->k1.processingK1 = true;
				nextIteration->usedGS = "";
				generateWaitTime(nextIteration, 2, sNIID);

				nextIteration->k1.savedK1WaitTime = nextIteration->k1.generatedK1WaitTime;

				nextIteration->k1.stringK1 += "1";
				nextIteration->k1.stringK1WT += std::to_string(nextIteration->k1.generatedK1WaitTime);



			}
			else {
				nextIteration->k1.stringK1 += "n";
				nextIteration->k1.stringK1WT += "n";
			}
			generateWaitTime(nextIteration, 1, sNIID);
			nextIteration->a1.savedA1WaitTime = nextIteration->a1.generatedA1WaitTime;

			nextIteration->a1.stringA1WT += std::to_string(nextIteration->a1.generatedA1WaitTime);

			nextIteration->r1.stringR1 += std::to_string(nextIteration->r1.stR1);
			nextIteration->k2.stringK2 += "n";
			nextIteration->k2.stringK2WT += "n";

		}
	}
};