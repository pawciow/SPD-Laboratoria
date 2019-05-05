#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <string>

#include "Zadanie.h"
#include "Kopiec.h"

using namespace std;

class RPQ
{
public:
	vector<Zadanie> listaZadan; //vector przechowujacy zadan¹ kolejnosc wykonywania zadan
	int n;						//ilosc wczytanych zadan
	int Cmax;					//moment zakonczenia q ostatniego zadania
	int LB;						//wartosc Cmax zwrocona przez algorytm Schrage z przerywaniami
	int a, b;					//indeksy pocz¹tku i konca sciezki krytycznej
	int c;						//indeks zadania interferencyjnego
	int sLB;					//szybki LB. wg tego permutacje s¹ kopcowane;


	int Schrage();				//algorytm Schrege'a: modyfikuje kolejnosc listyZadan

	int SchragePtm();			//metoda zwraca wartosc Cmax algorytmu Schrage z przerywaniami. Modyfikuje pole LB

	static bool cmpsLB(const RPQ & p1, const RPQ & p2) {
		return p1.sLB < p2.sLB;
	}

	friend ostream & operator << (ostream & strumienWyjsciowy, RPQ & doWypisania);

	RPQ(char * nazwa_pliku);
};