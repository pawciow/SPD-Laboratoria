#include "Schrage.h"
#include "Carlier.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>

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
	int score = 0;
	int i = 9;
	{
		std::string file= "dane_testowe\\carlier\\";
		file += std::to_string(i);
		file += ".txt";

		Carlier tmp;
		tmp.LoadTasks(file);
		int a = tmp.carlier(tmp.quickFIXVector, tmp.UB);
		cout << "\n najlepszy wynik: " << a;
		if (tmp.resultFromMakuchowski == a)
		{
			score++;
			std::cout << "DOBRZE! \n";
		}
			
	}
	cout << "by³o dobrze: " << score;
	return 0;
}



