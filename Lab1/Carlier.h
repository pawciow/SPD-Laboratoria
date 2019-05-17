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
	int U; // wartoœæ funkcji celu Cmax
	int UB; // górne oszacowanie, upper bound
	int LB; // dolne oszacowanie, lower bound

	int a; // numer pierwszego zadania w bloku K
	int b; // numer ostatniego zadania w bloku K
	int c; // numer zadania przeszkadzajacêgo, interference job

	unsigned int r_plim; // nowe r dla zadania c
	unsigned int p_plim; // suma p KROK 5
	unsigned int q_plim; // nowe q dla zadania c

	int r_mem; // zapamiêtane r zadania c
	int q_mem; // zapamiêtane q zadania c
	int nr_mem; // zapamiêtany numer zadania c

	int carlier();
	int find_a();
	int find_b();
	int find_c();



};