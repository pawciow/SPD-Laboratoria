#pragma once
#include "Machin.h"
class NEH
{
public:
	NEH() = default;
	virtual ~NEH() = default;
	void DO();
private:
	void StepOne();
	void StepTwo();
	void StepThree();
	void StepFour();
	std::vector<Machine> _machines;
	std::vector<std::pair<const int, int>> _sumForTask;
};

