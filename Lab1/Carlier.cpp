#include "Carlier.h"


using namespace std;

Carlier::Carlier()
{}

int Carlier::carlier(vector<RPQ> taskVector, int UB)
{
	unsigned int a = 0; // numer pierwszego zadania w bloku K
	unsigned int b = 0; // numer ostatniego zadania w bloku K
	unsigned int c = 0; // numer zadania przeszkadzajacêgo, interference job

	unsigned int U, LB;
	//U = __UB__;
	int i = 0;
	cout << "\n Na poczatku: " << UB << " Wielkoœæ taskvectora: " << taskVector.size()<< endl;
	//unsigned int R_PERMUTACJI_WYKONANIA_ZADAN_NA_MASZYNIE; //?? by³o u http://new.zsd.iiar.pwr.wroc.pl/files/zadania/CARLIER/AC.pdf

	Schrage schrage;
	schrage.LoadTasks(taskVector);
	U = schrage();
	////////// KROK 2
	if (U < UB)
	{
		cout << "Wielkosc taskVectora: " << taskVector.size() << endl;
		cout << "Wielkosc schrage vectora: " << schrage.resultOrder.size() << endl;
		UB = U;
		taskVector = schrage.resultOrder;
	}

	////////// KROK 3
	b = find_b(taskVector, U);
	if (b == -1)
	{
		//std::cerr << " B to minus jeden! Zwracam:" << u;
		return UB; // Tego nie powinno byæ. To zapobiega wywalaniu, ale to jest Ÿle. Trzeba ogarn¹æ sk¹d to jest.

	}

	a = find_a(taskVector, U, b);
	c = find_c(taskVector, U, a, b);

	if (c == -1)
	{
		cout << "END "<< U << "\n";
		return U;
	}

	// Krok 5:

	RPQ temporary = findH(c, b, taskVector);
	cout << "min_r " << temporary.R << "suma p " << temporary.P << "min_Q " << temporary.Q << endl;

	// Krok 6
	 if (toRemember_R == -1)
	{
		toRembember_NR = taskVector[c].NR;
		toRemember_R = taskVector[c].R;
	}
	taskVector[c].R = max({ taskVector[c].R, temporary.R + temporary.P });

	RPQ temp2 = findH(c - 1, b, taskVector);

	// Krok 7
	SchragePmtn schragePmtn;
	schragePmtn.LoadTasks(taskVector);
	LB = schragePmtn();
	LB = std::max({ LB, 
		temporary.R+temporary.P+temporary.Q,
		temp2.R+taskVector[c].R, temp2.P+taskVector[c].P, temp2.Q+taskVector[c].Q
	});

	// Krok 8
	if (LB < UB)
	{
		cout << "Left child: " << U << std::endl;
		//UB = LB;
		UB = carlier(taskVector, LB);
	}
	else
	{
		cout << "\nzmieniam\n";

	}

	
	// Krok 10
	for (auto & e : taskVector)
	{
		if (e.NR == toRembember_NR)
			e.R = toRemember_R;
	}
	toRemember_R = -1;
	// Krok 11
	if (toRemember_Q == -1)
	{
		toRembember_NR = taskVector[c].NR;
		toRemember_Q = taskVector[c].Q;
	}
	taskVector[c].Q = max({ taskVector[c].Q, temporary.Q + temporary.P });
	// Krok 12
	SchragePmtn schragePmtn2;
	schragePmtn2.LoadTasks(taskVector);
	LB = schragePmtn2();
	LB = std::max({ LB,
	temporary.R + temporary.P + temporary.Q,
	temp2.R + taskVector[c].R, temp2.P + taskVector[c].P, temp2.Q + taskVector[c].Q
		});
	//LB = std::max({ LB, temporary.Q + temporary.P + temporary.R, temp2.R + temp2.P, temp2.Q });
	// Krok 13
	if (LB < UB)
	{
		cout << "Right child: " << U << std::endl;
		//UB = LB;
		UB = carlier(taskVector, LB);
	}


	// Krok 15
	for (auto & e : taskVector)
	{
		if (e.NR == toRembember_NR)
			e.Q = toRemember_Q;
	}
	toRemember_Q = -1;

	return UB;

}



int Carlier::find_b(std::vector<RPQ> _tasks, int Cmax)
{

	unsigned int i = 0;
	for (i = 0; i < _tasks.size(); i++)
		if (Cmax == _tasks[i].timeWhenItsFinished + _tasks[i].Q)
			return i;
	
	return -1;
}

int Carlier::find_a(std::vector<RPQ> _tasks, int Cmax, int b)
{
	for (unsigned int a = 0; a < b; a++)
	{

		unsigned int sum = 0;
		for (unsigned int i = a; i <= b; i++)
			sum = sum + _tasks[i].P;

		if (_tasks[a].R + _tasks[b].Q + sum == Cmax)
			return a;
	}
	return -1;

}

int Carlier::find_c(std::vector<RPQ> _tasks, int Cmax, int a, int b)
{
	for (int i = b; i >= a; i--)
	{
		if (_tasks[i].Q < _tasks[b].Q)
		{
			return i;
		}
	}

	return -1;
}



Carlier::~Carlier() {}

void Carlier::LoadTasks(std::string fileName)
{
	std::ifstream fileStream(fileName);
	unsigned int  size;
	unsigned int r, p, q;
	fileStream >> size >> resultFromMakuchowski;
	for (unsigned int i = 0; i < size; i++)
	{
		fileStream >> r >> p >> q;
		quickFIXVector.push_back({ r,p,q,i + 1 });
	}
	fileStream.close();
}

RPQ Carlier::findH(int c, int b, std::vector<RPQ> taskVector)
{
	RpqComparatorByR by_R;
	RpqComparatorByQ by_Q;

	unsigned int TMP1 = 0, TMP2 = 0, sumP = 0;
	for (unsigned int i = c; i <= b; i++) // but i guess it should be b, not b+1
	{
		sumP =+ taskVector[i].P;
	}
	TMP1 = max_element(taskVector.begin() + (c), taskVector.begin() + b+1, by_R)->R; // Hax because min_element() gives  the biggest because of comparator
	TMP2 = min_element(taskVector.begin() + (c), taskVector.begin() + b+1, by_Q)->Q;

	return {TMP1, sumP, TMP2, 987};

}
