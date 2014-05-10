/*
 * Arbre.cpp
 *
 *  Created on: 9 mai 2014
 *      Author: alexandre
 */

#include "Arbre.h"

Arbre::Arbre(data* d)
{
	this->c = d->c;
	this->m = d->m;
	this->n = d->n;
	this->t = 0;

	// Create clients
	int i;
	this->lClient = (Client*) malloc(sizeof(Client)*d->n);
	for(i=1;i<=d->n;i++)
		this->lClient[i] = Client(i,d);

	for(i=0; i < this->n ;i++)
	{
		if(this->lClient[i].getSCost() == 0)
		{
			this->delClient(this->lClient[i].getId());
			i--;
		}
	}
}

Arbre::~Arbre()
{
	int i;
	for(i=0;i<this->n;i++)
		this->lClient[i].~Client();
	free(this->lClient);
}

void Arbre::start()
{
	int cpt = 0, i, minCost, idClient, valSol = 0, time = 0;
	int tabTime[80] = {0};
	Client c;

	while(this->n > 0)
	{
		cout << "t = " << this->t << endl;

		this->getMinCost(&idClient,&minCost);
		cout << "The min cost is " << minCost << " and the corresponding client is " << idClient << endl;

		c = this->getClient(idClient);

		// Increment the date
		this->addTime(c.getTimeTransport()*2);
		tabTime[cpt] = c.getTimeTransport();

		// Increment the value of the solution
		valSol += minCost + (tabTime[cpt]*2);

		// Get the min date of the last client
		if(this->n == 1)
			time = c.getMinDate();

		this->delClient(idClient);

		cpt++;
	}

	for(i=1; i < cpt;i++)
		time -= tabTime[i]*2;

	time -= tabTime[0];

	cout << "T0 = " << time << endl;
	cout << "Solution : " << valSol << endl;
}

void Arbre::addTime(int t)
{
	int i;
	for(i=0;i<this->n;i++)
		this->lClient[i].addTime(t);
	this->t += t;
}

void Arbre::getMinCost(int *id, int *min)
{
	int i;

	*min = this->lClient[0].getFullCost();
	*id= this->lClient[0].getId();

	for(i=1;i<this->n;i++)
	{
		if(this->lClient[i].getFullCost() < m)
		{
			*min = this->lClient[i].getFullCost();
			*id = this->lClient[i].getId();
		}
	}
}

void Arbre::delClient(int id)
{
	int i=0,cpt=0;

	while(i < this->n && this->lClient[i].getId() != id)
		i++;
	if(i >= this->n)
		return;

	if(this->n > 1)
	{
		Client *tmp = (Client*) malloc(sizeof(Client)*(this->n-1));

		for(i=0;i< this->n;i++)
		{
			if(this->lClient[i].getId() != id)
			{
				tmp[cpt] = this->lClient[i];
				cpt++;
			}
		}

		this->lClient = tmp;
		this->n--;
	}
	else
		this->n = 0;
}

Client& Arbre::getClient(int id)
{
	int i=0;
	while(i< this->n && this->lClient[i].getId() != id)
		i++;
	if(i >= this->n)
		throw exception();
	return this->lClient[i];
}
