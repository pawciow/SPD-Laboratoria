#include "Schrage.h"
#include "Carlier.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
void calculateSchragePMTNInstantions()
{

	int score = 0;
	for (int i = 1; i < 10; i++)
	{
		std::string file = "dane_testowe\\schragepmtn\\";
		file += std::to_string(i);
		file += ".txt";

		std::cout << "TEST NUMER: " << file << endl;
		SchragePmtn tmp;
		tmp.LoadTasks(file);
		int a = tmp();
		std::cout << "\n najlepszy wynik: " << a;
		if (tmp.resultFromMakuchowski == a)
		{
			score++;
			std::cout << "\n DOBRZE! \n";
		}
		else
		{
			std::cout << "\n ZLE! Powinno byc: " << tmp.resultFromMakuchowski << endl;
		}
		std::cout << " \n \n \n \n";

	}
	std::cout << "by³o dobrze: " << score;
}
void calculateTestInstantions()
{

	int score = 0;
	for (int i = 1; i < 10; i++)
	{
		if(i == 3 || i == 2 || i == 5 || i == 8)
			continue;
		std::string file = "dane_testowe\\carlier\\";
		file += std::to_string(i);
		file += ".txt";

		std::cout << "TEST NUMER: " << file << endl;
		Carlier tmp;
		tmp.LoadTasks(file);
		int a = tmp.carlier(tmp.quickFIXVector, 9999);//, tmp.UB);
		std::cout << "\n najlepszy wynik: " << a;
		if (tmp.resultFromMakuchowski == a)
		{
			score++;
			std::cout << "\n DOBRZE! \n";
		}
		else
		{
			std::cout << "\n ZLE! Powinno byc: " << tmp.resultFromMakuchowski << endl;
		}
		std::cout << " \n \n \n \n";

	}
	std::cout << "by³o dobrze: " << score;
}
void calculateInstanceFromLecture()
{
	Carlier tmp;
	tmp.LoadTasks("dane_testowe\\makuch_wyklad.txt");
	int a = tmp.carlier(tmp.quickFIXVector, 9999);
	std::cout << "\n Wynik: " << a;
}
int main()
{
	//calculateSchragePMTNInstantions();
	calculateInstanceFromLecture();
	//calculateTestInstantions();
	return 0;
}



