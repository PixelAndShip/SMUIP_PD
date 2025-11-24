#pragma once
#include "SimState.h"

class SimStates {
public:
	std::vector<SimState*> SS = {};
	float K2wl = 0;
	float K1wl = 0;
	~SimStates() {
		for (int i = 0;i < SS.size();i++) {
			delete SS[i];
		}
	}
};