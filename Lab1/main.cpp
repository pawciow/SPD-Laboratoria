#include "Schrage.h"
#include "Carlier.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>

int main()
{
	int score = 0;
	for(int i = 1; i < 10; i++)
	{
		//if (i == 8)
			//continue; // bo stack overflow
		std::string file= "dane_testowe\\carlier\\";
		file += std::to_string(i);
		file += ".txt";

		std::cout << "TEST NUMER: " << file << endl;
		Carlier tmp;
		tmp.LoadTasks(file);
		int a = tmp.carlier(tmp.quickFIXVector, tmp.UB);
		cout << "\n najlepszy wynik: " << a;
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
	cout << "by³o dobrze: " << score;
	return 0;
}



