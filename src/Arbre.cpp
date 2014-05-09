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
	for(i=0;i<d->n;i++)
		this->lClient[i] = Client(i,d);

	// TODO Check for unused clients
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
}

void Arbre::addTime(int t)
{
	int i;
	for(i=0;i<this->n;i++)
		this->lClient[i].addTime(t);
}

int Arbre::getMinCost()
{
	int i,min;

	min = this->lClient[0].getFullCost();
	for(i=1;i<this->n;i++)
	{
		if(this->lClient[i].getFullCost() < m)
			min = this->lClient[i].getFullCost();
	}
	return min;
}
