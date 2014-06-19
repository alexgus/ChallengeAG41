#include <cstdlib>
#include <cstring>


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

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
 * Best solution of the problem
 */
Solution *bestSol;

/**
 * List of date
 */
vector<double> *date = new vector<double>();

/**
 * Print a matrix
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

bool searchAllDate(vector<double> *v, Client *c)
{
	unsigned int cpt = 0;
	vector<double>::iterator it = v->begin();

	for(vector<double>::iterator date = c->getDate()->begin(); date != c->getDate()->end() ; ++date)
	{
		while(it != v->end() && *it != *date)
			++it;

		if(it != v->end())
			cpt++;
	}

	if(cpt == c->getDate()->size())
		return true;
	return false;
}

void eraseDate(vector<double> *v, double date)
{
	vector<double>::iterator it = v->begin();
	while(it != v->end() && *it != date)
		++it;

	if(it == v->end())
		return;
	v->erase(it);
}

vector<double>* copyVector(vector<double> *v)
{
	vector<double> *n = new vector<double>();

	for(vector<double>::iterator it = v->begin(); it != v->end();++it)
		n->push_back(*it);
	return n;
}

/**
 * Display Data
 */
void displayData()
{
	int i;
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

void handle_arg(int argc, char *argv[])
{
	int i;
	for(i=0;i< argc ; i++)
	{
		if(strcmp("-v",argv[i]) == 0)
			verbose = true;
	}
}

/**
 * Test a solution of the problem
 */
void testSol(vector<Client*> *list)
{
	Solution *test = new Solution();
	vector<double> *dateUnused = copyVector(date);
	unsigned int k = 0;

	while(k < list->size() && bestSol->getEval() > test->getEval())
	{
		if(searchAllDate(dateUnused,list->at(k)))
		{
			if(list->at(0)->getId() == 1 && list->at(0)->getDate()->size() == 1
					&& list->at(1)->getId() == 2 && list->at(1)->getDate()->size() == 3
					&& list->at(2)->getId() == 1 && list->at(2)->getDate()->size()==3
					&& list->at(3)->getId()== 3 && list->at(3)->getDate()->size() == 3)
				cout << "Coucou" << endl;

			cout << list->at(k)->getId() << ") ";
			vector<double> *dateClient = list->at(k)->getDate();
			for(vector<double>::iterator it = dateClient->begin(); it != dateClient->end();++it)
			{
				cout << *it << " ";
				eraseDate(dateUnused,*it);
			}
			test->testWay(list->at(k));
		}
		++k;
	}
	cout << endl;
	if(bestSol->getEval() > test->getEval() && test->getEval() != 0 && dateUnused->size() == 0)
	{
		*bestSol = *test;
		test = new Solution();
		if(verbose)
		{
			cout << "******************************************" << endl;
			bestSol->printSolution();
		}
	}
	else
	{
		delete test;
		test = new Solution();
	}

	delete test;
}

/**
 * Test all permutation of the list
 */
void testList(vector<Client*> *list)
{
	// Test first solution
	testSol(list);

	// Permut solution
	while(next_permutation(list->begin(), list->begin()+(list->size())))
		testSol(list);
}

int main(int argc, char *argv[])
{
// Declaration
	int i;
	ImportData *imp;
	CostTab *t;

	clock_t tBegin,tInit,tFirstSol,tPrepAlgo,tAlgoComplete,tAlgoSeparate,tAlgoMixed,tEnd;

// Initialize

	tBegin = clock();

	handle_arg(argc, argv);
	// Data
	imp = new ImportData();
	d = imp->getData();

	for(int j = 0; j < d->n ;++j)
		date->push_back(d->d[j]);

	if(verbose)
		displayData();

	// Initialize first solution
	t = new CostTab(d);

	if(verbose)
	{
		cout << endl << "================== Begin :";
		cout << endl << "--> Base Matrix <--" << endl;
		t->printCost();
	}

	tInit = clock();

// Begin

	// Get first solution
	t->calculatePerfectTime();
	bestSol = t->getSol();
	if(verbose)
		bestSol->printSolution();

	// Get second solution
	//bestSol->separateBatch();
	if(verbose)
	{
		cout << "================== Separate :" << endl << endl;
		bestSol->printSolution();
	}

	tFirstSol = clock();

	// ************** Branch and cut *****************

	// ***** Separate batch *****
	// (batch are grouped if there's no time to deliver them next)
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

	// Get the number of client to create
	int nbClient = 0;
	for(int k = 0; k < d->m ;++k)
		nbClient+=nbNewClient[k];

	// Declare three lists of clients
	vector<Client*> *lCompleteClient = new vector<Client*>();
	vector<Client*> *lSeparateClient = new vector<Client*>();
	vector<Client*> *lMixedClient = new vector<Client*>();

	// **** Fill tabs ****
	// Tab of complete client and mixed client
	for(i = 1 ; i <= d->m; ++i)
	{
		Client *c = new Client(i,d);
		lCompleteClient->push_back(c);
		lMixedClient->push_back(c);
	}
	// tab of separate client and mixed client
	for(i = 0 ; i < d->m; ++i)
	{
		for(int k = 0 ; k < nbNewClient[i] ; ++k)
		{
			Client *c = new Client(i+1,d,&bpc[(d->n * i)+k]);
			lSeparateClient->push_back(c);
			lMixedClient->push_back(c);
		}
	}

	// Free memory
	delete nbNewClient;

	tPrepAlgo = clock();

	// **** Begin branch and cut ****

	// Test all possibilities on complete list
	testList(lCompleteClient);
	tAlgoComplete = clock();

	// Test all possibilities on the other
	testList(lSeparateClient);
	tAlgoSeparate = clock();

	// Mixed solution
	testList(lMixedClient);
	tAlgoMixed = clock();

	// ***** Print the best solution found *****

	tEnd = clock();

	cout << endl <<endl << "***********************************" << endl
			<< "********* Best solution ***********" << endl
			<< "***********************************" << endl;
	bestSol->printSolution();

	cout << endl << endl << "Time init : " << ((float)(tInit-tBegin)/CLOCKS_PER_SEC) << endl
			<< "Time First Solution : " << ((float)(tFirstSol-tInit)/CLOCKS_PER_SEC) <<endl
			<< "Time prepare algo : " << ((float)(tPrepAlgo- tFirstSol)/CLOCKS_PER_SEC) <<endl
			<< "Time Algo with complete list : " <<((float)(tAlgoComplete-tBegin)/CLOCKS_PER_SEC) << endl
			<< "Time Algo with complete list : " << ((float)(tAlgoSeparate-tAlgoComplete)/CLOCKS_PER_SEC)<<endl
			<< "Time Algo with complete list : " << ((float)(tAlgoMixed-tAlgoSeparate)/CLOCKS_PER_SEC)<<endl << endl
			<< "Total time : " << ((float)(tEnd-tBegin)/CLOCKS_PER_SEC)<< endl;

// Finalize free memory
	delete lSeparateClient;
	delete lCompleteClient;
	delete lMixedClient;
	delete imp;
	delete t;
	//delete bpc;
	return EXIT_SUCCESS;
}
