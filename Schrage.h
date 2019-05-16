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
	virtual int operator() ();
	void LoadTasks(std::string filename);
	virtual ~Schrage();
	std::vector<RPQ> tasksVector;
	int Cmax;
public:
	Heap <RPQ, RpqComparatorByR>  notOrderedTask;
	Heap <RPQ, RpqComparatorByQ>	orderedTask;
};

class SchragePmtn : public Schrage
{
public:
	SchragePmtn();
	int operator() () final;
	virtual ~SchragePmtn();
};