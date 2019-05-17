#pragma once
#include "Schrage.h"

using namespace std;

class Carlier
{
public:
	Carlier();
	~Carlier();

	Schrage schrage;
	SchragePmtn schragePmtn;
	int n;

	//RPQ PI_opt[2000];
	int U; // warto�� funkcji celu Cmax
	int UB; // g�rne oszacowanie, upper bound
	int LB; // dolne oszacowanie, lower bound

	int a; // numer pierwszego zadania w bloku K
	int b; // numer ostatniego zadania w bloku K
	int c; // numer zadania przeszkadzajac�go, interference job

	unsigned int r_plim; // nowe r dla zadania c
	unsigned int p_plim; // suma p KROK 5
	unsigned int q_plim; // nowe q dla zadania c

	int r_mem; // zapami�tane r zadania c
	int q_mem; // zapami�tane q zadania c
	int nr_mem; // zapami�tany numer zadania c

	int carlier();
	int find_a();
	int find_b();
	int find_c();



};