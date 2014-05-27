#include <cstdlib>
#include <cstring>


#include <iostream>
#include <iomanip>

#include "ImportData.h"
#include "Tab.h"

#include <vector>
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
	Solution *solution;
// Initialize
	handle_arg(argc, argv);
	solution = new Solution();
	// Data
	imp = new ImportData();
	d = imp->getData();

	if(verbose)
	{
		cout << "Initialized constants :" 		 << endl
			 << "n    : " << d->n				 << endl
			 << "m    : " << d->m				 << endl
			 << "c    : " << d->c				 << endl
			 << "eta  : " << d->eta				 << endl
			 << "beta : " << d->beta			 << endl
			 << "tau  : Distance entre le fournisseur et les clients" << endl;
		for(i=1; i<=d->m; i++)
			cout << setw(SETW) << i;
		cout << endl;
		printTable(d->tau, d->m);

		cout << endl << endl << endl
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
	t = new Tab(d);
	cout << endl << "Base Matrix" << endl;

	if(verbose)
		t->printMatrix();

	cout <<"getNumberOfDelivery "<<t->getNumberOfDelivery()<<endl;
// Begin
for(int i =0; i<t->getNumberOfDelivery();i++){
	int min;
	Client* c;
	int tCost;
cout<<i<<endl;
	c = t->getMinClientLine();
	tCost = c->getTCost();
	t->addTime(tCost);
	solution->addWay(c);
	t->deleteClientOrder(t->getMinIndexLine());
	cout<<i<<endl;
}
	// Optimize t function of batch's date delivery
	// Evaluate the solution and keep the way with t

cout<<"Affichage §§§§§§§"<<endl;

vector<Client*> *lClient;

lClient= solution->getClient();

for(unsigned int i =0;i<lClient->size();i++){
		cout<<lClient->at(i)->getId()<<" "<<lClient->at(i)->getId2()<<endl;
	}
// Finalize
	delete imp;
	delete t;
	return EXIT_SUCCESS;
}
