#include "Schrage.h"

/*
std::list<RPQ> findPreparedTask(int time, std::list<RPQ> listWhereToFind)
{
	std::list<RPQ> a;
	std::transform(listWhereToFind.begin(), listWhereToFind.end(), a.begin(), std::back_inserter(a),
		[time](RPQ & tmp) {
			return tmp.Q > time;
		}
	);
	return a;
}*/
Schrage::Schrage()
{
	int time; /*min r*/
	int i; /*number */
	std::list<RPQ> partialOrder;

	while (!orderedTask.empty() || !notOrderedTask.empty())
	{
		/*std::list<RPQ> preparedTaskSoFar = findPreparedTask(time, notOrderedTask);
		while (!notOrderedTask.empty() && !preparedTaskSoFar.empty()) 
		{
			std::transform(orderedTask.begin(), orderedTask.end(), std::back_inserter(orderedTask), 
				[notOrderedTask]
			)
			orderedTask.push_back(e);
		}*/
		while (!notOrderedTask.empty() && notOrderedTask.top().Q > time)
		{
			orderedTask.push(notOrderedTask.top());
			notOrderedTask.pop();
		}
		

	}
}


Schrage::~Schrage()
{
}
