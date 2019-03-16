<<<<<<< HEAD
#include "JohnsonsAlgorithm.h"
#include "NEH.h"

int main()
{
	int time;
	Algorithm exampleAlgorithm;
	timesForJobs exampleTimes{ {1,1},{2,2},{3,3}, {4,4}, {5,5} };
	exampleAlgorithm.LoadTimesForMachines(Algorithm::MachineNumber::First, exampleTimes);
	timesForJobs exampleTimes2{ {1,2}, {2,3}, {3,4}, {4,5}, {5,6} };
	exampleAlgorithm.LoadTimesForMachines(Algorithm::MachineNumber::Second, exampleTimes2);
	timesForJobs exampleTimes3{ {1,3}, {2,2}, {3,1}, {4,4}, {5,5} };
	exampleAlgorithm.LoadTimesForMachines(Algorithm::MachineNumber::Third, exampleTimes3);

	time = exampleAlgorithm.countTime(exampleAlgorithm.JohnsonsTwoMachineAlgorithm(), false);
	std::cout << "Czas wykonania zadan wedlog reguly Johnson'a wynosi dla 2 maszyn: " << time << std::endl;
	time = exampleAlgorithm.permutations(false);
	std::cout << "Czas wykonania zadan po sprawdzeniu wszystkich mozliwosci dla 2 maszyn wynosi: " << time << std::endl << std::endl;

	time = exampleAlgorithm.countTime(exampleAlgorithm.JohnsonsThreeMachineAlgorithm(), true);
	std::cout << "Czas wykonania zadan wedlog reguly Johnson'a wynosi dla 3 maszyn: " << time << std::endl;
	time = exampleAlgorithm.permutations(true);
	std::cout << "Czas wykonania zadan po sprawdzeniu wszystkich mozliwosci dla 3 maszyn wynosi: " << time << std::endl;

	return 0;
}