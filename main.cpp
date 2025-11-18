#include "SimState.h"
#include <vector>
#include "GST.h"


int main(){
	


}

void startSim() {
	SimState* U_4_61 = new SimState(0,0);
	
	generateIteration(U_4_61);




}


//TODO: Before calling this function, must write 
SimState generateIteration(SimState* lastIteration) {
	
	int nextIterN = determineNextIteration(lastIteration);
	int GS_Id = lastIteration->UsedGS.back();
	SimState* nextIteration = new SimState(nextIterN, lastIteration->processedRequestsCount);
	//TODO: 2.generate next iteration 3.also make sure to process first generation
	if (lastIteration->K2.RequestBeingProcessed!=nullptr) {
		if (lastIteration->K2.RequestBeingProcessed->waitTime < nextIterN) {
			nextIteration->K2.RequestBeingProcessed = lastIteration->K2.RequestBeingProcessed;
			delete lastIteration->K2.RequestBeingProcessed;
		}
		else if (lastIteration->K2.RequestBeingProcessed->waitTime == nextIterN) {
			nextIteration->processedRequestsCount += 1;
			delete lastIteration->K2.RequestBeingProcessed;
		}
	}
	else {
		//TODO: Process adding Request to K2 by generating new waittime for it and also processing the queue R1
	}
	if (lastIteration->R1.firstInLine != nullptr) {
		nextIteration->R1 = lastIteration->R1;
		if (nextIteration->K2.RequestBeingProcessed == nullptr) {
			nextIteration->K2.RequestBeingProcessed = lastIteration->R1.firstInLine;
			nextIteration->R1.firstInLine = lastIteration->R1.firstInLine->nextInLine;
			nextIteration->K2.RequestBeingProcessed->nextInLine = nullptr;
		}
		
	}
	if (lastIteration->K1.RequestBeingProcessed != nullptr) {
		if (lastIteration->K1.RequestBeingProcessed->waitTime < nextIterN) {
			nextIteration->K1.RequestBeingProcessed = lastIteration->K1.RequestBeingProcessed;
			delete lastIteration->K1.RequestBeingProcessed;
		}
		else if (lastIteration->K1.RequestBeingProcessed->waitTime == nextIterN) {
			nextIteration->R1.appendToQueue(lastIteration->K1.RequestBeingProcessed);
		}
	}
	if (lastIteration->A1.RequestBeingProcessed != nullptr) {
		if (lastIteration->A1.RequestBeingProcessed->waitTime < nextIterN) {
			nextIteration->A1.RequestBeingProcessed = lastIteration->A1.RequestBeingProcessed;
			delete lastIteration->A1.RequestBeingProcessed;
		}
		else if (lastIteration->A1.RequestBeingProcessed->waitTime == nextIterN) {
			if (nextIteration->K1.RequestBeingProcessed == nullptr) {
				nextIteration->K1.RequestBeingProcessed = lastIteration->A1.RequestBeingProcessed;
				nextIteration->K1.RequestBeingProcessed->generateK1WaitTime();
			}
		}
	}
	else {
		nextIteration->A1.RequestBeingProcessed = new Request();
		nextIteration->A1.RequestBeingProcessed->generateA1WaitTime();
	}
}

int determineNextIteration(SimState* U_4_61) {

	int nextIter = 10000000;
	
	if (U_4_61!=nullptr) {
		SimState previousIteration = *U_4_61;
		if (previousIteration.A1.RequestBeingProcessed->waitTime<nextIter) {
			nextIter = previousIteration.A1.RequestBeingProcessed->waitTime;
		}
		if (previousIteration.K1.RequestBeingProcessed->waitTime < nextIter) {
			nextIter = previousIteration.K1.RequestBeingProcessed->waitTime;
		}
		if (previousIteration.R1.firstInLine->waitTime < nextIter) {
			nextIter = previousIteration.R1.firstInLine->waitTime;
		}
		if (previousIteration.K2.RequestBeingProcessed->waitTime < nextIter) {
			nextIter = previousIteration.K2.RequestBeingProcessed->waitTime;
		}
	}
	return nextIter;
}