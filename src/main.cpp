#include <cstdlib>
#include <cstring>


#include <iostream>
#include <iomanip>

#include "ImportData.h"
#include "Tab.h"

#define SETW 5

using namespace std;

/**
 * Display all information if it is true.
 * Command line option '-v'
 */
bool verbose = false;

/**
 * print a matrix
 */
void printTable(int *d, int max)
{
    int i;

    for(i=0; i<max; i++)
    	cout << setw(SETW) << d[i];
}

void handle_arg(int argc, char *argv[])
{
	int i;
	for(i=0;i< argc ; i++)
	{
		if(strcmp("-v",argv[i]) == 0)
			verbose = true;
	}
}

int main(int argc, char *argv[])
{
// Declaration
	int i;
	data *d;
	ImportData *imp;
	Tab *t;

// Initialize
	handle_arg(argc, argv);
	if(verbose)
	{
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
		for(i=1; i<=d->c; i++)
			cout << setw(SETW) << i;
		cout << endl;
		printTable(d->tau, d->c);

		cout << endl << endl << endl
			<< "Dates dues et clients associés aux produits demandés" << endl
			<< " i ";
		for(i=1; i<=d->n; i++)
			cout << setw(SETW) << i;
		cout << endl;
		cout << "cl "; printTable(d->cl, d->n);
		cout << endl;
		cout << "di "; printTable(d->d, d->n);
	}

	t = new Tab(d);
// Begin



// Finalize
	delete imp;
	return EXIT_SUCCESS;
}
