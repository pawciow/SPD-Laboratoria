#include "pch.h"
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <initializer_list>
#include <map>
#include <algorithm>
#include <utility>

using timesForJobs = std::list<std::pair<const int, const int>>; /*Nazwa niefortunna, trzeba zmieni� XD
																	Generalnie chodzi o pary:(Numer zadania, Czas wykonania)*/
class Machine
{
public:
	Machine() = default;
	void LoadTimes(timesForJobs times);
	timesForJobs _timesForJobs;

	std::pair<const int, const int> findMinTime();
	void deleteTask(std::pair<int, int> taskToDelete);
};

class JohnsonsTwoMachineAlgorithm
{
public:
	JohnsonsTwoMachineAlgorithm() = default;
	enum class MachineNumber { First, Second };
	void LoadTimesForMachines(MachineNumber whichMachine, timesForJobs times);
	std::list<const int> DO();
	int countTime(std::list<const int> jobOrder);
	int timeForSecondMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine);
private:
	Machine _firstMachine;
	Machine _secondMachine;
};

void Machine::LoadTimes(timesForJobs times)
{
	for (auto & e : times)
	{
		_timesForJobs.push_back(e);
	}
}

void JohnsonsTwoMachineAlgorithm::LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber whichMachine, timesForJobs times)
{
	if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::First)
	{
		_firstMachine.LoadTimes(times);
	}
	else if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::Second)
	{
		_secondMachine.LoadTimes(times);
	}
	else
	{
		std::cerr << "Wrong machine number!" << std::endl;
		exit(1);
	}
}

std::pair<const int, const int> Machine::findMinTime()
{
	auto min = std::make_pair(0, 999);
	std::list<std::pair<const int, const int>>::iterator it;
	for (it = _timesForJobs.begin(); it != _timesForJobs.end(); ++it)
	{
		if (std::get<1>(*it) < min.second)
		{
			min = *it;
		}
	}

	return min;
}

void Machine::deleteTask(std::pair<int, int> taskToDelete)
{
	std::list<std::pair<const int, const int>>::iterator it = _timesForJobs.begin();

	for (it = _timesForJobs.begin(); it != _timesForJobs.end(); ++it)
	{
		if (std::get<0>(*it) == taskToDelete.first)
		{
			it = _timesForJobs.erase(it);
			break;
		}

	}
}

std::list<const int> JohnsonsTwoMachineAlgorithm::DO()
{
	Machine tmpFirstMachine = _firstMachine;
	Machine tmpSecondMachine = _secondMachine;
	std::list<std::pair<const int, const int>> jobOptimalOrder1;
	std::list<std::pair<const int, const int>> jobOptimalOrder2;

	std::list<const int> finalJobOrder;
	std::list<const int>::iterator it;

	std::pair<int, int> lowestFromFirst;
	std::pair<int, int> lowestFromSecond;

	while (tmpFirstMachine._timesForJobs.empty() == false && tmpSecondMachine._timesForJobs.empty() == false)
	{
		lowestFromFirst = tmpFirstMachine.findMinTime();
		lowestFromSecond = tmpSecondMachine.findMinTime();

		if (lowestFromFirst.second < lowestFromSecond.second)
		{
			jobOptimalOrder1.push_back(lowestFromFirst);

			tmpFirstMachine.deleteTask(lowestFromFirst);
			tmpSecondMachine.deleteTask(lowestFromFirst);
		}
		else
		{
			jobOptimalOrder2.push_front(lowestFromSecond);

			tmpFirstMachine.deleteTask(lowestFromSecond);
			tmpSecondMachine.deleteTask(lowestFromSecond);
		}
	}

	while (jobOptimalOrder1.empty() == false)
	{
		finalJobOrder.push_back(jobOptimalOrder1.front().first);
		jobOptimalOrder1.pop_front();
	}
	while (jobOptimalOrder2.empty() == false)
	{
		finalJobOrder.push_back(jobOptimalOrder2.front().first);
		jobOptimalOrder2.pop_front();
	}

	std::cout << "Kolejnosc wykonywania podanych zadan wedlog reguly Johnson'a to:";

	for (it = finalJobOrder.begin(); it != finalJobOrder.end(); ++it)
	{
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	return finalJobOrder;
}

int JohnsonsTwoMachineAlgorithm::timeForSecondMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine)
{
	int gap = timeForFirstMachine - timeForSecondMachine;
	if (gap > 0) return gap;
	else return 0;
}

int JohnsonsTwoMachineAlgorithm::countTime(std::list<const int> jobOrder)
{
	int timeForFirstMachine = 0;
	int timeForSecondMachine = 0;
	int sumTimesForFirstMachine = 0;
	int timeGap;
	int i = 0;

	/* Zamiana list na wektory */
	std::vector<std::pair<const int, const int>> firstMachineTimesVector;
	std::vector<std::pair<const int, const int>> secondMachineTimesVector;
	std::transform(_firstMachine._timesForJobs.begin(), _firstMachine._timesForJobs.end(), firstMachineTimesVector.begin(), std::back_inserter(firstMachineTimesVector));
	std::transform(_firstMachine._timesForJobs.begin(), _secondMachine._timesForJobs.end(), secondMachineTimesVector.begin(), std::back_inserter(secondMachineTimesVector));

	std::list<std::pair<const int, const int>>::iterator it;
	std::list<const int>::iterator itJobOrder;

	it = _firstMachine._timesForJobs.begin();

	for (itJobOrder = jobOrder.begin(); itJobOrder != jobOrder.end(); ++itJobOrder)
	{
		timeForFirstMachine += firstMachineTimesVector[*itJobOrder].second;

		if ((timeGap = timeForSecondMachineHaveToWait(timeForFirstMachine, timeForSecondMachine)) != 0)
		{
			timeForSecondMachine += secondMachineTimesVector[*itJobOrder].second + timeGap;
		}
		else
		{
			timeForSecondMachine += secondMachineTimesVector[*itJobOrder].second;
		}
	}
	if (timeForFirstMachine >= timeForSecondMachine) return timeForFirstMachine;
	else return timeForSecondMachine;
}

int main()
{
	JohnsonsTwoMachineAlgorithm exampleAlgorithm;
	timesForJobs exampleTimes{ {1,1},{2,3},{3,5}, {4,7}, {5,9} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::First, exampleTimes);
	timesForJobs exampleTimes2{ {1,2}, {2,4}, {3,6}, {4,8}, {5,10} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::Second, exampleTimes2);
	exampleAlgorithm.countTime(exampleAlgorithm.DO());
	return 0;
}