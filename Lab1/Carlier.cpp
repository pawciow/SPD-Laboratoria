#include "Carlier.h"


using namespace std;

Carlier::Carlier() : a(0), b(0), c(-1), U(0), UB(INT_MAX), LB(0)
{}

int Carlier::carlier(vector<RPQ> taskVector, int __UB__)
{
	int U;
	int i = 0;
	//unsigned int R_PERMUTACJI_WYKONANIA_ZADAN_NA_MASZYNIE; //?? by³o u http://new.zsd.iiar.pwr.wroc.pl/files/zadania/CARLIER/AC.pdf

	Schrage schrage;
	schrage.LoadTasks(taskVector);

	SchragePmtn schragePmtn;

	U = schrage();
	////////// KROK 2
	if (U < UB)
	{
		UB = U;
		taskVector = schrage.resultOrder;
	}

	////////// KROK 3
	find_b(taskVector, schrage.Cmax);

	cout << "Zadanie b: " << b << " o numerze:" << taskVector[b].NR << endl;
	find_a(taskVector, schrage.Cmax);

	c = find_c(taskVector, schrage.Cmax);

	if (a == b)
		return U; // TMP?
//	cout << c << endl;

	cout << "Zadanie b:\n" << "\n\tNumer zadania: " << taskVector[b].NR << endl;
	cout << "Zadanie a:\n" << "\n\tNumer zadania: " << taskVector[a].NR << endl;
	// cout << "Zadanie Krytyczne(C):\n" << "\n\tNumer zadania: " << taskVector[c].NR << endl;

	if (c == -1)
	{
		cout << "END";
		return U;
	}

	// Krok 5:

	RpqComparatorByR by_R;
	RpqComparatorByQ by_Q;
	unsigned int new_p;
	for (auto it = taskVector.begin() + c + 1; it <= taskVector.begin() + b; it++)
	{
		new_p = +it->P;
		std::cout << it->R << " " << it->P << " " << it->Q << " \n";
	}
	/* IM NOT SURE ABOUT BOUNDARIES - I MEAN IF (C+1) OR +B(MAYBE B+1?)*/
	auto min_r = max_element(taskVector.begin() + (c + 1), taskVector.begin() + b + 1, by_R);
	auto min_q = min_element(taskVector.begin() + (c + 1), taskVector.begin() + b + 1, by_Q);// HAX: because this compartor gives the biggest
	//auto min_p = max_element(taskVector.begin() + (c + 1), taskVector.begin() + b+1, by_P);

	RPQ temporary(min_r->R, min_r->P, min_q->Q, 1234);
	cout << "min_r " << temporary.R << "suma p " << temporary.P << "min_Q " << temporary.Q;

	// Krok 6
	//R_PERMUTACJI_WYKONANIA_ZADAN_NA_MASZYNIE = max({ R_PERMUTACJI_WYKONANIA_ZADAN_NA_MASZYNIE, temporary.R + temporary.P }); // Todo: ZROZUMIEÆ?
	unsigned int toRembember_NR = taskVector[c].NR;
	unsigned int toRemember_R = taskVector[c].R;
	taskVector[c].R = max({ min_r->R, temporary.R + temporary.P });
	// Krok 7
	schragePmtn.LoadTasks(taskVector);
	LB = schragePmtn();

	// Krok 8
	if (LB < UB)
	{
		UB = carlier(taskVector, UB); // Krok 9
	}
	// Krok 10
	for (auto & e : taskVector)
	{
		if (e.NR == toRembember_NR)
			e.R = toRemember_R;
	}

	// Krok 11
	toRembember_NR = taskVector[c].NR;
	unsigned int toRemember_P = taskVector[c].R;

	taskVector[c].Q = max({ taskVector[c].Q, temporary.Q + temporary.P });
	// Krok 12
	LB = schragePmtn();

	// Krok 13
	if (LB < UB)
	{
		UB = carlier(taskVector, UB); // Krok 14
	}

	// Krok 15
	for (auto & e : taskVector)
	{
		if (e.NR == toRembember_NR)
			e.P = toRemember_P;
	}

	return U;

}



int Carlier::find_b(std::vector<RPQ> _tasks, int Cmax)
{
	cout << "ZNAJDOWAINE B: \n ";

	/*for (auto e : _tasks)
	{
		cout << e.NR << " " << e.timeWhenItsFinished << " \n";
	}*/
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
		unsigned int BIGSUM = 0;
		BIGSUM = _tasks[a].R + _tasks[b].Q;
		unsigned int sum = 0;
		for (unsigned int i = a; i <= b; i++)
			sum = sum + _tasks[i].P;
		BIGSUM = BIGSUM + sum;
		if (BIGSUM == Cmax)
			return a;
	}
	return -1;

}

int Carlier::find_c(std::vector<RPQ> _tasks, int Cmax)
{
	for (int i = b; i >= a; i--)
	{
		if (_tasks[i].Q < _tasks[b].Q)
		{
			c = i;
			return c;
		}
	}

	return -1;
}



Carlier::~Carlier() {}