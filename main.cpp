#include "ManageSimStates.h"
#include "Output.h"


int main() {
	ManageSimStates MSS = ManageSimStates();
	MSS.OP.launchPrint();
	int maxProcR = 4;
	std::cout << "Enter max processed requests count:";
	std::cin >> maxProcR;
	std::cout << std::endl;
	MSS.Simulate_U_4_61(maxProcR);
}


