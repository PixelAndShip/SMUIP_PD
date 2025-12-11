#pragma once
// this class is used to count each requests waiting time in the queue R1, the queue is structured
// in a linked list, as to easily adhere to the FIFO principal
class R1QueueState {
public:
	int WT = 0; // requests wait time
	R1QueueState* nextR1QueueState = nullptr; 
	

	R1QueueState(int wt) {
		WT = wt;
	}
};