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

/*http://kkapd.f11.com.pl/zsw/Algorytm_Johnsona/przyklad_Johnson.htm Przyk³ad który bêdziemy odtwarzaæ*/
void JohnsonsTwoMachineAlgorithm::DO()
{
	std::list<std::pair<const int, const int>> jobOptimalOrder1;
	std::list<std::pair<const int, const int>> jobOptimalOrder2;

	std::list<std::pair<const int, const int>>::iterator it;

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

	while (jobOptimalOrder2.empty() == false)
	{

		jobOptimalOrder1.push_back(jobOptimalOrder2.front());
		jobOptimalOrder2.pop_front();
	}

	std::cout << "Kolejnosc wykonywania podanych zadan wedlog reguly Johnson'a to:";
	for (it = jobOptimalOrder1.begin(); it != jobOptimalOrder1.end(); ++it)
	{
		std::cout << " " << std::get<0>(*it);
	}
	std::cout << std::endl;
}

int main()
{
	JohnsonsTwoMachineAlgorithm exampleAlgorithm;
	timesForJobs exampleTimes{ {1,1},{2,3},{3,5}, {4,7}, {5,9} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::First, exampleTimes);
	timesForJobs exampleTimes2{ {1,2}, {2,4}, {3,6}, {4,8}, {5,10} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::Second, exampleTimes2);
	exampleAlgorithm.DO();
	return 0;
}