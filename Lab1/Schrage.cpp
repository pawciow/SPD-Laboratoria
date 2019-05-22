
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
		notOrderedTask.push({ r,p,q,i+1 });
		tasksVector.push_back({ r,p,q,i+1 });
	}
	fileStream.close();
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
	std::cout << "Schrage result:"<<tmpCmax << std::endl;
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
	unsigned int time{};
	unsigned int i{};
	unsigned int tmpCmax{ 0 };

	std::vector<RPQ> order;
	std::list<RPQ> interrupts;

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
			while (!interrupts.empty())
				interrupts.pop_back();

			for (int i = 0; i < notOrderedTask.size; i++)
				if ((orderedTask.top().P + time > notOrderedTask.top().R) && (orderedTask.top().Q < notOrderedTask.top().Q))
					interrupts.push_back(notOrderedTask.top());

			if (interrupts.empty())
			{
				order.push_back(orderedTask.top());
				orderedTask.pop();
				time += order.back().P;

				if (time + order.back().Q > tmpCmax)
					tmpCmax = time + order.back().Q;
			}

			else
			{
				RPQ part1 = orderedTask.top();
				orderedTask.pop();
				RPQ part2 = part1;

				part1.P = interrupts.back().R - time;
				part2.P -= part1.P;
				orderedTask.push(part2);

				order.push_back(part1);

				order.back().timeWhenItsFinished = time; // FOR CARLIER

				time += order.back().P;

				if (time + order.back().Q > tmpCmax)
					tmpCmax = time + order.back().Q;
			}
		}
	}
	std::cout << "Schgrage pmtn result:" << tmpCmax << std::endl;
	Cmax = tmpCmax;
	resultOrder = order;
	return Cmax;
}

SchragePmtn::~SchragePmtn()
{}