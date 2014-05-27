/*
 * Tab.cpp
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#include "Tab.h"

Tab::Tab()
{
	this->d = 0;
	this->eval = 0;
	this->t = 0;
	this->way = 0;
	this->lClient = 0;
	this->sol =0;
}

Tab::Tab(Tab& t)
{

	this->d = t.d;
	this->eval = t.eval;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));
	this->sol = t.sol;

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients

	// Fill it
	memcpy(this->way,t.way,sizeof(int)*(this->d->n/this->d->c)*this->d->m);
}

Tab::Tab(data* d)
{
	this->d = d;
	this->eval = 0;
	this->t = 0;

	// Initialize tabs function of batch and clients
	int* nbBpC =(int*) malloc(sizeof (int)*(d->m+1));// Nb batch / Client
	memset(nbBpC,0,sizeof(int)*(d->m+1));
	int i,j, cpt = 0;
	double n;

	// Compute the nb of batch per client
	for(i=0;i<d->n;i++)
		nbBpC[d->cl[i]]++;

	// Create
	this->lClient = new vector<Client*>();
	for(i=1;i<=d->n;i++)
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
				cpt++;
			}
		}
	}

	this->sol = new Solution(this->lClient);

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients

	// Fill tabs
	for(i=0;i < cpt;i++)
		this->way[i] = -1;
}

Tab::~Tab()
{
	unsigned int i;

	for(i=0;i < this->lClient->size();i++)
		delete this->lClient->at(i);
}

Tab& Tab::operator =(Tab& t)
{


	this->d = t.d;
	this->eval = t.eval;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients

	// Fill it
	memcpy(this->way,t.way,sizeof(int)*(this->d->n/this->d->c)*this->d->m);

	return *this;
}

int Tab::getMinIndexLine()
{
	int min = this->lClient->at(0)->getFullCost();
	int minIndex = 0;
	unsigned int itJ;

	for(itJ=1;itJ<this->lClient->size();itJ++)
	{
		if(min > this->lClient->at(itJ)->getFullCost())
		{
			min = this->lClient->at(itJ)->getFullCost();
			minIndex = itJ;
		}
	}

	return minIndex;
}

Client* Tab::getMinClientLine()
{
	double min = this->lClient->at(0)->getFullCost();
	Client* cMin = this->lClient->at(0);
	unsigned int itJ;

	for(itJ=1;itJ<this->lClient->size();itJ++)
	{
		if(min > this->lClient->at(itJ)->getFullCost())
		{
			min = this->lClient->at(itJ)->getFullCost();
			cMin = this->lClient->at(itJ);
		}
	}

	return cMin;
}

double Tab::getMinValLine()
{
	double min = this->lClient->at(0)->getFullCost();
	unsigned int itJ;

	for(itJ=1;itJ<this->lClient->size();itJ++)
	{
		if(min > this->lClient->at(itJ)->getFullCost())
			min = this->lClient->at(itJ)->getFullCost();
	}
	return min;
}

int Tab::getNumberOfDelivery(){
	return lClient->size();
}

void Tab::addTime(int t)
{
	unsigned int i;

	for(i=0; i< this->lClient->size();i++)
		this->lClient->at(i)->addTime(t);
	this->t += t;
}

void Tab::remTime(int t)
{
	unsigned int i;

	for(i=0; i< this->lClient->size();i++)
		this->lClient->at(i)->remTime(t);
	this->t -= t;
}

void Tab::operator >>(int time)
{
	this->remTime(time);
}

void Tab::operator <<(int t)
{
	this->addTime(t);
}

void Tab::printCost()
{
	unsigned int j;

	for(j=0;j<this->lClient->size();j++)
	{
		cout << setw(5) << this->lClient->at(j)->getFullCost();
		cout << endl;
	}
}

void Tab::deleteClientOrder(int numClient)
{
	this->sol->addWay(this->getMinClientLine());
	lClient->erase(lClient->begin()+numClient);
}
