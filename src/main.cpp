#include <cstdlib>

#include <iostream>
#include <iomanip>

#include "ImportData.h"

#define SETW 6

using namespace std;

typedef unsigned int date;

/**
 * print a matrix
 */
void printMatrix(int d[MAX_TAU])
{
    int i;

    for(i=1; i<=MAX_TAU; i++)
    	cout << setw(SETW) << i;
    cout << endl;
    for(i=0; i<MAX_TAU; i++)
    	cout << setw(SETW) << d[i];
}

int main()
{
// Declaration
	data *d;
	ImportData *imp;

// Initialize
	cout << "Initialize Data" << endl;
	imp = new ImportData();
	d = imp->getData();

	cout << "Initialized constants :" 		 << endl
		 << "n    : " << d->n				 << endl
		 << "m    : " << d->m				 << endl
		 << "c    : " << d->c				 << endl
		 << "eta  : " << d->eta				 << endl
		 << "beta : " << d->beta			 << endl
		 << "tau  : " << endl; printMatrix(d->tau);

// Begin

// Finalize
	delete imp;
	return EXIT_SUCCESS;
}
