#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <string>

using namespace std;

template <class T>
class Kopiec
{
private:
	T * tablicaElementow;
	int iloscElementow;
	bool(*funkcjaPorownujaca)(const T &, const T &);
public:
	int push(T element);
	T pop();
	T top();
	bool empty();
	void wypisz();
	Kopiec(bool(*compare)(const T &, const T &));

};

template <class T>
Kopiec<T>::Kopiec(bool(*cmp)(const T &, const  T &))
{
	iloscElementow = 0;
	funkcjaPorownujaca = cmp;
	tablicaElementow = NULL;
}

template <class T>
int Kopiec<T>::push(T element)
{

	if (iloscElementow == 0) { //dodajemy na szczyt kopca
		tablicaElementow = new T[1];
		tablicaElementow[iloscElementow] = element;
		iloscElementow++;
		return 1;
	}
	else {
		T * temp = tablicaElementow;
		tablicaElementow = new T[iloscElementow + 1];
		copy(temp, temp + iloscElementow, tablicaElementow);
		delete[] temp;

		int aktualnyIndeks = iloscElementow;
		int indeksOjca = iloscElementow / 2;
		T tmp;

		tablicaElementow[iloscElementow] = element;
		while ((indeksOjca >= 0) && (funkcjaPorownujaca(tablicaElementow[indeksOjca], tablicaElementow[aktualnyIndeks])))
		{
			tmp = tablicaElementow[indeksOjca];
			tablicaElementow[indeksOjca] = tablicaElementow[aktualnyIndeks];
			tablicaElementow[aktualnyIndeks] = tmp;

			aktualnyIndeks = indeksOjca;
			indeksOjca /= 2;
		}
		iloscElementow++;
		return iloscElementow;
	}
}

template <class T>
T Kopiec<T>::pop()
{
	T doZwrotu;
	if (iloscElementow == 0)
	{
		cerr << "Brak elementow na kopcu!" << endl;
		return doZwrotu;
	}
	doZwrotu = tablicaElementow[0];
	tablicaElementow[0] = tablicaElementow[iloscElementow - 1];
	int aktualnyIndeks = 0;

	while ((((aktualnyIndeks + 1) * 2 - 1 < iloscElementow - 1) && (funkcjaPorownujaca(tablicaElementow[aktualnyIndeks], tablicaElementow[(aktualnyIndeks + 1) * 2 - 1]))) || //jezeli ktores z dzieci jest wieksze - zamien z wiekszym z nich
		(((aktualnyIndeks + 1) * 2 < iloscElementow - 1) && (funkcjaPorownujaca(tablicaElementow[aktualnyIndeks], tablicaElementow[(aktualnyIndeks + 1) * 2]))))
	{
		if (funkcjaPorownujaca(tablicaElementow[(aktualnyIndeks + 1) * 2 - 1], tablicaElementow[(aktualnyIndeks + 1) * 2])) //je¿eli prawe dziecko jest wieksze 
		{																											// to z nim zamieniamy aktualny indeks
			T tmp = tablicaElementow[(aktualnyIndeks + 1) * 2];
			tablicaElementow[(aktualnyIndeks + 1) * 2] = tablicaElementow[aktualnyIndeks];
			tablicaElementow[aktualnyIndeks] = tmp;
			aktualnyIndeks = (aktualnyIndeks + 1) * 2;
		}
		else
		{
			T tmp = tablicaElementow[(aktualnyIndeks + 1) * 2 - 1];
			tablicaElementow[(aktualnyIndeks + 1) * 2 - 1] = tablicaElementow[aktualnyIndeks];
			tablicaElementow[aktualnyIndeks] = tmp;
			aktualnyIndeks = (aktualnyIndeks + 1) * 2 - 1;
		}
	}
	iloscElementow--;

	T * temp = tablicaElementow;
	tablicaElementow = new T[iloscElementow];
	copy(temp, temp + iloscElementow, tablicaElementow);

	delete[] temp;
	return doZwrotu;
}

template <class T>
T Kopiec<T>::top()
{
	T doZwrotu;
	if (iloscElementow == 0)
	{
		cerr << "Brak elementow na kopcu!\n";
		return doZwrotu;
	}
	doZwrotu = tablicaElementow[0];
	return doZwrotu;
}

template <class T>
void Kopiec<T>::wypisz()
{
	for (int i = 0; i < iloscElementow; i++)
	{
		cout << "Indeks: " << i << " wartosc: " << tablicaElementow[i] << endl;
	}
}

template <class T>
bool Kopiec<T>::empty()
{
	if (iloscElementow == 0)
		return true;
	else
		return false;
}
