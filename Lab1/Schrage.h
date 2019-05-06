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
	Heap <RPQ, RpqComparatorByR>  notOrderedTask;
	Heap <RPQ, RpqComparatorByQ>	orderedTask;
};

