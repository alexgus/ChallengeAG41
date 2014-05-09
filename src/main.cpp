#include <cstdlib>

#include <iostream>
#include <iomanip>

#include "ImportData.h"
#include "Arbre.h"

#define SETW 6

using namespace std;

/**
 * print a matrix
 */
void printTable(int *d, int max)
{
    int i;

    for(i=0; i<max; i++)
    	cout << setw(SETW) << d[i];
}

int main()
{
// Declaration
	int i;
	data *d;
	ImportData *imp;
	Arbre *arbre;

// Initialize
	cout << "Initializing Data" << endl;
	imp = new ImportData();
	d = imp->getData();

	cout << "Initialized constants :" 		 << endl
		 << "n    : " << d->n				 << endl
		 << "m    : " << d->m				 << endl
		 << "c    : " << d->c				 << endl
		 << "eta  : " << d->eta				 << endl
		 << "beta : " << d->beta			 << endl
		 << "tau  : Distance entre le fournisseur et les clients" << endl;
    for(i=1; i<=MAX_TAU; i++)
    	cout << setw(SETW) << i;
    cout << endl;
    printTable(d->tau, MAX_TAU);

    cout << endl << endl << endl
    	<< "Dates dues et clients associés aux produits demandés" << endl
    	<< " i ";
    for(i=1; i<=d->n; i++)
       	cout << setw(SETW) << i;
    cout << endl;
	cout << "cl "; printTable(d->cl, d->n);
	cout << endl;
	cout << "di "; printTable(d->d, d->n);

// Begin
	arbre = new Arbre(d);
	arbre->start();

// Finalize
	delete imp;
	delete arbre;
	free(d);
	return EXIT_SUCCESS;
}
