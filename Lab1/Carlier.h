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

	void LoadTasks(std::string fileName);
	std::vector<int> wyniki;
	std::vector<RPQ> quickFIXVector; //For loading
	int U; // wartoœæ funkcji celu Cmax
	int UB; // górne oszacowanie, upper bound
	int LB; // dolne oszacowanie, lower bound
	int resultFromMakuchowski;

	int toRemember_R = -1;
	unsigned int toRembember_NR = 0;
	int toRemember_P = -1;
private:

	int find_a(std::vector<RPQ> _tasks, int Cmax, int b);
	int find_b(std::vector<RPQ> _tasks, int Cmax);
	int find_c(std::vector<RPQ> _tasks, int Cmax, int a, int b);



};