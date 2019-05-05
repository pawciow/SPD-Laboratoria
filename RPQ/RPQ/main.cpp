#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <string>
#include "Kopiec.h"
#include "RPQ.h"
#include "Zadanie.h"

using namespace std;


int main() {
	char pause;

	char wej[10]  = "in100.txt";
	char wyj[11] = "out100.txt";

	RPQ test(wej);
	test.Schrage();
	
	cout << "Cmax znalezionego: " << test.Cmax << endl;
	ofstream plikout(wyj);

	plikout << "1 " << test.n << endl;
	for (int i = 0;i < test.n;i++) {
		plikout << test.listaZadan[i].nr << " ";
	}
	plikout << endl << test.Cmax;
	plikout.close();

	cin >> pause;
	return 0;
}








