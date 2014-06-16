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
		if(nbNewClient[(d->cl[i])-1] != 0)
		{
			int j = 0;
			int date = d->d[i];
			int nb = nbNewClient[(d->cl[i])-1];
			int tmp = bpc[(d->n*(d->cl[i]-1))+j].at(bpc[(d->n*(d->cl[i]-1))+j].size()-1);
			int dateF = tmp + d->tau[(d->cl[i]-1)];
			int dateD = *bpc[(d->n*(d->cl[i]-1))+j].begin() - d->tau[d->cl[i]-1];
			while((j < nbNewClient[(d->cl[i])-1]) && // Search if there's time to deliver it before or after
					(d->d[i] >= *bpc[(d->n*(d->cl[i]-1))+j].begin() - d->tau[d->cl[i]-1]
							&& d->d[i] <= ((bpc[(d->n*(d->cl[i]-1))+j].at(bpc[(d->n*(d->cl[i]-1))+j].size()-1)) + d->tau[(d->cl[i]-1)])))
			{
				date = d->d[i];
				nb = nbNewClient[(d->cl[i])-1];
				dateF = ((*bpc[(d->n*(d->cl[i]-1))+j].end()-1) + d->tau[(d->cl[i]-1)]);
				dateD = *bpc[(d->n*(d->cl[i]-1))+j].begin() - d->tau[d->cl[i]-1];

				++j;
			}

			// If there's no time to deliver it before or after, try to insert it in not full client
			if(j >= nbNewClient[(d->cl[i])-1])
			{
				int k = 0; // Search if the transporter going to be full or not
				while(k < nbNewClient[d->cl[i]-1] && (int) bpc[(d->n*(d->cl[i]-1))+k].size() > d->c) // FIXME Cast unsigned
					++k;

				if(k >= nbNewClient[d->cl[i]-1]) // If batch take all place, create new client
				{
					bpc[(d->n*(d->cl[i]-1))+k] = vector<double>();
					bpc[(d->n*(d->cl[i]-1))+k].push_back(d->d[i]);
					++nbNewClient[d->cl[i]-1];
				}
				else // else insert it
					bpc[(d->n*(d->cl[i]-1))+k].push_back(d->d[i]);
			}
			else // If there's time, create new client
			{
				bpc[(d->n*(d->cl[i]-1))+j] = vector<double>();
				bpc[(d->n*(d->cl[i]-1))+j].push_back(d->d[i]);
				++nbNewClient[d->cl[i]-1];
			}
		}
		else
		{
			bpc[(d->n*(d->cl[i]-1))] = vector<double>();
			bpc[(d->n*(d->cl[i]-1))].push_back(d->d[i]);
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
