#include "NEH.h"



void NEH::DO()
{
	std::cout << "Starting the NEH algorithm. Step one:" << std::endl;
	StepOne();
}

void NEH::StepOne()
{
	std::vector<std::pair<const int, int>> sumForTasks(_machines[0]._timesForJobs.size()); /* Pary w postaci : nr zadania, suma dla tego zadanka*/
	
	for (auto & e : _machines)
	{
		for (auto & i : e._timesForJobs)
		{
			sumForTasks[i.first].second =+ i.second;
		}
	}

	//_sumForTask = sumForTasks;
}

void NEH::StepTwo()
{
	/*std::sort(_sumForTask.begin(), _sumForTask.end(),
		[](std::pair<const int, int> first, std::pair<const int, int> second)->bool {
			return(first.second > second.second);
	});*/
}