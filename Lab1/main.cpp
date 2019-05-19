#include "Schrage.h"
#include "Carlier.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>

int main()
{
	int score = 0;
	int i = 2;
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
			std::cout << "\n DOBRZE! \n";
		}
			
	}
	cout << "by³o dobrze: " << score;
	return 0;
}



