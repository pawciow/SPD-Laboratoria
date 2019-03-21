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
private:
	void StepOne();
	void StepTwo();
	std::pair<int,int> StepThree();
	void StepFour();
	std::vector<Machine> _machines;
	std::vector<std::pair<int, int>> _sumForTask; /* Pary w postaci : nr zadania, suma dla tego zadanka*/
	void printSumForTask();

};

