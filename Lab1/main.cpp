#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <initializer_list>
#include <map>
#include <algorithm>

using timesForJobs = std::list<std::pair<const int, const int>>; /*Nazwa niefortunna, trzeba zmieniæ XD
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
	void DO();
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
	std::cout << min.first << std::endl; // test

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
		}
	}
}

/*http://kkapd.f11.com.pl/zsw/Algorytm_Johnsona/przyklad_Johnson.htm Przyk³ad który bêdziemy odtwarzaæ*/
void JohnsonsTwoMachineAlgorithm::DO()
{
	//std::list<int> jobsToConsiderate{ 1,2,3,4,5 };
	std::list<std::pair<const int, const int>> jobOptimalOrder1{};
	std::list<std::pair<const int, const int>> jobOptimalOrder2{};

	std::pair<int, int> lowestFromFirst;
	std::pair<int, int> lowestFromSecond;

	while (_firstMachine._timesForJobs.empty() == false && _secondMachine._timesForJobs.empty() == false)
	{
		lowestFromFirst = _firstMachine.findMinTime();
		lowestFromSecond = _secondMachine.findMinTime();

		if (lowestFromFirst.second < lowestFromSecond.second)
		{
			jobOptimalOrder1.push_back(lowestFromFirst);

			_firstMachine.deleteTask(lowestFromFirst);
			_secondMachine.deleteTask(lowestFromFirst);
		}
		else
		{
			jobOptimalOrder2.push_front(lowestFromSecond);

			_firstMachine.deleteTask(lowestFromSecond);
			_secondMachine.deleteTask(lowestFromSecond);
		}
	}
}

int main()
{
	JohnsonsTwoMachineAlgorithm exampleAlgorithm;
	timesForJobs exampleTimes{ {1,6},{2,0},{3,5}, {4,8}, {5,2} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::First, exampleTimes);
	timesForJobs exampleTimes2{ {1,5}, {2,1}, {3,4}, {4,8}, {5,3} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::Second, exampleTimes2);
	exampleAlgorithm.DO();
	return 0;
}