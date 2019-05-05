#pragma once
#include<list>
#include<queue>
#include"RPQ.h"
class Schrage
{
public:
	Schrage();
	//std::list<RPQ> notOrderedTask, orderedTask;
	virtual ~Schrage();
private:
	std::list<RPQ> findPreparedTask(int time, std::list<RPQ> listWhereToFind);
	std::priority_queue <RPQ, std::vector<RPQ>, RPQ> notOrderedTask, orderedTask;
};

