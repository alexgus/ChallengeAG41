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
 * Data of the file
 */
data *d;

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
	ImportData *imp;
	CostTab *t;
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

	// Get first solution
	t->calculatePerfectTime();
	t->getSol()->printSolution();
	// Get second solution
	t->getSol()->separateBatch();
	cout << "================== Separate :" << endl << endl;
	t->getSol()->printSolution();

	// TODO Branch and cut
	// Separate batch (batch are grouped if there's no time to deliver them next)
	vector<double> *bpc = new vector<double>[d->m*d->n];
	int *nbNewClient = new int[d->m];

	for(i = 0; i < d->m ; ++i)
		nbNewClient[i] = 0;

	for(i=0;i<d->n;++i)
	{
		const int index = (d->n*(d->cl[i]-1));
		if(nbNewClient[(d->cl[i])-1] != 0)
		{
			// Check if we can deport the current product in other client or if the client reached the limit of the transporter
			int j = 0;

			double tl = d->tau[d->cl[i]-1];
			double date = d->d[i];
			double dateL = bpc[index + j].at(0);
			while(j < nbNewClient[d->cl[i]-1]
			    && !((int) bpc[index + j].size() >= d->c
			    ||date >= dateL + tl
			    ||date <= dateL - tl))
			    j++;

			if(j < nbNewClient[d->cl[i]-1]) // Insert in a new client
			{
				bpc[index+nbNewClient[d->cl[i]-1]] = vector<double>();
				bpc[index+nbNewClient[d->cl[i]-1]].push_back(d->d[i]);
				++nbNewClient[d->cl[i]-1];
			}
			else
				bpc[index].push_back(d->d[i]);
		}
		else
		{
			bpc[index] = vector<double>();
			bpc[index].push_back(d->d[i]);
			++nbNewClient[d->cl[i]-1];
		}
	}

	for(i = 0 ; i < d->m*d->n; ++i)
	{
		cout << "N :" << i << "\t";
		for(vector<double>::iterator it = bpc[i].begin(); it != bpc[i].end();++it)
			cout << *it << " ";
		cout <<endl;
	}



	// Create tab of Client object
	// Evaluate

// Finalize
	delete imp;
	delete t;
	return EXIT_SUCCESS;
}
