#pragma once
#include "SimState.h"
#include "R1QueueState.h"
#include <iostream>
class SimStates {
public:
	std::vector<SimState*> SS = {};
	float K2wl = 0;
	float K1wl = 0;
	float totalR1 = 0;
	float R1in = 0;
	float R1out = 0;
	float totalR1WT = 0;
	

	R1QueueState* firstInLine = nullptr;

	~SimStates() {
		for (auto* state : SS) delete state;
		SS.clear();

		R1QueueState* current = firstInLine;
		while (current != nullptr) {
			R1QueueState* next = current->nextR1QueueState;
			delete current;
			current = next;
		}
		firstInLine = nullptr;
	}
	
	void addNewR1QueueState(int wt) {
		if (firstInLine == nullptr ) {  
			firstInLine = new R1QueueState(wt);
			return;
		}
		

		R1QueueState* currentQueueState = firstInLine;
		
		while (currentQueueState != nullptr) {
			if (currentQueueState->nextR1QueueState == nullptr) {
				currentQueueState->nextR1QueueState = new R1QueueState(wt);
				break;
			}
			else {
				currentQueueState = currentQueueState->nextR1QueueState;
			}
		}
	}
	



	int releaseFirstInLine() {
		if (firstInLine == nullptr ) {
			
			return 0;
		}
		R1QueueState* toDeleteFirstInLine = firstInLine;
		int wt = toDeleteFirstInLine->WT;
		firstInLine = toDeleteFirstInLine->nextR1QueueState;
		delete toDeleteFirstInLine;
		return wt;
	}
};