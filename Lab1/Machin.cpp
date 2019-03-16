#include "Machin.h"


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
	for (auto it = _timesForJobs.begin(); it != _timesForJobs.end(); ++it)
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
	for (auto it = _timesForJobs.begin(); it != _timesForJobs.end(); ++it)
	{
		if (std::get<0>(*it) == taskToDelete.first)
		{
			it = _timesForJobs.erase(it);
			break;
		}
	}
}
