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
	virtual void operator() ();
	void LoadTasks(std::string filename);
	virtual ~Schrage();
protected:
	Heap <RPQ, RpqComparatorByR>  notOrderedTask;
	Heap <RPQ, RpqComparatorByQ>	orderedTask;
};

class SchragePmtn : public Schrage
{
public:
	SchragePmtn();
	void operator() () final;
	virtual ~SchragePmtn();
};