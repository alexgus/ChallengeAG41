#include <cstdlib>
#include <cstring>


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

#include "ImportData.h"
#include "CostTab.h"

#define COEF_TAU 1

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
			vector<double> *dateClient = list->at(k)->getDate();
			for(vector<double>::iterator it = dateClient->begin(); it != dateClient->end();++it)
				eraseDate(dateUnused,*it);
			test->testWay(list->at(k));
		}
		++k;
	}
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

/**
 * find a client in a list
 */
bool findClient(vector<Client*>* list, Client *c)
{
	// test on id and size
	for(vector<Client*>::iterator lc = list->begin();lc != list->end();++lc)
	{
		if((*lc)->getId() == c->getId())
		{
			unsigned int cpt = 0;
			for(vector<double>::iterator dateList = (*lc)->getDate()->begin() ; dateList != (*lc)->getDate()->end() ; ++dateList)
			{
				for(vector<double>::iterator date = c->getDate()->begin() ; date != c->getDate()->end() ; ++date)
				{
					if(*date == *dateList)
						cpt++;
				}
			}
			if(cpt == (*lc)->getDate()->size())
				return true;
		}
	}
	return false;
}

int main(int argc, char *argv[])
{
// Declaration
	int i;
	ImportData *imp;
	CostTab *t;

	clock_t tBegin,tInit,tFirstSol,tPrepAlgo,tAlgoMixed,tEnd;

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

			double tl = d->tau[d->cl[i]-1]*COEF_TAU;
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

	// Declare lists of clients
	vector<Client*> *lMixedClient = new vector<Client*>();

	// **** Fill tabs ****
	// Tab of complete client and mixed client
	for(i = 1 ; i <= d->m; ++i)
	{
		Client *c = new Client(i,d);
		if(c->getDate()->size() != 0)
			lMixedClient->push_back(c);
	}
	// tab of separate client and mixed client
	for(i = 0 ; i < d->m; ++i)
	{
		for(int k = 0 ; k < nbNewClient[i] ; ++k)
		{
			Client *reste = new Client(*lMixedClient->at(i));
			Client *c = new Client(i+1,d,&bpc[(d->n * i)+k]);

			for(vector<double>::iterator itDateSuppr = bpc[(d->n * i)+k].begin() ; itDateSuppr != bpc[(d->n * i)+k].end() ; ++itDateSuppr)
				reste->supprDate(*itDateSuppr);

			if((!findClient(lMixedClient,c) || !findClient(lMixedClient,reste)))
			{
				if(c->getDate()->size() != 0)
					lMixedClient->push_back(c);
				if(reste->getDate()->size() != 0)
					lMixedClient->push_back(reste);
			}
		}
	}

	if(verbose)
	{
		// Display list size
		cout << "**********************************************************" <<endl;
		cout << "Size Mixed client : " << lMixedClient->size()<<endl;
		cout << "**********************************************************" <<endl;
	}

	// Free memory
	delete nbNewClient;

	tPrepAlgo = clock();

	// **** Begin branch and cut ****


	for(vector<Client*>::iterator cIt = lMixedClient->begin(); cIt != lMixedClient->end(); ++cIt)
	{
		cout << (*cIt)->getId() << " ";
		for(vector<double>::iterator dateC = (*cIt)->getDate()->begin() ; dateC != (*cIt)->getDate()->end(); ++dateC)
			cout << *dateC << " ";
		cout << endl;
	}

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
			<< "Time Algo : " << ((float)(tAlgoMixed-tPrepAlgo)/CLOCKS_PER_SEC)<<endl << endl
			<< "Total time : " << ((float)(tEnd-tBegin)/CLOCKS_PER_SEC)<< endl;

// Finalize free memory
	delete lMixedClient;
	delete imp;
	delete t;
	//delete bpc;
	return EXIT_SUCCESS;
}
