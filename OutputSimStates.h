#pragma once
#include "OutputSimState.h"

class OutputSimStates {
public:
	std::vector<OutputSimState*> SS = {};

	~OutputSimStates() {
		for (int i = 0;i < SS.size();i++) {
			delete SS[i];
		}
	}
};