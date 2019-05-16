#include "Carlier.h"


using namespace std;

Carlier::Carlier() : a(0), b(0), c(-1), U(0), UB(INT_MAX), LB(0), r_plim(INT_MAX), p_plim(0), q_plim(INT_MAX), r_mem(-2), q_mem(-2), nr_mem(0) {}

int Carlier::carlier()
{
	int i = 0;
	n=100;
	Heap <RPQ, RpqComparatorByR>  tmpTaskHeap = schrage.notOrderedTask;
	std::vector<RPQ> tmpTaskVector;

	while (tmpTaskHeap.empty()!=true)
	{
		tmpTaskVector.push_back(tmpTaskHeap.top());
		tmpTaskHeap.pop();
	}
	std::reverse(tmpTaskVector.begin(), tmpTaskVector.end());
	////////// KROK 1
	U = schrage();

	 ////////// KROK 2
	if (U < UB)
	{
		UB = U;
		for (i = 0; i < n; i++)
		{
			PI_opt[i] = tmpTaskVector[i];
		}
	}

	////////// KROK 3
	find_b();

	cout << b << endl;
	find_a();

	cout << a << endl;
	find_c();

	cout << c << endl;

	cout << "Zadanie b:\n" << "\tPozycja w permutacji: " << b + 1 << " z " << n << "\n\tNumer zadania: " << tmpTaskVector[b].NR << endl;
	cout << "Zadanie a:\n" << "\tPozycja w permutacji: " << a + 1 << " z " << n << "\n\tNumer zadania: " << tmpTaskVector[a].NR << endl;
	cout << "Zadanie c:\n" << "\tPozycja w permutacji: " << c + 1 << " z " << n << "\n\tNumer zadania: " << tmpTaskVector[c].NR << endl;
	
	////////// KROK 4
	if (c == -1)
	{
		cout << "\tNie znaleziono zadania c!!!\n";
		return U; 
	}


	////////// KROK 5
	for (i = c + 1; i <= b; i++)
	{
		r_plim = std::min(r_plim, tmpTaskVector[i].R);
		p_plim += tmpTaskVector[i].P;
		q_plim = std::min(q_plim, tmpTaskVector[i].Q); 
	}
	
	////////// KROK 6
	if (r_mem == -2)
	{
		nr_mem = tmpTaskVector[c].NR;
		r_mem = tmpTaskVector[c].R;
	}

	tmpTaskVector[c].R = max(tmpTaskVector[c].R, r_plim + p_plim);

	////////// KROK 7
	LB = schragePmtn();

	////////// KROK 8
	if (LB < UB)
	{
		cout << "\tPierwszy if spelniony\n\n\n";
		////////// KROK 9
		UB = carlier();
	}
	////////// KROK 10
	for (i = 0; i < n; i++)
	{
		if (nr_mem == tmpTaskVector[i].NR)
			tmpTaskVector[i].R = r_mem; 
	}
	r_mem = -2;

	////////// KROK 11
	if (q_mem == -2)
	{
		nr_mem = tmpTaskVector[c].NR;
		q_mem = tmpTaskVector[c].Q;
	}

	tmpTaskVector[c].Q = max(tmpTaskVector[c].Q, q_plim + p_plim);

	////////// KROK 12
	LB = schragePmtn();

	////////// KROK 13
	if (LB < UB)
	{
		cout << "\tDrugi if spelniony\n\n\n\n";
		////////// KROK 14
		UB = carlier();

	}
	////////// KROK 15
	for (i = 0; i < n; i++)
	{
		if (nr_mem == tmpTaskVector[i].NR)
			tmpTaskVector[i].Q = q_mem; 
	}

	q_mem = -2;

	return U;

}



int Carlier::find_b()
{
	int i = 0;
	for (i = n - 1; i > 0; i--)
	{
		if (schrage.Cmax == schrage.tasksVector[i].Q + schrage.tasksVector[i].Q)
		{
			b = i;
			break;
		}
	}

	return b;
}

int Carlier::find_a()
{
	int suma = 0, i;

	for (a = 0; a < b; a++)
	{

		suma = 0;
		for (i = a; i <= b; i++)
		{
			suma += schrage.tasksVector[i].P;
		}

		if (schragePmtn.Cmax == (schragePmtn.tasksVector[a].R + suma + schragePmtn.tasksVector[b].Q))
		{
			return a;
		}
	}
	return a;

}

int Carlier::find_c()
{
	c = -1;
	int i;

	for (i = b; i >= a; i--)
	{
		if (schrage.tasksVector[i].Q < schrage.tasksVector[b].Q)
		{
			c = i;
			break;
		}
	}

	return c;
}



Carlier::~Carlier() {}