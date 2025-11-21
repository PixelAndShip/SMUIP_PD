#pragma once
#include "SimState.h"

class SimStates {
public:
	std::vector<SimState*> SS = {};

	~SimStates() {
		for (int i = 0;i < SS.size();i++) {
			delete SS[i];
		}
	}
};