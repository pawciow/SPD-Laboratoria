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

class JohnsonsTwoMachineAlgorithm
{
public:
	JohnsonsTwoMachineAlgorithm() = default;
	enum class MachineNumber { First, Second, Third };
	virtual void LoadTimesForMachines(MachineNumber whichMachine, timesForJobs times);
	std::list<int> FindOptimalOrder();
	int virtual countTime(std::list<int> jobOrder);
	int timeForNextMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine);
	int permutations();
	Machine _firstMachine;
	Machine _secondMachine;
	bool nextMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine);
};

class JohnsonsThreeMachineAlgorithm : public JohnsonsTwoMachineAlgorithm
{
public:
	JohnsonsThreeMachineAlgorithm() = default;
	void LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber whichMachine, timesForJobs times) override;
	int countTime(std::list<int> jobOrder) override;
	std::list<int> FindOptimalOrderForThree(); // Wyj¹tkowo niefortunna nazwa, przyda³oby siê póŸniej zmieniæ xD
private:
	Machine _firstMachine;
	Machine _secondMachine;
	Machine _thirdMachine;
};

void Machine::LoadTimes(timesForJobs times)
{
	for (auto & e : times)
		_timesForJobs.push_back(e);
}

std::pair<const int, const int> Machine::findMinTime()
{
	auto min = std::make_pair(0, 999);
	for (auto it = _timesForJobs.begin(); it != _timesForJobs.end(); ++it)
	{
		if (std::get<1>(*it) < min.second)
			min = *it;
	}

	return min;
}

void Machine::deleteTask(std::pair<int, int> taskToDelete)
{
	for (auto it = _timesForJobs.begin(); it != _timesForJobs.end(); ++it)
	{
		if (std::get<0>(*it) == taskToDelete.first)
		{
			it = _timesForJobs.erase(it);
			break;
		}
	}
}

void JohnsonsTwoMachineAlgorithm::LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber whichMachine, timesForJobs times)
{
	if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::First)
		_firstMachine.LoadTimes(times);

	else if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::Second)
		_secondMachine.LoadTimes(times);

	else
	{
		std::cerr << "Wrong machine number!" << std::endl;
		exit(1);
	}
}

bool JohnsonsTwoMachineAlgorithm::nextMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine)
{
	return (timeForFirstMachine > timeForSecondMachine);
}

std::list<int> JohnsonsTwoMachineAlgorithm::FindOptimalOrder()
{
	Machine tmpFirstMachine = _firstMachine;
	Machine tmpSecondMachine = _secondMachine;
	std::list<std::pair<const int, const int>> jobOptimalOrder1;
	std::list<std::pair<const int, const int>> jobOptimalOrder2;

	std::list<int> finalJobOrder;
	
	while (!tmpFirstMachine._timesForJobs.empty() && !tmpSecondMachine._timesForJobs.empty())
	{
		auto lowestFromFirst = tmpFirstMachine.findMinTime();
		auto lowestFromSecond = tmpSecondMachine.findMinTime();

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

	for (auto && it : finalJobOrder)
		std::cout << " " << it;
	std::cout << std::endl;

	return finalJobOrder;
}

int JohnsonsTwoMachineAlgorithm::timeForNextMachineHaveToWait(int timeForFirstMachine, int timeForSecondMachine)
{
	int gap = timeForFirstMachine - timeForSecondMachine;
	if (gap > 0) return gap;
	else return 0;
}

int JohnsonsTwoMachineAlgorithm::countTime(std::list<int> jobOrder)
{
	int timeForFirstMachine = 0;
	int timeForSecondMachine = 0;

	std::vector<std::pair<const int, const int>> firstMachineTimesVector{
		std::begin(_firstMachine._timesForJobs), std::end(_firstMachine._timesForJobs) };
	std::vector<std::pair<const int, const int>> secondMachineTimesVector{
		std::begin(_secondMachine._timesForJobs), std::end(_secondMachine._timesForJobs) };

	for (auto itJobOrder = jobOrder.begin(); itJobOrder != jobOrder.end(); ++itJobOrder)
	{
		timeForFirstMachine += firstMachineTimesVector[*itJobOrder - 1].second;
		if (nextMachineHaveToWait(timeForFirstMachine,timeForSecondMachine))
			timeForSecondMachine = (timeForFirstMachine + secondMachineTimesVector[*itJobOrder-1].second);
		else
			timeForSecondMachine += secondMachineTimesVector[*itJobOrder - 1].second;
	}

	return std::max(timeForFirstMachine,timeForSecondMachine);
}

int JohnsonsTwoMachineAlgorithm::permutations()
{
	std::vector<std::pair<int, int>> firstMachineTimesVector{
		_firstMachine._timesForJobs.begin(), _firstMachine._timesForJobs.end() };
	std::list<int> jobOrder;
	int minTime = 9999;
	int timeTmp;
	
	while (std::next_permutation(firstMachineTimesVector.begin(), firstMachineTimesVector.end()))
	{
		jobOrder.clear();
		for (unsigned int i = 0; i < firstMachineTimesVector.size(); i++)
		{
			jobOrder.push_back(firstMachineTimesVector[i].first);
		}
		timeTmp = countTime(jobOrder);
		if (timeTmp < minTime)
			minTime = timeTmp;
	}

	return minTime;
}

void JohnsonsThreeMachineAlgorithm::LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber whichMachine, timesForJobs times)
{
	if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::First)
		_firstMachine.LoadTimes(times);

	else if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::Second)
		_secondMachine.LoadTimes(times);

	else if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::Third)
		_thirdMachine.LoadTimes(times);

	else
	{
		std::cerr << "Wrong machine number!" << std::endl;
		exit(1);
	}
}

std::list<int> JohnsonsThreeMachineAlgorithm::FindOptimalOrderForThree()
{
	std::vector<std::pair<const int, int>> tmpFirstMachineJobs(_firstMachine._timesForJobs.begin(), _firstMachine._timesForJobs.end());
	std::vector<std::pair<const int, int>> tmpSecondMachineJobs(_secondMachine._timesForJobs.begin(), _secondMachine._timesForJobs.end());
	std::vector<std::pair<const int, int>> tmpThirdMachineJobs(_thirdMachine._timesForJobs.begin(), _thirdMachine._timesForJobs.end());

	
	for (unsigned int i = 0; i < _firstMachine._timesForJobs.size(); i++)
	{
		JohnsonsTwoMachineAlgorithm::_firstMachine._timesForJobs.push_back(
			std::make_pair(i,(tmpFirstMachineJobs[i].second + tmpSecondMachineJobs[i].second)));
		JohnsonsTwoMachineAlgorithm::_secondMachine._timesForJobs.push_back(
			std::make_pair(i, (tmpThirdMachineJobs[i].second + tmpSecondMachineJobs[i].second)));
	} 
	
	return FindOptimalOrder();
}

int JohnsonsThreeMachineAlgorithm::countTime(std::list<int> jobOrder)
{
	std::vector<std::pair<const int, int>> tmpFirstMachineJobs(_firstMachine._timesForJobs.begin(), _firstMachine._timesForJobs.end());
	std::vector<std::pair<const int, int>> tmpSecondMachineJobs(_secondMachine._timesForJobs.begin(), _secondMachine._timesForJobs.end());
	std::vector<std::pair<const int, int>> tmpThirdMachineJobs(_thirdMachine._timesForJobs.begin(), _thirdMachine._timesForJobs.end());

	int timeForFirstMachine = 0, timeForSecondMachine = 0, timeForThirdMachine = 0;

	for (auto & e : jobOrder)
	{
		timeForFirstMachine =+ tmpFirstMachineJobs[e].second;
		if (nextMachineHaveToWait(timeForFirstMachine, timeForSecondMachine))
			timeForSecondMachine = timeForFirstMachine + tmpSecondMachineJobs[e].second;
		else
			timeForSecondMachine += tmpSecondMachineJobs[e].second;

		if (nextMachineHaveToWait(timeForSecondMachine, timeForThirdMachine))
			timeForThirdMachine = timeForSecondMachine + tmpSecondMachineJobs[e].second;
		else
			timeForThirdMachine += tmpThirdMachineJobs[e].second;
	}

	return std::max(std::max(timeForFirstMachine, timeForSecondMachine), timeForThirdMachine);
}

int main()
{
	int time;
	JohnsonsTwoMachineAlgorithm exampleAlgorithm;
	timesForJobs exampleTimes{ {1,3},{2,5},{3,7}, {4,9}, {5,2} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::First, exampleTimes);
	timesForJobs exampleTimes2{ {1,4}, {2,11}, {3,1}, {4,12}, {5,10} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::Second, exampleTimes2);
	time = exampleAlgorithm.countTime(exampleAlgorithm.FindOptimalOrder());
	std::cout << "Czas wykonania zadan wedlog reguly Johnson'a wynosi: " << time << std::endl;
	time = exampleAlgorithm.permutations();
	std::cout << "Czas wykonania zadan po sprawdzeniu wszystkich mozliwosci wynosi: " << time << std::endl;
	return 0;
}