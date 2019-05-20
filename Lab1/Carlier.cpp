#include "Carlier.h"


using namespace std;

Carlier::Carlier() : U(0), UB(INT_MAX), LB(0)
{}

int Carlier::carlier(vector<RPQ> taskVector, int __UB__)
{
	unsigned int a = 0; // numer pierwszego zadania w bloku K
	unsigned int b = 0; // numer ostatniego zadania w bloku K
	unsigned int c = 0; // numer zadania przeszkadzajacêgo, interference job

	U = __UB__;
	int i = 0;
	//unsigned int R_PERMUTACJI_WYKONANIA_ZADAN_NA_MASZYNIE; //?? by³o u http://new.zsd.iiar.pwr.wroc.pl/files/zadania/CARLIER/AC.pdf

	Schrage schrage;
	schrage.LoadTasks(taskVector);

	SchragePmtn schragePmtn;

	U = schrage();
	////////// KROK 2
	if (U < UB)
	{
		UB = U;
		taskVector = schrage.resultOrder;
	}

	////////// KROK 3
	b = find_b(taskVector, U);
	if (b == -1)
	{
		std::cerr << " B to minus jeden! taskVector: \n";
		for (auto e : taskVector)
			std::cerr << e.NR << " " << e.R << " " << e.P << " " << e.Q << endl;
		return U; // Tego nie powinno byæ. To zapobiega wywalaniu, ale to jest Ÿle. Trzeba ogarn¹æ sk¹d to jest.

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

	// Krok 7
	schragePmtn.LoadTasks(taskVector);
	LB = schragePmtn();

	// Krok 8
	if (LB < UB)
	{
		cout << "PRZED WEJŒCIEM W PIERWSZEGO IFA: " << U << std::endl;
		taskVector = schragePmtn.resultOrder;
		U = carlier(taskVector, U); // Krok 9
	}
	// Krok 10
	for (auto & e : taskVector)
	{
		if (e.NR == toRembember_NR)
			e.R = toRemember_R;
	}
	toRemember_R = -1;
	// Krok 11
	if (toRemember_P = -1)
	{
		toRembember_NR = taskVector[c].NR;
		toRemember_P = taskVector[c].P;
	}


	temporary = findH(c, b, taskVector);
	taskVector[c].Q = max({ taskVector[c].Q, temporary.Q + temporary.P });
	// Krok 12
	SchragePmtn schragePmtn2;
	schragePmtn2.LoadTasks(taskVector);
	LB = schragePmtn2();

	// Krok 13
	if (LB < UB)
	{
		cout << "PRZED WEJŒCIEM W DRUGIEGO IFA: " << U << std::endl;
		taskVector = schragePmtn2.resultOrder;
		U = carlier(taskVector, UB); // Krok 14
	}

	// Krok 15
	for (auto & e : taskVector)
	{
		if (e.NR == toRembember_NR)
			e.P = toRemember_P;
	}
	toRemember_P = -1;
	return U;

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
	for (unsigned int i = c + 1; i < b + 1; i++)
	{
		sumP = +taskVector[i].P;
	}
	TMP1 = min_element(taskVector.begin() + c + 1, taskVector.begin() + b, by_R)->R;
	TMP2 = max_element(taskVector.begin() + c + 1, taskVector.begin() + b, by_Q)->Q;

	return {TMP1, sumP, TMP2, 987};

}
