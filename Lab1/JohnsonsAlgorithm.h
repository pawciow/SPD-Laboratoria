#pragma once
#include "Machin.h"

class Algorithm : public ILoadable
{
public:
	Algorithm() = default;
	enum class MachineNumber { First, Second, Third };
	void LoadTimesForMachines(MachineNumber whichMachine, timesForJobs times);
	std::list<int> JohnsonsTwoMachineAlgorithm();
	std::list<int> JohnsonsThreeMachineAlgorithm();
	int countTime(std::list<int> jobOrder, bool threeMachines);
	int timeForSecondMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine);
	int permutations(bool threeMachines);

	virtual void LoadDataFromFile(std::string fileName);
private:
	Machine _firstMachine;
	Machine _secondMachine;
	Machine _thirdMachine;
};