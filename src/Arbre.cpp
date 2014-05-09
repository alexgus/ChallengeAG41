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
	int min, id, val;
	Client c;

	while(this->n > 0)
	{
		cout << "t = " << this->t << endl;

		this->getMinCost(&id,&min);
		cout << "The min cost is " << min << " and the corresponding client " << id << endl;

		c = this->getClient(id);
		val = c.getFullCost();
		this->addTime(val);

		this->delClient(id);
	}
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

Client& Arbre::getClient(int id)
{
	int i=0;
	while(i< this->n && this->lClient[i].getId() != id)
		i++;
	if(i >= this->n)
		throw exception();
	return this->lClient[i];
}
