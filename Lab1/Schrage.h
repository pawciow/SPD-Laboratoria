#pragma once
#include<list>
#include"RPQ.h"
class Schrage
{
public:
	Schrage();
	std::list<RPQ> notOrderedTask, orderedTask;
	std::list<RPQ> findPreparedTask(int time);
	virtual ~Schrage();
};

