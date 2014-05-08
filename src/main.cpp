#include <cstdlib>

#include <iostream>

#include "ImportData.h"

using namespace std;

int main()
{
// Declaration
	data *d;
	ImportData *imp;

// Initialize
	cout << "Initialize Data" << endl;
	imp = new ImportData();
	d = imp->getData();

	cout << "Initialized constants :" << endl;
	cout << "n    : " << d->n    << endl;
	cout << "m    : " << d->m    << endl;
	cout << "c    : " << d->c    << endl;
	cout << "eta  : " << d->eta  << endl;
	cout << "beta : " << d->beta << endl;

// Begin

// Finalize
	delete imp;
	return EXIT_SUCCESS;
}
