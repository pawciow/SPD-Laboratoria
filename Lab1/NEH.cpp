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
					_machines[i]._timesForJobs.push_back(std::make_pair(j+1, timeTmp));
				}
				else
					return false;
			}
		}
		std::cout << "wczytywanie sie powiodlo" << std::endl;
		return true;
	}
	else
		return false;
}

int NEH::countTime(std::vector<std::pair<int, int>> jobOrder)
{
	int timeGap = 0;
	int i = 0;
	std::vector<int> timesForMachines;
	std::vector<std::pair<int, int>>::iterator itJobOrder;

	for (int i = 0; i < _machines.size(); i++)
		timesForMachines.push_back(0);

	for (itJobOrder = jobOrder.begin(); itJobOrder != jobOrder.end(); ++itJobOrder)
	{
		std::vector<std::pair<int, int>> MachineTimesVector0
		{ std::begin(_machines[0]._timesForJobs), std::end(_machines[0]._timesForJobs) };

		timesForMachines[0] += MachineTimesVector0[(*itJobOrder).first - 1].second;

		for (int i = 1; i < _machines.size(); i++)
		{
			std::vector<std::pair<const int, const int>> MachineTimesVector2
			{ std::begin(_machines[i]._timesForJobs), std::end(_machines[i]._timesForJobs) };


			timeGap = timeForSecondMachineHaveToWait(timesForMachines, i);

			if (timeGap != 0)
				timesForMachines[i] += MachineTimesVector2[std::get<0>(*itJobOrder) - 1].second + timeGap;
			else
				timesForMachines[i] += MachineTimesVector2[std::get<0>(*itJobOrder) - 1].second;
		}
	}
	std::cout << timesForMachines.back() << " dla :";
	return timesForMachines.back();
}

int NEH::timeForSecondMachineHaveToWait(std::vector<int> timesForMachines, int number)
{
	int gap = timesForMachines[number - 1] - timesForMachines[number];
	if (gap > 0) return gap;
	else return 0;
};

void NEH::printSumForTask()
{
	for (const auto & e : _sumForTask)
		std::cout << "(" << e.first << "," << e.second << "),";
	std::cout << std::endl;
}

void NEH::StepOne()
{
	std::vector<std::pair<int, int>> sumForTasks(_machines[0]._timesForJobs.size()); /* Pary w postaci : nr zadania, suma dla tego zadanka*/

	for (auto & e : _machines)
	{
		for (auto & i : e._timesForJobs)
		{
			sumForTasks[i.first - 1].second = sumForTasks[i.first - 1].second + i.second;
			sumForTasks[i.first - 1].first = i.first;
		}
	}

	_sumForTask = sumForTasks;
}

void NEH::StepTwo()
{
	std::sort(_sumForTask.begin(), _sumForTask.end(),
		[](const std::pair<int, int> & first, const std::pair<int, int> & second)->bool {
		return(first.second < second.second);
	});
}

const std::pair<int, int> & NEH::StepThree(std::vector<std::pair<int, int>> & sumForTaskTmp)
{

	return(*std::max_element(std::begin(sumForTaskTmp), std::end(sumForTaskTmp),
		[](const std::pair<int, int> & first, const std::pair<int, int> & second)
	{
		return(first.second < second.second);
	}));


}

void NEH::StepFour()
{

	std::vector<std::pair<int, int>> sumForTaskTmp = _sumForTask;
	while (sumForTaskTmp.empty() != true)
	{
		//auto & taskToAdd = StepThree(sumForTaskTmp);
		std::pair<int, int> taskToAdd = sumForTaskTmp.back();
		int bestTime = 99999;
		int bestPlace = 0;


		std::vector<std::vector<std::pair<int, int>>> permutations;
		for (unsigned int i = 0; i < optimalTaskList.size() + 1; i++)
		{

			std::vector<std::pair<int, int>> tmp = optimalTaskList;
			//std::copy(optimalTaskList.begin(),optimalTaskList.end(),tmp);
			tmp.insert(tmp.begin() + i, taskToAdd);

			int timeTmp = countTime(tmp);
			if (bestTime > timeTmp)
			{
				bestTime = timeTmp;
				bestPlace = i;
			}

			for (const auto & e : tmp)
			{
				std::cout << "(" << e.first << "," << e.second << ")";
			}
			std::cout << std::endl;
		}
		optimalTaskList.insert(optimalTaskList.begin() + bestPlace, taskToAdd);
		sumForTaskTmp.pop_back();

		std::cout << "Optymalna droga po tym kroku: ";
		for (const auto & e : optimalTaskList) {
			std::cout << e.first << " ";
		}
		std::cout << " z czasem: " << bestTime << std::endl;
	}

}
