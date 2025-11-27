#pragma once
class R1QueueState {
public:
	int WT = 0;
	R1QueueState* nextR1QueueState = nullptr;
	~R1QueueState() {
		delete nextR1QueueState;
	}
};