#include "RPQ.h"

using namespace std;

RPQ::RPQ(char * nazwa_pliku)
{
	int rozmiar;				//zmienna pozorowana. trzeba gdzies wczytac "3"
	ifstream plikin(nazwa_pliku);
	plikin >> n;
	plikin >> rozmiar;
	Zadanie * wczytywane;
	int rr, pp, qq;
	for (int i = 0; i < n; i++) {
		plikin >> rr >> pp >> qq;
		wczytywane = new Zadanie(rr, pp, qq, i + 1);
		listaZadan.push_back(*(wczytywane));
		delete wczytywane;
	}
	plikin.close();
}


int RPQ::Schrage()
{
	int aktualnyCzas = 0;
	int _Cmax = 0;

	Kopiec<Zadanie> kopiecZadan(&Zadanie::compR);						//kopiec z wszystkimi zadaniami posortowanymi wg. R
	for (int i = 0; i < n; i++)
		kopiecZadan.push(listaZadan[i]);

	Kopiec<Zadanie> dostepneZadania(&Zadanie::compQ);					//kopiec dostepnych w danej chwili czasowej zadan; posortowana od najwiêkszego Q
	vector<Zadanie> listaSchrage;										//lista uszeregowana wg. algorytmu Schrage'a. pod koniec metody podpinana pod listeZadan

	while ((!kopiecZadan.empty()) || (!dostepneZadania.empty())) {
		while ((!kopiecZadan.empty()) && (kopiecZadan.top().r <= aktualnyCzas)) {
			dostepneZadania.push(kopiecZadan.top());
			kopiecZadan.pop();
		}

		if (dostepneZadania.empty()) {
			aktualnyCzas = kopiecZadan.top().r;
		}
		else {
			listaSchrage.push_back(dostepneZadania.top());		//dodajesz zadanie do listy
			dostepneZadania.pop();								//usuwa zadanie z puli dostepnych 
			listaSchrage.back().t_on = aktualnyCzas;		//ustawia realny czas rozpoczecia realizacji zadania na maszynie
			aktualnyCzas += listaSchrage.back().p;		//aktualizuje czas

			if (aktualnyCzas + listaSchrage.back().q > _Cmax)
				_Cmax = aktualnyCzas + listaSchrage.back().q;
		}
	}
	/*tu zmienione */
	Cmax = _Cmax;
	listaZadan.clear();
	listaZadan = listaSchrage;
	listaSchrage.clear();
	return Cmax;
}

int RPQ::SchragePtm()
{
	int aktualnyCzas = 0;
	int _Cmax = 0;

	vector<Zadanie>listaNieprzydzielonych;								//ze wzgledu na koniecznoœæ swobodnego dostepu do wszystkich zadan nie mozna tego realizowac na kopcu.
	listaNieprzydzielonych = listaZadan;								//tworzymy kopie listy zadan
	sort(listaNieprzydzielonych.begin(), listaNieprzydzielonych.end(), Zadanie::compR);

	Kopiec<Zadanie> listaDostepnych(&Zadanie::compQ);					//kopiec dostepnych w danej chwili czasowej zadan. Posortowany od najwiekszego Q

	vector<Zadanie> listaSchrage;										//lista uszeregowana wg. algorytmu Schrage'a. pod koniec metody podpinana pod listeZadan

	Kopiec<Zadanie> listaPrzerwan(&Zadanie::compQ);						//lista tych zadan, na rzecz ktorych moze wystapic przerwanie.
																		//Posortowana od najmniejszego R

	while ((!listaNieprzydzielonych.empty()) || (!listaDostepnych.empty())) {
		while ((!listaNieprzydzielonych.empty()) && (listaNieprzydzielonych.back().r <= aktualnyCzas)) {
			listaDostepnych.push(listaNieprzydzielonych.back());					//tworzymy listê zadan, ktorych r juz uplynelo
			listaNieprzydzielonych.pop_back();
		}

		if (listaDostepnych.empty()) {
			aktualnyCzas = listaNieprzydzielonych.back().r;
		}
		else {
			while (!listaPrzerwan.empty())
				listaPrzerwan.pop();								//czyszczenie listy przerwan  

			for (int i = 0; i < (int)listaNieprzydzielonych.size();i++)	//tworzenie nowej listy przerwan
				if ((listaDostepnych.top().p + aktualnyCzas > listaNieprzydzielonych[i].r) && (listaDostepnych.top().q < listaNieprzydzielonych[i].q))
					listaPrzerwan.push(listaNieprzydzielonych[i]);	//na liste przerwan kladziemy te zadania, ktorych q jest wieksze od aktualnie dodawanego algorytmem Schrage'a
																	//a r miesci sie w przedziale (aktualnyCzas, aktualnyCzas+p dodawanego). Na rzecz tych zadan powinno wyst¹piæ przerwanie.
																	//elementy na liscie przerwan sa kopiami!

			if (listaPrzerwan.empty()) {							//nie ma przerwan - normalna procedura Schrage'a
				listaSchrage.push_back(listaDostepnych.top());		//dodajesz zadanie do listy
				listaDostepnych.pop();								//usuwa zadanie z puli dostepnych 
				listaSchrage.back().t_on = aktualnyCzas;				//ustawia realny czas rozpoczecia realizacji zadania na maszynie
				aktualnyCzas += listaSchrage.back().p;				//aktualizuje czas

				if (aktualnyCzas + listaSchrage.back().q > _Cmax)
					_Cmax = aktualnyCzas + listaSchrage.back().q;
			}
			else {							//przerwanie
				Zadanie part1 = listaDostepnych.top();
				listaDostepnych.pop();
				Zadanie part2 = part1;

				part1.p = listaPrzerwan.top().r - aktualnyCzas;			//czêœæ zadania, która zrealizuje siê do momentu przerwania. 
				part2.p -= part1.p;									//pozosta³a czêœæ zadania: od part2.p (==part1.p oryginalnego) odejmujesz czêœæ, która bêdzie zrealizowana
				listaDostepnych.push(part2);						//reszta realizowanego zadania trafia spowrotem do listy dostepnych zadan

				listaSchrage.push_back(part1);
				listaSchrage.back().t_on = aktualnyCzas;
				aktualnyCzas += listaSchrage.back().p;

				if (aktualnyCzas + listaSchrage.back().q > _Cmax)
					_Cmax = aktualnyCzas + listaSchrage.back().q;

			}
		}
	}

	/* tu zmienione */
	Cmax = _Cmax;
	listaZadan.clear();
	listaZadan = listaSchrage;
	listaSchrage.clear();
	return Cmax;
}

ostream & operator << (ostream & strumienWyjsciowy, RPQ & doWypisania)
{
	for (int i = 0; i < (int)doWypisania.listaZadan.size(); i++)
		strumienWyjsciowy << doWypisania.listaZadan[i];

	return strumienWyjsciowy;
}