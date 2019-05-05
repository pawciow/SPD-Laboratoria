#pragma once
#include<list>
#include <algorithm>
#include<iostream>
#include<queue>
#include"RPQ.h"
#include <fstream>
class Schrage
{
public:
	Schrage();
	void operator() ();
	void LoadTasks(std::string filename);
	//std::list<RPQ> notOrderedTask, orderedTask;
	virtual ~Schrage();
private:
	std::priority_queue <RPQ, std::vector<RPQ>, RpqComparatorByR> notOrderedTask;
	std::priority_queue <RPQ, std::vector<RPQ>, RpqComparatorByQ>	orderedTask;
};

