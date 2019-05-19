#include "Carlier.h"


using namespace std;

Carlier::Carlier() : a(0), b(0), c(-1), U(0), UB(INT_MAX), LB(0)
{}

int Carlier::carlier(vector<RPQ> taskVector)
{
	int U;
	int i = 0;

	Schrage schrage;
	schrage.LoadTasks(taskVector);

	SchragePmtn schragePmtn;
	schragePmtn.LoadTasks(taskVector);
	
	U = schrage();
	 ////////// KROK 2
	if (U < UB)
	{
		UB = U;
		taskVector = schrage.resultOrder;
	}

	for (auto e : taskVector)
	{
		cout << e.NR << " " << e.timeWhenItsFinished << " \n";
	}
		
	////////// KROK 3
	find_b(taskVector, U);

	cout << "Zadanie b: " << b << " o numerze:" << taskVector[b].NR << endl;
	find_a(taskVector, U);

	cout << a << endl;
	find_c(taskVector, U);

	cout << c << endl;

	cout << "Zadanie b:\n" << "\n\tNumer zadania: " << taskVector[b].NR << endl;
	cout << "Zadanie a:\n" << "\n\tNumer zadania: " << taskVector[a].NR << endl;
	cout << "Zadanie Krytyczne(C):\n" << "\n\tNumer zadania: " << taskVector[c].NR << endl;
	
	////////// KROK 4
	if (c == -1)
	{
		cout << "END";
		return U; 
	}

	return U;

}



int Carlier::find_b(std::vector<RPQ> _tasks, int Cmax)
{
	cout << "ZNAJDOWAINE B: \n \n";

	for (auto e : _tasks)
	{
		cout << e.NR << " " << e.timeWhenItsFinished << " \n";
	}
	unsigned int i = 0;
	for (i = 0; i < _tasks.size(); i++)
	{
		//cout << "Czas zakoñczenia + Czas.Q";
		//cout << _tasks[i].timeWhenItsFinished << " + " << _tasks[i].Q << endl;
		if (Cmax == _tasks[i].timeWhenItsFinished + _tasks[i].Q)
		{
			b = i;
			cout << "Znaleziono zadanie numer: " << _tasks[b].NR << endl
				 << "Które w kolejnoœæi jest: "  << i <<endl;

			return b;

		}
	}
}

int Carlier::find_a(std::vector<RPQ> _tasks, int Cmax)
{
	// cout << "Zatrzymam siê przed zadaniem: " << _tasks[b].NR << endl;  // TMP DEBUG
	for (a = 0; a < b; a++)
	{
		unsigned int sum = 0;
		for (unsigned int i = 0; i <= b; i++)
		{

			sum = sum + _tasks[i].P;
		}

		auto BIGSUM = sum + _tasks[a].P + _tasks[b].R;
		//cout << "BIGSUM: " << BIGSUM << endl; // TMP DEBUG
		if (BIGSUM == Cmax)
			return a;
	}
	return 1;

}

int Carlier::find_c(std::vector<RPQ> _tasks, int Cmax)
{
	c = -1;
	int i = b;

	for (i = b; i >= a; i--)
	{
		if (_tasks[i].Q < _tasks[b].Q)
		{
			c = i;
			break;
		}
	}

	return c;
}



Carlier::~Carlier() {}