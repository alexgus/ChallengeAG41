/*
 * Client.cpp
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#include "Client.h"

Client::Client()
{
	this->id=0;
	this->id2 =0;
	this->t = 0;
	this->beta = 0;
	this->eta = 0;
	this->timeTransport = 0;
	this->tCost = 0;
	this->sCost = 0;
	this->nbBatch = 0;
	this->batch = NULL;
	this->date = NULL;
}

Client::Client(int id, int n, data* d)
{
	this->id = id;
	this->id2 = n;
	this->t = 0;
	this->beta = d->beta;
	this->eta = d->eta;
	this->timeTransport = d->tau[id];
	this->tCost = 0;
	this->sCost = 0;

	// Fill Batch date and nbBatch corresponding to the right client
	int i,cpt=0;

	int* tmpB = (int*) malloc(sizeof(int)*d->n);
	int* tmpD = (int*) malloc(sizeof(int)*d->n);
	for(i=0; i < d->n ;i++)
	{
		if(d->cl[i] == id)
		{
			tmpB[cpt] = i;
			tmpD[cpt] = d->d[i];
			cpt++;
		}
	}

	// Sort tabs
	int j,k,swapD,swapB;
	i=0;
	while(i<cpt-1)
	{
		// Found bigger
		if(tmpD[i] > tmpD[i+1])
		{
			j=0;
			// Save data
			swapD = tmpD[i+1];
			swapB = tmpB[i+1];

			// Search where insert it
			j=0;
			while(j<cpt-1 && tmpD[j] < swapD)
				j++;

			// Move
			k=i;
			while(k>=j)
			{
				tmpB[k+1] = tmpB[k];
				tmpD[k+1] = tmpD[k];
				k--;
			}

			// Assert
			tmpB[j] = swapB;
			tmpD[j] = swapD;
		}
		i++;
	}

	// Allocate tables to their good size
	this->nbBatch = cpt - (this->id2 * d->c);
	if(this->nbBatch != 0)
	{
		this->batch = (int*) malloc(sizeof(int)*this->nbBatch);
		this->date = (int*) malloc(sizeof(int)*this->nbBatch);

		// Copy to the new tables
		for(i=0;i<this->nbBatch;i++)
		{
			this->batch[i] = tmpB[(this->id2 * d->c)+i];
			this->date[i] = tmpD[(this->id2 * d->c)+i];
		}
	}
	else
		throw "nbBatch = 0 !";

	// init cost
	this->calcSCost();
	this->calcTCost();

	free(tmpB);
	free(tmpD);
}

Client::~Client()
{
	if(this->nbBatch != 0)
	{
		free(this->batch);
		this->batch = NULL;
		free(this->date);
		this->date = NULL;
	}
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

double Client::getSCost()
{
	return this->sCost;
}

double Client::getFullCost()
{
	return (this->tCost + this->sCost);
}

void Client::calcTCost()
{
	this->tCost = this->timeTransport * this->eta * 2;
}

void Client::calcSCost()
{
	int i;

	this->sCost = 0;
	for(i=0; i < this->nbBatch; i++)
		this->sCost += this->beta * (this->date[i] - this->t) * this->id;
}

int Client::getId()
{
	return this->id;
}

void Client::delBatch(int id)
{
	int i,cpt = 0;
	bool find = false;

	for(i=0;i< this->nbBatch;i++)
	{
		if(this->batch[i] == id)
			find = true;
	}

	if(!find)
		return;

	int* tmpB = (int*) malloc(sizeof(int)*(this->nbBatch-1));
	int* tmpD = (int*) malloc(sizeof(int)*(this->nbBatch-1));

	for(i=0;i< this->nbBatch;i++)
	{
		if(this->batch[i] != id)
		{
			tmpB[i] = this->batch[i];
			tmpD[i] = this->date[i];
			cpt++;
		}
	}

	this->nbBatch--;
	this->batch = tmpB;
	this->date = tmpD;
	this->calcSCost();
}

int Client::getTimeTransport()
{
	return this->timeTransport;
}

int Client::getMinDate()
{
	if(this->nbBatch == 0)
		return -1;

	int i, min = this->date[0];
	for(i=0; i < this->nbBatch;i++)
	{
		if(min > this->date[i])
			min = this->date[i];
	}
	return min;
}
