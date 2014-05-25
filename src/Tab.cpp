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

	this->computeCost();
}

Tab::~Tab()
{
	int i;

	for(i=0;i < this->nbClients;i++)
	{
		delete this->mat[i];
		delete this->lClient[i];
	}
	delete this->mat;
}

Tab& Tab::operator =(Tab& t)
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

	return *this;
}

double Tab::getMinLine(int i, int j = -1)
{
	int min;
	int itJ;

	for(itJ=0;itJ<this->nbClients;itJ++)
	{
		if(itJ != j && min > this->mat[i][itJ])
			min = this->mat[i][itJ];
	}

	return min;
}

double Tab::getMinCol(int j, int i = -1)
{
	int min;
	int itI;

	for(itI=0;itI<this->nbClients;itI++)
	{
		if(itI != i && min > this->mat[itI][j])
			min = this->mat[itI][j];
	}

	return min;
}

void Tab::subtract(double n)
{
	int i,j;

	for(i=0;i < this->nbClients;i++)
	{
		for(j=0;j<this->nbClients;j++)
		{
			if(i != j)
				this->mat[i][j] -= n;
		}
	}
}

void Tab::operator -(double n)
{
	this->subtract(n);
}

int Tab::maxPenality(int *iMax, int *jMax)
{
	int i,j;
	int max;

	for(i=0;i<this->nbClients;i++)
	{
		for(j=0;j<this->nbClients;j++)
		{
			if(this->mat[i][j] == 0)
			{
				*iMax = i;
				*jMax = j;
				max = (this->getCol0(j) - 1) + (this->getLine0(i) - 1);
			}
		}
	}

	return max;
}

void Tab::deleteWay()
{
}

void Tab::computeCost()
{
	int i,j;

	for(i=0;i < this->nbClients;i++)
	{
		for(j=0;j<this->nbClients;j++)
		{
			if(i != j || this->mat[i][j] != -1)
				this->mat[i][j] = this->lClient[i]->getFullCost();
			else
				this->mat[i][j] = -1;
		}
	}
}

void Tab::addTime(int t)
{
	int i;

	for(i=0; i< this->nbClients;i++)
		this->lClient[i]->addTime(t);
	this->computeCost();
}

void Tab::remTime(int t)
{
	int i;

	for(i=0; i< this->nbClients;i++)
		this->lClient[i]->remTime(t);
	this->computeCost();
}

void Tab::operator >>(int time)
{
	this->remTime(time);
}

void Tab::operator <<(int t)
{
	this->addTime(t);
}

bool Tab::checkHamiltonian()
{
	return false;
}

void Tab::printMatrix()
{
	int i,j;

	for(j=0;j<this->nbClients;j++)
	{
		for(i=0; i<this->nbClients; i++)
			cout << setw(5) << this->mat[j][i];
		cout << endl;
	}
}

int Tab::getLine0(int i)
{
	int j,nb = 0;
	for(j=0;j < this->nbClients; j++)
		if(this->mat[i][j] == 0)
			nb++;
	return nb;
}

int Tab::getCol0(int j)
{
	int i,nb = 0;
	for(i=0;i < this->nbClients; i++)
		if(this->mat[i][j] == 0)
			nb++;
	return nb;
}
