#pragma once
#include "SimState.h"
#include "R1QueueState.h"
class SimStates {
public:
	std::vector<SimState*> SS = {};
	float K2wl = 0;
	float K1wl = 0;
	float totalR1 = 0;
	float R1in = 0;
	float R1out = 0;
	float totalR1WT = 0;
	std::vector<int> R1WTstarts = {};

	R1QueueState* firstInLine = nullptr;

	~SimStates() {
		for (int i = 0;i < SS.size();i++) {
			delete SS[i];
		}
	}

	R1QueueState* getLastR1QueueState() {
		R1QueueState* currentQueueState = firstInLine;
		while (currentQueueState != nullptr) {
			currentQueueState = currentQueueState->nextR1QueueState;
		}
		return currentQueueState;
	}

	void increaseAllR1QueueStateWT() {
		R1QueueState* currentQueueState = firstInLine;
		while (currentQueueState != nullptr) {
			currentQueueState->WT += 1;
			currentQueueState = currentQueueState->nextR1QueueState;
		}
	}

	int releaseFirstInLine() {
		
		R1QueueState* toDeleteFirstInLine = firstInLine;
		int wt = toDeleteFirstInLine->WT-1;
		firstInLine = toDeleteFirstInLine->nextR1QueueState;
		delete toDeleteFirstInLine;
		return wt;
	}
};