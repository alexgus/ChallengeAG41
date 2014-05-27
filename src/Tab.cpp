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
	this->lClient = 0;
	this->sol =0;
}

Tab::Tab(Tab& t)
{

	this->d = t.d;
	this->eval = t.eval;
	this->nbClients = t.nbClients;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));
	this->sol = t.sol;

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients
	this->mat = new double[this->nbClients];

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
	int* nbBpC =(int*) malloc(sizeof (int)*(d->m+1));// Nb batch / Client
	memset(nbBpC,0,sizeof(int)*(d->m+1));
	int i,j;
	double n;

	this->nbClients = 0;

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
				this->nbClients++;
			}
		}
	}

	this->sol = new Solution(this->lClient);

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients
	this->mat = new double[this->nbClients];

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
		delete this->lClient->at(i);
	}
	delete this->mat;
}

Tab& Tab::operator =(Tab& t)
{


	this->d = t.d;
	this->eval = t.eval;
	this->nbClients = t.nbClients;
	this->t = t.t;
	this->lClient = new vector<Client*>(*(t.lClient));

	// Allocate memory
	this->way = new int[(this->d->n/this->d->c)*this->d->m]; // (Number of batch / capacity of the transporter) * number of clients
	this->mat = new double[this->nbClients];


	// Fill it
	memcpy(this->mat,t.mat,sizeof(double)*this->nbClients*this->nbClients);
	memcpy(this->way,t.way,sizeof(int)*(this->d->n/this->d->c)*this->d->m);

	return *this;
}

int Tab::getMinIndexLine()
{
	int min;
	int itJ;

	for(itJ=0;itJ<this->nbClients;itJ++)
	{
		if(itJ != -1 && min > this->mat[itJ])
			min = itJ;
	}

	return min;
}

Client* Tab::getMinClientLine()
{
	double min;
	Client* cMin;
	int itJ;

			for(itJ=0;itJ<this->nbClients;itJ++)
			{
				if(itJ != -1 && min > this->mat[itJ])
				{
					min = this->mat[itJ];
					cMin = this->lClient->at(itJ);
				}
			}
			return cMin;

}

double Tab::getMinValLine()
{
	double min;
		int itJ;

		for(itJ=0;itJ<this->nbClients;itJ++)
		{
			if(itJ != -1 && min > this->mat[itJ])
				min = mat[itJ];
		}
		return min;
}

int Tab::getNumberOfDelivery(){
	return lClient->size();
}

void Tab::subtract(double n)
{
	int i;

	for(i=0;i < this->nbClients;i++)
	{

				this->mat[i] -= n;
	}
}


void Tab::operator -(double n)
{
	this->subtract(n);
}


void Tab::computeCost()
{
	int i;

	for(i=0;i < this->nbClients;i++)
	{

			if(this->mat[i] != -1)
				this->mat[i] = this->lClient->at(i)->getFullCost();

	}
}

void Tab::addTime(int t)
{
	int i;

	for(i=0; i< this->nbClients;i++)
		this->lClient->at(i)->addTime(t);
	this->computeCost();
}

void Tab::remTime(int t)
{
	int i;

	for(i=0; i< this->nbClients;i++)
		this->lClient->at(i)->remTime(t);
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

void Tab::printMatrix()
{
	int j;

	for(j=0;j<this->nbClients;j++)
	{
			cout << setw(5) << this->mat[j];
		cout << endl;
	}
}
int comprar(const void* elem1, const void *elem2)
{
	double* ele1 = (double*) elem1;
	double* ele2 = (double*) elem2;

	if(*ele1<*ele2){
		return -1;
	}
	else {
		if(*ele1 ==*ele2){
			return 0;
		}
		else{
			return 1;
		}
	}


}

void Tab::sort()
{
	qsort(this->mat,nbClients,sizeof(double),comprar);
}

int Tab::getLine0()
{
	int j,nb = 0;
	for(j=0;j < this->nbClients; j++)
		if(this->mat[j] == 0)
			nb++;
	return nb;
}

void Tab::deleteClientOrder(int numClient)
{
	lClient->erase(lClient->begin()+numClient);
	this->mat[numClient]= -1;

}
