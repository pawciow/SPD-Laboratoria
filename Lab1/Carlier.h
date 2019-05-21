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
	int carlier(std::vector<RPQ> taskVector, int UB);//, int __UB__);

	void LoadTasks(std::string fileName);
	std::vector<int> wyniki;
	std::vector<RPQ> quickFIXVector; //For loading
	//int U; // warto�� funkcji celu Cmax
	//int UB; // g�rne oszacowanie, upper bound
	//int LB; // dolne oszacowanie, lower bound
	int resultFromMakuchowski;

	int toRemember_R = -1;
	unsigned int toRembember_NR = 0;
	int toRemember_Q = -1;
private:

	int find_a(std::vector<RPQ> _tasks, int Cmax, int b);
	int find_b(std::vector<RPQ> _tasks, int Cmax);
	int find_c(std::vector<RPQ> _tasks, int Cmax, int a, int b);
	RPQ findH(int a, int b, std::vector<RPQ> taskVector);

};