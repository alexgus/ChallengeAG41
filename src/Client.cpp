/*
 * Client.cpp
 *
 *  Created on: 9 mai 2014
 *      Author: alexandre
 */

#include "Client.h"

Client::Client()
{
}

Client::Client(int id, data* d)
{
	this->id = id;
	this->t = 0;
	this->beta = d->beta;
	this->eta = d->eta;
	this->timeTransport = d->tau[id];

	// Fill Batch date and nbBatch
	int i,cpt=0;

	int* tmpB = (int*) malloc(sizeof(int)*d->n);
	int* tmpD = (int*) malloc(sizeof(int)*d->n);
	for(i=0; i < d->n ;i++)
	{
		if(d->cl[i] == id)
		{
			tmpB[cpt] = d->cl[i];
			tmpD[cpt] = d->d[i];
			cpt++;
		}
	}

	// Allocate tables to their good size
	this->nbBatch = cpt;
	this->batch = (int*) malloc(sizeof(int)*cpt);
	this->date = (int*) malloc(sizeof(int)*cpt);

	// Copy to the new tables
	for(i=0;i<cpt;i++)
	{
		this->batch[i] = tmpB[i];
		this->date[i] = tmpD[i];
	}

	this->calcSCost();
	this->calcTCost();

	free(tmpB);
	free(tmpD);
}

Client::~Client()
{
	free(this->batch);
	free(this->date);
}

void Client::addTime(int toAdd)
{
	this->t += toAdd;
	this->calcSCost();
}

int Client::getTCost()
{
	return this->tCost;
}

int Client::getSCost()
{
	return this->sCost;
}

int Client::getFullCost()
{
	return (this->tCost + this->sCost);
}

void Client::calcTCost()
{
	this->tCost = this->timeTransport * this->eta;
}

void Client::calcSCost()
{
	int i;

	for(i=0; i < this->nbBatch; i++)
		this->sCost += this->beta * (this->date[i] - this->t);
}
