#include"Schrage.h"
#include"Carlier.h"
#include <iostream>
#include <cstdio>
#include <ctime>

void TestSchrageOnAllMachines();
void TestCarlierOnAllMachines();

int main()
{
	//clock_t start = clock();
	
	int pause;
	//TestSchrageOnAllMachines();
	TestCarlierOnAllMachines();
	//printf("Czas wykonywania: %lu ms\n", clock() - start);
	std::cin >> pause;
	return 0;
}

void TestSchrageOnFile(std::string fileName)
{
	Schrage tmp1;
	SchragePmtn tmp2;
	tmp1.LoadTasks(fileName);
	tmp1();
	//tmp2();
}

void TesCarlierOnFile(std::string fileName)
{
	Carlier tmp;
	tmp.schrage.LoadTasks(fileName);
	tmp.schragePmtn.LoadTasks(fileName);
	tmp.carlier();
	//tmp2();
}

void TestSchrageOnAllMachines()
{
	std::vector<std::string> a{ "in50.txt", "in100.txt", "in200.txt" };
	for (auto e : a)
	{
		clock_t start = clock();
		printf("%s\n	", e.c_str());
		//std::cout << e << "  ";
		TestSchrageOnFile(e);
		printf("Czas wykonywania: %lu ms\n", clock() - start);
	}
}

void TestCarlierOnAllMachines()
{
	std::vector<std::string> a{ "in100.txt" };
	for (auto e : a)
	{
		clock_t start = clock();
		printf("%s\n	", e.c_str());
		//std::cout << e << "  ";
		TesCarlierOnFile(e);
		printf("Czas wykonywania: %lu ms\n", clock() - start);
	}
}
