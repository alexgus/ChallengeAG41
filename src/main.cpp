#include <cstdlib>
#include <cstring>


#include <iostream>
#include <iomanip>

#include "ImportData.h"
#include "CostTab.h"

#include <vector>

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

/**
 * print a matrix
 */
void printTable(double *d, int max)
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
	CostTab *t;
	Solution *solution;
// Initialize
	handle_arg(argc, argv);
	// Data
	imp = new ImportData();
	d = imp->getData();

	if(verbose)
	{
		cout << "================== Initialized constants :" 		 << endl
				<< "n    : " << d->n				 << endl
				<< "m    : " << d->m				 << endl
				<< "c    : " << d->c				 << endl
				<< "eta  : " << d->eta				 << endl
				<< "tau  : Distance entre le fournisseur et les client et cout associés" << endl;
		for(i=1; i<=d->m; i++)
			cout << setw(SETW) << i;
		cout << endl;
		printTable(d->tau, d->m);
		cout << endl;
		printTable(d->beta, d->m);

		cout << endl
				<< "Dates dues et clients associés aux produits demandés" << endl
				<< " i ";
		for(i=1; i<=d->n; i++)
			cout << setw(SETW) << i;
		cout << endl;
		cout << "cl "; printTable(d->cl, d->n);
		cout << endl;
		cout << "di "; printTable(d->d, d->n);
		cout << endl;
	}

	// Structure
	t = new CostTab(d);

	if(verbose)
	{
		cout << endl << "================== Begin :";
		cout << endl << "--> Base Matrix <--" << endl;
		t->printCost();
	}

// Begin
	Client* c;

	// TODO Algorithm
t->calculatePerfectTime();

	// Evaluate the solution
	solution = t->getSol();

	solution->evaluate();

	if(verbose)
	{
		cout << endl <<"==================  Solution :" << endl <<
				"Begin time : " << solution->getTime() << endl;
		for(vector<Client*>::iterator it = solution->getClient()->begin(); it != solution->getClient()->end(); ++it)
			cout << "Client " << (*it)->getId() << " received its order number " << (*it)->getId2() << endl;
	}

	cout << "Final value of the solution " << solution->getEval() << endl;

// Finalize
	delete imp;
	delete t;
	return EXIT_SUCCESS;
}
