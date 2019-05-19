#pragma once
#include "Schrage.h"
#include <algorithm>
#include <numeric>
using namespace std;

class Carlier
{
public:
	Carlier();
	~Carlier();
	int carlier(std::vector<RPQ> taskVector, int __UB__);

	int U; // warto�� funkcji celu Cmax
	int UB; // g�rne oszacowanie, upper bound
	int LB; // dolne oszacowanie, lower bound
private:
	unsigned int a; // numer pierwszego zadania w bloku K
	unsigned int b; // numer ostatniego zadania w bloku K
	unsigned int c; // numer zadania przeszkadzajac�go, interference job

	int find_a(std::vector<RPQ> _tasks, int Cmax);
	int find_b(std::vector<RPQ> _tasks, int Cmax);
	int find_c(std::vector<RPQ> _tasks, int Cmax);



};