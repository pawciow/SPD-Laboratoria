#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <initializer_list>
#include <map>
#include <algorithm>

using timesForJobs = std::vector<std::pair<const int, const int>>; /*Nazwa niefortunna, trzeba zmieniæ XD
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
	enum class MachineNumber {First,Second};
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
	/*TODO*/
}
/*http://kkapd.f11.com.pl/zsw/Algorytm_Johnsona/przyklad_Johnson.htm Przyk³ad który bêdziemy odtwarzaæ*/
void JohnsonsTwoMachineAlgorithm::DO()
{
	std::list<int> jobsToConsiderate{ 1,2,3,4,5 };
	/*TODO*/
	//while (jobsToConsiderate.size() != 0)
	{
		//int lowestFromFirst = std::min_element(_firstMachine._timesForJobs.begin(), _firstMachine._timesForJobs.end(),[]());
	}
}

int main()
{
	JohnsonsTwoMachineAlgorithm exampleAlgorithm;
	timesForJobs exampleTimes{ {1,6},{2,0},{3,5}, {4,8}, {5,2} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::First, exampleTimes);
	timesForJobs exampleTimes2{ {1,5}, {2,1}, {3,4}, {4,8}, {5,3} };
	exampleAlgorithm.LoadTimesForMachines(JohnsonsTwoMachineAlgorithm::MachineNumber::Second, exampleTimes2);
	return 0;
}