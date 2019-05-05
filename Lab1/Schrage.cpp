#include "Schrage.h"


std::list<RPQ> findPreparedTask(int time, std::list<RPQ> listWhereToFind)
{
	std::list<RPQ> a;
	/*for (std::list<RPQ>::iterator i = listWhereToFind.begin(); i != listWhereToFind.end(); i++)
	{
		if (i->P <= time)
		{
			a.push_back(*i);
			listWhereToFind.erase(i);
		}
	}*/
	std::transform(listWhereToFind.begin(), listWhereToFind.end(), a.begin(), std::back_inserter(a),
		[time](RPQ & tmp) {
		return tmp.Q > time;
		}
	);
	return a;
}
Schrage::Schrage()
{
	int time; /*min r*/
	int i; /*number */
	std::list<RPQ> partialOrder;

	while (!orderedTask.empty() || !notOrderedTask.empty())
	{
		while (notOrderedTask.empty() &&
			time >= (std::min(notOrderedTask.begin(), notOrderedTask.end(),
			[](const RPQ & a, const RPQ & b){
			return a.Q > b.Q;
			}))->Q) /*Trochê nieczytelne XD ale to znajduje najmniejsze zadanka i sprawdza czy jest mniejsze ni¿ aktualny time*/
		{
			RPQ a = *std::min(notOrderedTask.begin(), notOrderedTask.end(),
				[](const RPQ & a, const RPQ & b) {
				return a.Q > b.Q;
			});
		}

	}
}


Schrage::~Schrage()
{
}
