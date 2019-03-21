#include "NEH.h"



void NEH::DO()
{
	std::cout << "Starting the NEH algorithm. Step one:" << std::endl;
	StepOne();
	printSumForTask();
	StepTwo();
	printSumForTask();
	StepFour();
}

void NEH::printSumForTask()
{
	for (const auto & e : _sumForTask)
		std::cout << "("<< e.first << "," << e.second << "),";
	std::cout << std::endl;
}
void NEH::StepOne()
{
	std::vector<std::pair<int, int>> sumForTasks(_machines[0]._timesForJobs.size()); /* Pary w postaci : nr zadania, suma dla tego zadanka*/
	
	for (auto & e : _machines)
	{
		for (auto & i : e._timesForJobs)
		{
			sumForTasks[i.first - 1].second = sumForTasks[i.first-1].second + i.second;
			sumForTasks[i.first - 1].first = i.first;
		}
	}

	_sumForTask = sumForTasks;
}

void NEH::StepTwo()
{
	std::sort(_sumForTask.begin(), _sumForTask.end(),
		[](const std::pair<int, int> & first, const std::pair<int, int> & second)->bool {
		return(first.second > second.second);
	});
}

std::pair<int, int> NEH::StepThree()
{
	return (*std::min_element(std::begin(_sumForTask), std::end(_sumForTask),
		[](const std::pair<int, int> & first, const std::pair<int, int> & second)
		{
		return(first.second > second.second);
	}));
}

void NEH::StepFour()
{

}