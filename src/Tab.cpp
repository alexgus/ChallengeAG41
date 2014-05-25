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
	this->nbClients = 0;
	this->mat = 0;
	this->t = 0;
	this->way = 0;
}

Tab::Tab(Tab& t)
{
	int i;

	this->d = t.d;
	this->eval = t.eval;
	this->nbClients = t.nbClients;
	this->t = t.t;
	this->lClient = vector<Client*>(t.lClient);

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients
	this->mat = new double*[this->nbClients];
	for(i=0;i<this->nbClients;i++)
		this->mat[i] = new double[this->nbClients];

	// Fill it
	memcpy(this->mat,t.mat,sizeof(double)*this->nbClients*this->nbClients);
	memcpy(this->way,t.way,sizeof(int)*(this->d->n/this->d->c)*this->d->m);
}

Tab::Tab(data* d)
{
	this->d = d;
	this->eval = 0;
	this->t = 0;

	// Initialize tabs function of batch and clients
	int nbBpC[d->m+1] = {0}; // Nb batch / Client
	int i,j,n;

	this->nbClients = 0;

	// Compute the nb of batch per client
	for(i=0;i<d->n;i++)
		nbBpC[d->cl[i]]++;

	// Create
	for(i=0;i<d->n;i++)
	{
		if(nbBpC[i] >= 1)
		{
			n = (nbBpC[i]/d->c)+1; // n = number of client to create
			for(j=0;j<n;j++)
			{
				// i = client number i (i in [1..m])
				// j = new created client (i is composed of many j)
				// data to extract batch
				this->lClient.push_back(new Client(i,j,d));
				this->nbClients++;
			}
		}
	}

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients
	this->mat = new double*[this->nbClients];
	for(i=0;i<this->nbClients;i++)
		this->mat[i] = new double[this->nbClients];

	// Fill tabs
	for(i=0;i < this->nbClients;i++)
		this->way[i] = -1;

	for(i=0;i < this->nbClients;i++)
	{
		for(j=0;j<this->nbClients;j++)
			this->mat[i][j] = this->lClient[i]->getFullCost();
	}

	// Debug
    for(j=0;j<this->nbClients;j++)
    {
    	for(i=0; i<this->nbClients; i++)
    		cout << setw(5) << this->mat[j][i];
    	cout << endl;
    }
}

Tab::~Tab()
{

}

Tab& Tab::operator =(Tab& t)
{
}

double Tab::getMinLine(int i, int j)
{
}

double Tab::getMinCol(int j, int i)
{
}

void Tab::subtract(double n)
{
}

void Tab::operator -(double n)
{
}

int Tab::maxPenality()
{
}

void Tab::deleteWay()
{
}

void Tab::computeCost()
{
}

void Tab::addTime(int t)
{
}

void Tab::remTime(int t)
{
}

void Tab::operator >>(int time)
{
}

void Tab::operator <<(int t)
{
}

bool Tab::checkHamiltonian()
{
}
