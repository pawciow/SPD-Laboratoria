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

void Schrage::SchragePmtn() 
{
	unsigned int time{}; /*min r*/
	unsigned int i{}; /*number */
	unsigned int Cmax{ 0 };

	std::vector<RPQ> order;
	
	std::vector<RPQ> listaprzerwan;

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

			while (!listaprzerwan.empty())
				listaprzerwan.pop_back();

			for (int i = 0; i < (int)notOrderedTask.size(); i++)
				if ((orderedTask.top().P + time > notOrderedTask.top().R) && (orderedTask.top().Q < notOrderedTask.top().Q))
					listaprzerwan.push_back(notOrderedTask.top());

			if (listaprzerwan.empty())
			{
				order.push_back(orderedTask.top());
				orderedTask.pop();
				time += order.back().P;

				if (time + order.back().Q > Cmax)
					Cmax = time + order.back().Q;
			}

			else 
			{
				RPQ part1 = orderedTask.top();
				orderedTask.pop();
				RPQ part2 = part1;

				part1.P = listaprzerwan.back().R - time;
				part2.P -= part1.P;
				orderedTask.push(part2);

				order.push_back(part1);
				
				time += order.back().P;

				if (time + order.back().Q > Cmax)
					Cmax = time + order.back().Q;



			}

		}

	}
	std::cout << Cmax << std::endl;

}

Schrage::~Schrage()
{
}
