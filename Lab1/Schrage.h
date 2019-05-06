#pragma once
#include <list>
#include <algorithm>
#include <iostream>
#include <queue>
#include "RPQ.h"
#include "Heap.hpp"
#include <fstream>


class Schrage
{
public:
	Schrage();
	void operator() ();
	void LoadTasks(std::string filename);
	virtual ~Schrage();
	void SchragePmtn();
private:
	std::priority_queue <RPQ, std::vector<RPQ>, RpqComparatorByR> notOrderedTask;
	std::priority_queue <RPQ, std::vector<RPQ>, RpqComparatorByQ>	orderedTask;
};

