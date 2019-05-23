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

	int resultFromMakuchowski;


private:

	int find_a(std::vector<RPQ> _tasks, int Cmax, int b);
	int find_b(std::vector<RPQ> _tasks, int Cmax);
	int find_c(std::vector<RPQ> _tasks, int Cmax, int a, int b);
	RPQ findH(int a, int b, std::vector<RPQ> taskVector);

	void testyEliminacyjne(int a, int b, std::vector<RPQ> taskVector, RPQ k, int UB);

	
};