#pragma once
#include "Machin.h"
class NEH
{
public:
	NEH() = default;
	virtual ~NEH() = default;
	void DO();
	void LoadData(const Machine & machine)
	{
		_machines.push_back(machine);
	}
	bool LoadFromFile(std::string fileName);
	int countTime(std::list<int> jobOrder);
	int timeForSecondMachineHaveToWait(std::vector<int> timesForMachines, int number);
private:
	void StepOne();
	void StepTwo();
	const std::pair<int, int> & StepThree();
	void StepFour();
	std::vector<Machine> _machines;
	std::vector<std::pair<int, int>> _sumForTask; /* Pary w postaci : nr zadania, suma dla tego zadanka*/
	void printSumForTask();
	std::vector<std::pair<int,int>> optimalTaskList;
	void countTimeForList(std::vector<std::pair<int, int>> taskList)
	{
		std::cout << "TMP DEBUG";
	};
};
