#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <initializer_list>
#include <map>
#include <algorithm>
#include <iterator>

using timesForJobs = std::list<std::pair<const int, const int>>;

class Machine
{
public:
	Machine() = default;
	void LoadTimes(timesForJobs times);
	timesForJobs _timesForJobs;

	std::pair<const int, const int> findMinTime();
	void deleteTask(std::pair<int, int> taskToDelete);
};

class Algorithm
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
private:
	Machine _firstMachine;
	Machine _secondMachine;
	Machine _thirdMachine;
};

void Machine::LoadTimes(timesForJobs times)
{
	for (auto & e : times)
	{
		_timesForJobs.push_back(e);
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

void Algorithm::LoadTimesForMachines(Algorithm::MachineNumber whichMachine, timesForJobs times)
{
	if (whichMachine == Algorithm::MachineNumber::First)
	{
		_firstMachine.LoadTimes(times);
	}
	else if (whichMachine == Algorithm::MachineNumber::Second)
	{
		_secondMachine.LoadTimes(times);
	}
	else if (whichMachine == Algorithm::MachineNumber::Third)
	{
		_thirdMachine.LoadTimes(times);
	}
	else
	{
		std::cerr << "Wrong machine number!" << std::endl;
		exit(1);
	}
}

std::list<int> Algorithm::JohnsonsTwoMachineAlgorithm()
{
	Machine tmpFirstMachine = _firstMachine;
	Machine tmpSecondMachine = _secondMachine;
	std::list<std::pair<const int, const int>> jobOptimalOrder1;
	std::list<std::pair<const int, const int>> jobOptimalOrder2;

	std::list<int> finalJobOrder;
	std::list<int>::iterator it;

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

	std::cout << "Kolejnosc wykonywania podanych zadan wedlog reguly Johnson'a dla 2 maszyn to:";

	for (it = finalJobOrder.begin(); it != finalJobOrder.end(); ++it)
	{
		std::cout << " " << *it;
	}
	std::cout << std::endl;

	return finalJobOrder;
}

std::list<int> Algorithm::JohnsonsThreeMachineAlgorithm()
{
	Machine tmpFirstVirtualMachine;
	Machine tmpSecondVirtualMachine;

	std::vector<std::pair<int, int>> firstMachineTimesVector{ std::begin(_firstMachine._timesForJobs), std::end(_firstMachine._timesForJobs) };
	std::vector<std::pair<int, int>> secondMachineTimesVector{ std::begin(_secondMachine._timesForJobs), std::end(_secondMachine._timesForJobs) };
	std::vector<std::pair<int, int>> thirdMachineTimesVector{ std::begin(_thirdMachine._timesForJobs), std::end(_thirdMachine._timesForJobs) };
	std::list<std::pair<const int, const int>> firstVirtualMachineTimes;
	std::list<std::pair<const int, const int>> secondVirtualMachineTimes;
	std::pair<int, int> tmpPair;
	std::list<std::pair<const int, const int>> jobOptimalOrder1;
	std::list<std::pair<const int, const int>> jobOptimalOrder2;

	std::list<int> finalJobOrder;
	std::list<std::pair<const int, const int>>::iterator it;
	std::list<int>::iterator itJobOrder;

	std::pair<int, int> lowestFromFirst;
	std::pair<int, int> lowestFromSecond;

	int i = 0;

	for (it = _firstMachine._timesForJobs.begin(); it != _firstMachine._timesForJobs.end(); ++it)
	{
		tmpPair.first = firstMachineTimesVector[i].first;
		tmpPair.second = firstMachineTimesVector[i].second + secondMachineTimesVector[i].second;
		firstVirtualMachineTimes.push_back(tmpPair);

		tmpPair.first = firstMachineTimesVector[i].first;
		tmpPair.second = secondMachineTimesVector[i].second + thirdMachineTimesVector[i].second;
		secondVirtualMachineTimes.push_back(tmpPair);
		i++;
	}

	tmpFirstVirtualMachine._timesForJobs = firstVirtualMachineTimes;
	tmpSecondVirtualMachine._timesForJobs = secondVirtualMachineTimes;

	while (tmpFirstVirtualMachine._timesForJobs.empty() == false && tmpSecondVirtualMachine._timesForJobs.empty() == false)
	{
		lowestFromFirst = tmpFirstVirtualMachine.findMinTime();
		lowestFromSecond = tmpSecondVirtualMachine.findMinTime();

		if (lowestFromFirst.second < lowestFromSecond.second)
		{
			jobOptimalOrder1.push_back(lowestFromFirst);

			tmpFirstVirtualMachine.deleteTask(lowestFromFirst);
			tmpSecondVirtualMachine.deleteTask(lowestFromFirst);
		}
		else
		{
			jobOptimalOrder2.push_front(lowestFromSecond);

			tmpFirstVirtualMachine.deleteTask(lowestFromSecond);
			tmpSecondVirtualMachine.deleteTask(lowestFromSecond);
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

	std::cout << "Kolejnosc wykonywania podanych zadan wedlog reguly Johnson'a dla 3 maszyn to:";

	for (itJobOrder = finalJobOrder.begin(); itJobOrder != finalJobOrder.end(); ++itJobOrder)
	{
		std::cout << " " << *itJobOrder;
	}
	std::cout << std::endl;

	return finalJobOrder;
}

int Algorithm::timeForSecondMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine)
{
	int gap = timeForFirstMachine - timeForSecondMachine;
	if (gap > 0) return gap;
	else return 0;
}

int Algorithm::countTime(std::list<int> jobOrder, bool threeMachines)
{
	int timeForFirstMachine = 0;
	int timeForSecondMachine = 0;
	int timeForThirdMachine = 0;

	int timeGap = 0;
	int i = 0;

	std::vector<std::pair<const int, const int>> firstMachineTimesVector{ std::begin(_firstMachine._timesForJobs), std::end(_firstMachine._timesForJobs) };
	std::vector<std::pair<const int, const int>> secondMachineTimesVector{ std::begin(_secondMachine._timesForJobs), std::end(_secondMachine._timesForJobs) };
	std::vector<std::pair<const int, const int>> thirdMachineTimesVector{ std::begin(_thirdMachine._timesForJobs), std::end(_thirdMachine._timesForJobs) };

	std::list<int>::iterator itJobOrder;

	for (itJobOrder = jobOrder.begin(); itJobOrder != jobOrder.end(); ++itJobOrder)
	{
		timeForFirstMachine += firstMachineTimesVector[*itJobOrder - 1].second;
		timeGap = timeForSecondMachineHaveToWait(timeForFirstMachine, timeForSecondMachine);
		if (timeGap != 0)
		{
			timeForSecondMachine += secondMachineTimesVector[*itJobOrder - 1].second + timeGap;
		}
		else
		{
			timeForSecondMachine += secondMachineTimesVector[*itJobOrder - 1].second;
		}

		if (threeMachines == true)
		{
			timeGap = timeForSecondMachineHaveToWait(timeForSecondMachine, timeForThirdMachine);
			if (timeGap != 0)
			{
				timeForThirdMachine += thirdMachineTimesVector[*itJobOrder - 1].second + timeGap;
			}
			else
			{
				timeForThirdMachine += thirdMachineTimesVector[*itJobOrder - 1].second;
			}
		}
	}
	if (threeMachines == false)
		return timeForSecondMachine;
	else
		return timeForThirdMachine;
}

int Algorithm::permutations(bool threeMachines)
{
	std::vector<std::pair<int, int>> firstMachineTimesVector{ std::begin(_firstMachine._timesForJobs), std::end(_firstMachine._timesForJobs) };
	std::list<int> jobOrder;
	int minTime = 9999;
	int timeTmp;

	do
	{
		jobOrder.clear();
		for (int i = 0; i < firstMachineTimesVector.size(); i++)
		{
			jobOrder.push_back(firstMachineTimesVector[i].first);
		}
		timeTmp = countTime(jobOrder, threeMachines);
		if (timeTmp < minTime)
			minTime = timeTmp;
	} while (std::next_permutation(firstMachineTimesVector.begin(), firstMachineTimesVector.end()));

	return minTime;
}

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