#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <map>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <fstream>

using timesForJobs = std::list<std::pair<const int, const int>>;

class ILoadable {
public:
	virtual void LoadDataFromFile(std::string fileName) = 0;
	virtual ~ILoadable() = default;
};

class Machine
{
public:
	Machine() = default;
	void LoadTimes(timesForJobs times);
	timesForJobs _timesForJobs;

	std::pair<const int, const int> findMinTime();
	void deleteTask(std::pair<int, int> taskToDelete);
};
