/*
 * Tab.cpp
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#include "CostTab.h"

CostTab::CostTab()
{
	this->eval = 0;
	this->t = 0;
	this->lClient = 0;
	this->sol =0;
}

CostTab::CostTab(CostTab& t)
{
	this->eval = t.eval;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));
	this->sol = t.sol;
}

CostTab::CostTab(data* d)
{
	this->eval = 0;
	this->t = 0;

	// Initialize tabs function of batch and clients
	int* nbBpC = new int[d->m+1];// Nb batch / Client
	memset(nbBpC,0,sizeof(int)*(d->m+1));
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

CostTab::~CostTab()
{
	unsigned int i;

	for(i=0;i < this->lClient->size();i++)
		delete this->lClient->at(i);

	delete this->sol;
}

CostTab& CostTab::operator =(CostTab& t)
{
	this->eval = t.eval;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));

	return *this;
}

int CostTab::getMinIndexLine()
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

Client* CostTab::getMinClientLine()
{
	vector<Client*>::iterator min = this->lClient->begin();

	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
	{
		if((*min)->getFullCost() > (*it)->getFullCost())
			min = it;
	}

	return *min;
}

double CostTab::getMinValLine()
{
	vector<Client*>::iterator min = this->lClient->begin();

	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
	{
		if((*min)->getFullCost() > (*it)->getFullCost())
			min = it;
	}

	return (*min)->getFullCost();
}

void CostTab::addTime(double t)
{
	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
		(*it)->addTime(t);
	this->t += t;
}

void CostTab::remTime(double t)
{
	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
			(*it)->remTime(t);
	this->t -= t;
}

void CostTab::deleteClientOrder(int numClient)
{
	this->sol->addWay(this->getMinClientLine());
	lClient->erase(lClient->begin()+numClient);
}

void CostTab::printCost()
{
	if(this->lClient->size() > 0)
	{
		for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
			cout << setw(SETW - 3) << "C" << (*it)->getId() << " " << (*it)->getId2();
		cout << endl;
		for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
			cout << setw(SETW) << (*it)->getFullCost();
		cout << endl;
	}
	else
		cout << "No Clients" << endl;
}

Client* CostTab::getMinClientDate()
{
	Client* cMin = this->lClient->at(0);
	for(vector<Client*>::iterator it = this->lClient->begin();it != this->lClient->end();++it)
	{
		if(cMin->getMinDate() > (*it)->getMinDate())
			cMin = (*it);
	}
	return cMin;
}
