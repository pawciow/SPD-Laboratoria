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
		_firstMachine.findMinTime();
	}
	else if (whichMachine == JohnsonsTwoMachineAlgorithm::MachineNumber::Second)
	{
		_secondMachine.LoadTimes(times);
		_secondMachine.findMinTime();

	}
	else
	{
		std::cerr << "Wrong machine number!" << std::endl;
		exit(1);
	}
}

std::pair<const int, const int> Machine::findMinTime() /* Tak bym to rozwi¹za³ ale mo¿esz porawiæ jak jest nieoptymalnie czy coœ */
{
	std::pair<int, int> min = { 0, 999 };
	std::list<std::pair<const int, const int>>::iterator it;
	for (it = _timesForJobs.begin(); it != _timesForJobs.end(); ++it)
	{
		if (_timesForJobs.front().second < min.second) // to jest Ÿle, jak to porównaæ?
		{
			min = *it;
			//min.second = _timesForJobs.front().second;
			//min.first = _timesForJobs.front().first;
		}
	}
	std::cout << min.first << std::endl; // test
	return min;
}

/*http://kkapd.f11.com.pl/zsw/Algorytm_Johnsona/przyklad_Johnson.htm Przyk³ad który bêdziemy odtwarzaæ*/
void JohnsonsTwoMachineAlgorithm::DO()
{
	std::list<int> jobsToConsiderate{ 1,2,3,4,5 };
	std::list<std::pair<int, int>> jobOptimalOrder1{ NULL };
	std::list<std::pair<int, int>> jobOptimalOrder2{ NULL };

	while (jobsToConsiderate.size() != 0)
	{
		std::pair<int, int> lowestFromFirst = _firstMachine.findMinTime();
		std::pair<int, int> lowestFromSecond = _secondMachine.findMinTime();
		if (lowestFromFirst.second < lowestFromSecond.second)
		{
			jobOptimalOrder1.push_back(lowestFromFirst);
			jobsToConsiderate.remove(lowestFromFirst.first);
		}
		else
		{
			jobOptimalOrder2.push_front(lowestFromSecond);
			jobsToConsiderate.remove(lowestFromSecond.second);
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
	//exampleAlgorithm.DO();
	return 0;
}