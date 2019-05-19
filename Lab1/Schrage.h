#pragma once
#include <list>
#include <algorithm>
#include <iostream>
#include <queue>
#include "RPQ.h"
#include "Heap.hpp"
#include <fstream>
#include <map>


class Schrage
{
public:
	Schrage();
	virtual int operator() ();
	void LoadTasks(std::string filename);
	void LoadTasks(std::vector<RPQ> _tasksVector);
	virtual ~Schrage();
	Heap <RPQ, RpqComparatorByR>  notOrderedTask;
	Heap <RPQ, RpqComparatorByQ>	orderedTask;
	int Cmax;
public:
	std::vector<RPQ> resultOrder;
	std::vector<RPQ> tasksVector;
	std::map<unsigned int, unsigned int> whenTaskStarted;
};

class SchragePmtn : public Schrage
{
public:
	SchragePmtn();
	int operator() () final;
	virtual ~SchragePmtn();
};