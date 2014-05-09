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

