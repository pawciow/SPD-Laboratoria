
#include "Carlier.h"


using namespace std;

Carlier::Carlier()
{}

int Carlier::carlier(vector<RPQ> taskVector, int UB)
{
	unsigned int a = 0; // numer pierwszego zadania w bloku K
	unsigned int b = 0; // numer ostatniego zadania w bloku K
	unsigned int c = 0; // numer zadania przeszkadzajacêgo, interference job
	unsigned int toRemember_R{};
	unsigned int toRembember_NR{};
	unsigned int toRemember_Q{};
	unsigned int U, LB;
	//U = __UB__;
	int i = 0;
	cout << "\n	       Na poczatku: " << UB << endl;
	Schrage schrage;
	schrage.LoadTasks(taskVector);
	U = schrage();
	////////// KROK 2
	if (U < UB)
	{
		cout << "Zmieniam " << UB << " na " << U << endl;
		UB = U;
		taskVector = schrage.resultOrder;
	}


	////////// KROK 3
	b = find_b(taskVector, U);
	if (b == -1)
	{
		std::cerr << "   B to minus jeden! Zwracam:" << UB;
		return UB; // Tego nie powinno byc. To zapobiega wywalaniu, ale to jest zle. Trzeba ogarn¹æ sk¹d to jest.

	}

	a = find_a(taskVector, U, b);
	if (a == -1)
	{
		std::cerr << " A to minus jeden! Zwracam: " << UB << endl;
		return UB;
	}
	c = find_c(taskVector, U, a, b);

	if (c == -1)
	{
		cout << "END " << U << "\n";
		return U;
	}

	cout << "A numer: " << taskVector[a].NR << " B numer: " << taskVector[b].NR << " C numer: " << taskVector[c].NR << endl;
	cout << "A: " << a << " B: " << b << "C: " << c << endl;
	// Krok 5:

	RPQ temporary = findH(c, b, taskVector);
	cout << "BLOK K" << endl;
	cout << "min_r " << temporary.R << "suma p " << temporary.P << "min_Q " << temporary.Q << endl;

	// Krok 6
	toRembember_NR = taskVector[c].NR;
	toRemember_R = taskVector[c].R;

	taskVector[c].R = max({ taskVector[c].R, temporary.R + temporary.P });
	cout << "New R: " << taskVector[c].R << endl;
	RPQ temp2 = findH(c - 1, b, taskVector);

	// Krok 7
	SchragePmtn schragePmtn;
	schragePmtn.LoadTasks(taskVector);
	LB = schragePmtn();
	cout << "LB: " << LB << " H{K}: " << temporary.width() << "H(K u {C}): " << temp2.width() << endl;
	LB = std::max({ LB,
		temporary.width(),
		temp2.width()
		});

	//Testy eliminacyjne
	testyEliminacyjne(a, b, taskVector, temporary, UB);
	/******************************* ZOBACZYĆ CZY TO TUTAJ       *************************************/
	// Krok 8
	if (LB < UB)
	{
		cout << "Left child enters with: " << UB << std::endl;
		UB = carlier(taskVector, UB);
		cout << "And Left child returns with: " << UB << endl << endl;
	}
	else
	{
		cout << "No left child " << UB << endl;
	}
	


	// Krok 10
	for (auto & e : taskVector)
	{
		if (e.NR == toRembember_NR)
			e.R = toRemember_R;
	}


	// Krok 11	
	toRembember_NR = taskVector[c].NR;
	toRemember_Q = taskVector[c].Q;
	taskVector[c].Q = max({ taskVector[c].Q, temporary.Q + temporary.P });
	cout << "New Q: " << taskVector[c].Q << endl;

	// Krok 12
	SchragePmtn schragePmtn2;
	schragePmtn2.LoadTasks(taskVector);
	LB = schragePmtn2();
	temp2 = findH(c - 1, b, taskVector);

	cout << "LB: " << LB << " H{K}: " << temporary.width() << "H(K u {C}): " << temp2.width() << endl;

	//Testy eliminacyjne
	testyEliminacyjne(a, b, taskVector, temporary, UB);
	/******************************* ZOBACZYĆ CZY TO TUTAJ       *************************************/
	LB = max({
		LB,
		temporary.width(),
		temp2.width()
		});



	// Krok 13
	if (LB < UB)
	{
		cout << "Right child enters with: " << UB << std::endl;
		UB = carlier(taskVector, UB);
		cout << "And Right child returns with: " << UB << endl;
	}
	else
	{
		cout << "No right child \n";
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
	for (i = _tasks.size() - 1; i > 0; i--)
		if (Cmax == _tasks[i].timeWhenItsFinished + _tasks[i].Q)
			return i;

	return -1;
}

int Carlier::find_a(std::vector<RPQ> _tasks, int Cmax, int b)
{
	for (unsigned int a = 0; a <= b; a++)
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


	cout << "\n    Counting for: ";
	unsigned int TMP1 = 0, TMP2 = 0, sumP = 0;
	for (unsigned int i = c + 1; i <= b; i++)
	{
		cout << i << " ";
		sumP = sumP + taskVector[i].P;
	}
	TMP1 = max_element(taskVector.begin() + (c + 1), taskVector.begin() + b + 1, by_R)->R; // Hax because min_element() gives  the biggest because of comparator
	TMP2 = min_element(taskVector.begin() + (c + 1), taskVector.begin() + b + 1, by_Q)->Q;

	cout << endl;
	return { TMP1, sumP, TMP2, 987 };

}

void Carlier::testyEliminacyjne(int a, int b, std::vector<RPQ> taskVector, RPQ k, int UB)
{
	cout << "\n\n	TESTY ELIMINACYJNE \n" ;
	vector<int>  L;
	/*for (unsigned int i = 0; i < a; i++)
	{
		cout << "Sprawdzam : " << i << " ";
		if (taskVector[i].P > UB - k.width())
			L.push_back(i);
	}
	for (unsigned int i = b; i < taskVector.size(); i++)
	{
		cout << i << " ";
		if (taskVector[i].P > UB - k.width())
			L.push_back(i);
	}*/
	/*
	cout << "Sprawdzam : "; 
	for (int i = 0; i < taskVector.size(); i++)
	{
		cout << i << " ";
		if (taskVector[i].P > UB - k.width())
			L.push_back(i);
	}

	for(auto & e : L)
		cout << "\n Znaleziono: " << e << " ";
	*/
	for (auto & e : L)
	{
		if ((taskVector[e].R + taskVector[e].P + k.P + taskVector[b].Q) >= UB)
		{
			taskVector[e].R = max({ taskVector[e].R, (k.R + k.P) });
			cout << " \n Spelniono warunek 1 dla: " << e;
		}
		if ((k.R + taskVector[e].P + k.P + taskVector[b].Q) >= UB)
		{
			taskVector[e].Q = max({ taskVector[e].Q, k.Q + k.P });
			cout << " \n Spelniono warunek 2 dla: " << e << endl << endl;
		}
	}
}

