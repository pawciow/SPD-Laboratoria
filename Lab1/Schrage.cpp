
#include "Schrage.h"


void Schrage::LoadTasks(std::string filename)
{
	std::ifstream fileStream(filename);
	unsigned int a, size;
	unsigned int r, p, q;
	fileStream >> size >> a;
	for (unsigned int i = 0; i < size; i++)
	{
		fileStream >> r >> p >> q;
		notOrderedTask.push({ r,p,q,i + 1 });
		tasksVector.push_back({ r,p,q,i + 1 });
	}
	fileStream.close();
	resultFromMakuchowski = a;
}

void Schrage::LoadTasks(std::vector<RPQ> _tasksVector)
{
	tasksVector = _tasksVector;
	for (const auto & e : tasksVector)
		notOrderedTask.push(e);
}
Schrage::Schrage() {}

int Schrage::operator() ()
{
	unsigned int time{}; /*min r*/
	unsigned int i{}; /*number */
	unsigned int tmpCmax{ 0 };
	std::vector<RPQ> order;

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
			order.back().timeWhenItsFinished = time; // FOR CARLIER
			if (time + order.back().Q > tmpCmax)
				tmpCmax = time + order.back().Q;
		}

	}
	std::cout << "Schrage: " << tmpCmax << std::endl;
	Cmax = tmpCmax;
	resultOrder = order;
	return Cmax;
}

Schrage::~Schrage()
{
}


SchragePmtn::SchragePmtn()
{}

int SchragePmtn::operator() ()
{
	RPQ currentTask = { 0, 0, 0, 0 };
	RPQ tmp;
	std::vector<RPQ> order;
	int i = 0;
	int time = notOrderedTask.top().R;
	Cmax = 0;

	while (!orderedTask.empty() || !notOrderedTask.empty())
	{
		while (!notOrderedTask.empty() && (notOrderedTask.top().R <= time))
		{
			tmp = notOrderedTask.top();
			orderedTask.push(tmp);
			order.push_back(tmp);
			notOrderedTask.pop();


			if (tmp.Q > currentTask.Q)
			{

				currentTask.P = time - tmp.R;
				time = tmp.R;
				if (currentTask.P > 0)
				{
					orderedTask.push(currentTask);
					order.push_back(currentTask);

				}
			}

		}
		if (orderedTask.empty())
		{
			time = notOrderedTask.top().R;
		}
		else
		{
			tmp = orderedTask.top();
			orderedTask.pop();
			order.pop_back();
			currentTask = tmp;

			time = time + tmp.P;
			Cmax = (Cmax > (time + tmp.Q)) ? Cmax : (time + tmp.Q);
		}
	}

	std::cout << "Schrage pmtn:" << Cmax << std::endl;
	return Cmax;
}

SchragePmtn::~SchragePmtn()
{}
