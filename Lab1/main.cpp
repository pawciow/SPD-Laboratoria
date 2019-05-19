#include "Schrage.h"
#include "Carlier.h"
#include <iostream>
#include <cstdio>
#include <ctime>


/*
void TesCarlierOnFile(std::string fileName)
{
	Carlier tmp("in100.txt");
	tmp.carlier();
	//tmp2();
}


void TestCarlierOnAllMachines()
{
	std::vector<std::string> a{ "in50.txt" };
	for (auto e : a)
	{
		clock_t start = clock();
		printf("%s\n	", e.c_str());
		//std::cout << e << "  ";
		TesCarlierOnFile(e);
		printf("Czas wykonywania: %lu ms\n", clock() - start);
	}
}*/


int main()
{
	//clock_t start = clock();
	
	int pause;
	Schrage TMP; 
	TMP.LoadTasks("makuch_wyklad.txt");
	//TMP.LoadTasks("data.txt");
	Carlier tmp;
	int a = tmp.carlier(TMP.tasksVector, tmp.UB);
	cout << "najlepszy wynik: " << a;
	return 0;
}



