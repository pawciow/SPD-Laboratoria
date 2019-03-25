#include "JohnsonsAlgorithm.h"
#include "NEH.h"

int main()
{
	/*int time;
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
	std::cout << "Czas wykonania zadan po sprawdzeniu wszystkich mozliwosci dla 3 maszyn wynosi: " << time << std::endl;*/

	NEH algorithm;
	NEH alg;
	Machine first, second, third;
	/*first.LoadTimes({ { 1,12 }, { 2,9 }, { 3,6 }, { 4,3 } });
	second.LoadTimes({ {1,11},{2,8}, {3,5}, {4,2} });
	third.LoadTimes({ {1,10},{2,7},{3,4},{4,1} });*/
	
	/*first.LoadTimes({ { 1,4 }, { 2,4 }, { 3,1 }, { 4,5 } });
	second.LoadTimes({ {1,1},{2,3}, {3,2}, {4,1} });
	third.LoadTimes({ {1,4},{2,3},{3,3},{4,3} });*/
	
	first.LoadTimes({ {1,1}, {2,9},{3,7},{4,4} });
	second.LoadTimes({ {1,3},{2,3},{3,8},{4,8} });
	third.LoadTimes({ {1,8},{2,5},{3,6},{4,7} });

	algorithm.LoadData(first);
	algorithm.LoadData(second);
	algorithm.LoadData(third);

	algorithm.DO();
	alg.LoadFromFile("cos.txt");
	int a;
	std::cin >> a;
	return 0;
}
