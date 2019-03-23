#include "NEH.h"



void NEH::DO()
{
	std::cout << "Starting the NEH algorithm. Step one:" << std::endl;
	StepOne();
	printSumForTask();
	StepTwo();
	printSumForTask();
	for(int i = 0; i< 5; i++)
	StepFour();
}

bool NEH::LoadFromFile(std::string fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());
	if (!file.good())
		return false;

	Machine machineTmp;

	int taskAmount;
	int machinesAmount;
	int timeTmp;

	file >> taskAmount >> machinesAmount;
	if (!file.fail())
	{
		for (int i = 0; i < machinesAmount; i++)
		{
			_machines.push_back(machineTmp);
		}

		for (int j = 0; j < taskAmount; j++)
		{
			for (int i = 0; i < machinesAmount; i++)
			{
				file >> timeTmp;
				if (!file.fail())
				{
					_machines[i]._timesForJobs.push_back(std::make_pair(j, timeTmp));
				}
				else
					return false;
			}
		}
		return true;
	}
	else
		return false;
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

const std::pair<int, int> & NEH::StepThree()
{
	return(*std::max_element(std::begin(_sumForTask), std::end(_sumForTask),
		[](const std::pair<int, int> & first, const std::pair<int, int> & second)
		{
		return(first.second > second.second);
	}));
}

void NEH::StepFour()
{
	auto & taskToAdd = StepThree();
	std::vector<std::vector<std::pair<int, int>>> permutations;
	for (unsigned int i = 0; i < optimalTaskList.size(); i++)
	{
		std::vector<std::pair<int, int>> tmp = optimalTaskList;
		//std::copy(optimalTaskList.begin(),optimalTaskList.end(),tmp);
		tmp.insert(tmp.begin() + i, taskToAdd);
		for (const auto & e : tmp)
		{
			std::cout << "(" << e.first << "," << e.second << ")";
		}
		std::cout << std::endl;
	}
	optimalTaskList.push_back(taskToAdd);
}
