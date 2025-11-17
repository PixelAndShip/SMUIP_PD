#include "SimState.h"
#include <vector>


int main(){
	


}

void startSim() {
	SimState SS(0, 0);
	std::vector<SimState> U_4_61 = {SS};
	generateIteration(&U_4_61);

}

SimState generateIteration(std::vector<SimState>* U_4_61) {
	SimState lastIteration = U_4_61->back();
	int nextIterN = determineNextIteration(U_4_61);
	SimState nextIteration(nextIterN, lastIteration.processedRequestsCount);
	//TODO: 1.get info on which processes take priority upon completion 2.generate next iteration 3.also make sure to process first generation

}

int determineNextIteration(std::vector<SimState>* U_4_61) {

	int nextIter = 10000000;
	
	if (!U_4_61->empty()) {
		SimState previousIteration = U_4_61->back();
		if (previousIteration.A1.firstInLine->waitTime<nextIter) {
			nextIter = previousIteration.A1.firstInLine->waitTime;
		}
		if (previousIteration.K1.RequestBeingProcessed.waitTime < nextIter) {
			nextIter = previousIteration.K1.RequestBeingProcessed.waitTime;
		}
		if (previousIteration.R1.firstInLine->waitTime < nextIter) {
			nextIter = previousIteration.R1.firstInLine->waitTime;
		}
		if (previousIteration.K2.RequestBeingProcessed.waitTime < nextIter) {
			nextIter = previousIteration.K2.RequestBeingProcessed.waitTime;
		}
	}
	return nextIter;
}