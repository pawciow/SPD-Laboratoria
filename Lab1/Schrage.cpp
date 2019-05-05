#include "Schrage.h"


void Schrage::LoadTasks(std::string filename)
{
	std::ifstream fileStream(filename);
	unsigned int a, size;
	unsigned int r,p,q;
	fileStream >> size >> a;
	for (unsigned int i = 0; i < size; i++)
	{
		fileStream >> r >> p >> q;
		notOrderedTask.push({ r,p,q });
	}
	fileStream.close();
}
Schrage::Schrage() {}

void Schrage::operator() ()
{
	unsigned int time{}; /*min r*/
	unsigned int i{}; /*number */
	unsigned int Cmax{ 0 };
	std::list<RPQ> order;

	while (!orderedTask.empty() || !notOrderedTask.empty())
	{
		while (!notOrderedTask.empty() && notOrderedTask.top().R <= time)
		{
			orderedTask.push(notOrderedTask.top());
			notOrderedTask.pop();
		}

		if (orderedTask.empty())
		{
			time = notOrderedTask.top().R;
		}
		else
		{
			order.push_back(orderedTask.top());
			orderedTask.pop();

			time += order.back().P;
			if (time + order.back().Q > Cmax)
				Cmax = time + order.back().Q;
		}

	}
	std::cout << Cmax << std::endl;

}


Schrage::~Schrage()
{
}
