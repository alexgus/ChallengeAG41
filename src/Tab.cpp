/*
 * Tab.cpp
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#include "Tab.h"

Tab::Tab()
{
	this->eval = 0;
	this->t = 0;
	this->lClient = 0;
	this->sol =0;
}

Tab::Tab(Tab& t)
{
	this->eval = t.eval;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));
	this->sol = t.sol;
}

Tab::Tab(data* d)
{
	this->eval = 0;
	this->t = 0;

	// Initialize tabs function of batch and clients
	int* nbBpC = new int[d->m+1];// Nb batch / Client
	memset(nbBpC,0,sizeof(int)*d->m+1);
	int i,j;
	double n;

	// Compute the nb of batch per client
	for(i=0;i<d->n;i++)
		nbBpC[d->cl[i]]++;

	// Create
	this->lClient = new vector<Client*>();
	for(i=1;i<=d->m;i++)
	{
		if(nbBpC[i] >= 1)
		{
			n = (nbBpC[i]/(double)d->c) + 1; // n = number of client to create
			for(j=1;j<n;j++)
			{
				// i = client number i (i in [1..m])
				// j = new created client (i is composed of many j)
				// data to extract batch
				this->lClient->push_back(new Client(i,j,d));
			}
		}
	}

	this->sol = new Solution(this->lClient);

	delete nbBpC;
}

Tab::~Tab()
{
	unsigned int i;

	for(i=0;i < this->lClient->size();i++)
		delete this->lClient->at(i);

	delete this->sol;
}

Tab& Tab::operator =(Tab& t)
{
	this->eval = t.eval;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));

	return *this;
}

int Tab::getMinIndexLine()
{
	int minIndex = 0;
	vector<Client*>::iterator min = this->lClient->begin();

	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
	{
		if((*min)->getFullCost() > (*it)->getFullCost())
		{
			min = it;
			minIndex = it - this->lClient->begin(); // Get the index from the begin (pointer size soustraction)
		}
	}

	return minIndex;
}

Client* Tab::getMinClientLine()
{
	vector<Client*>::iterator min = this->lClient->begin();

	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
	{
		if((*min)->getFullCost() > (*it)->getFullCost())
			min = it;
	}

	return *min;
}

double Tab::getMinValLine()
{
	vector<Client*>::iterator min = this->lClient->begin();

	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
	{
		if((*min)->getFullCost() > (*it)->getFullCost())
			min = it;
	}

	return (*min)->getFullCost();
}

void Tab::addTime(int t)
{
	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
		(*it)->addTime(t);
	this->t += t;
}

void Tab::remTime(int t)
{
	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
			(*it)->remTime(t);
	this->t -= t;
}

void Tab::deleteClientOrder(int numClient)
{
	this->sol->addWay(this->getMinClientLine());
	lClient->erase(lClient->begin()+numClient);
}

void Tab::printCost()
{
	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
	{
		cout << setw(5) << (*it)->getFullCost();
		cout << endl;
	}
}
