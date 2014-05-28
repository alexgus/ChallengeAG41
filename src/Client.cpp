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
	this->time = 0;
	this->beta = 0;
	this->eta = 0;
	this->timeTransport = 0;
	this->tCost = 0;
	this->sCost = 0;
	this->date = 0;
}

Client::Client(int id, int n, data* d)
{
	this->id = id;
	this->id2 = n;
	this->time = 0;
	this->beta = d->beta;
	this->eta = d->eta;
	this->timeTransport = d->tau[id];
	this->tCost = 0;
	this->sCost = 0;

	// Fill Batch date and nbBatch corresponding to the right client
	int i,cpt=0, nb = 0;

	int* tmpB = new int[d->n];
	int* tmpD = new int[d->n];

	for(i=0; i < d->n ;i++)
	{
		if(d->cl[i] == id)
		{
			tmpB[cpt] = i;
			tmpD[cpt] = d->d[i];
			cpt++;
		}
	}

	if(cpt == 0)
		throw "nbBatch <= 0 !";

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

	if(cpt > d->c)
	{
		if(this->id2*d->c <= cpt)
			nb = d->c;
		else
			nb = (this->id2 * d->c) - cpt;
	}
	else
		nb = cpt;

	this->date = new vector<int>();

	// Copy to the new tables
	for(i=0;i<nb;i++)
		this->date->push_back(tmpD[(this->id2 -1)+i]);

	// init cost
	this->calcSCost();
	this->calcTCost();

	delete tmpB;
	delete tmpD;
}

Client::~Client()
{
	if(this->date->size() > 0)
	{
		delete this->date;
		this->date = 0;
	}
}

void Client::addTime(int toAdd)
{
	this->time += toAdd;
	this->calcSCost();
}

void Client::remTime(int t)
{
	this->time -= t;
	this->calcSCost();
}

void Client::calcTCost()
{
	this->tCost = this->timeTransport * this->eta * 2;
}

void Client::calcSCost()
{
	this->sCost = 0;
	for(vector<int>::iterator it= this->date->begin(); it != this->date->end(); ++it)
		this->sCost += this->beta * (*it - this->time) * this->id;
}

int Client::getMinDate()
{
	if(this->date->size() <= 0)
		return -1;

	vector<int>::iterator min = this->date->begin();

	for(vector<int>::iterator it; it != this->date->end();++it)
	{
		if(*min > *it)
			min = it;
	}

	return *min;
}
