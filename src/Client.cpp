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

Client::Client(int id, data* d)
{
	this->id = id;
	this->id2 = 0;
	this->time = 0;
	this->beta = d->beta[id-1];
	this->eta = d->eta;
	this->timeTransport = d->tau[id-1];
	this->tCost = 0;
	this->sCost = 0;

	this->date = new vector<double>();

	int cpt = 0;
	for(int i=0; i < d->n;i++)
	{
		if(d->cl[i] == id && cpt < d->c)
		{
			this->date->push_back(d->d[i]);
			cpt++;
		}
	}

	this->calcSCost();
	this->calcTCost();
}

Client::Client(int id, data* d, int n)
{
	this->id = id;
	this->id2 = 0;
	this->time = 0;
	this->beta = d->beta[id-1];
	this->eta = d->eta;
	this->timeTransport = d->tau[id-1];
	this->tCost = 0;
	this->sCost = 0;

	this->date = new vector<double>();

	int i = 0;
	int cpt = 0;
	while(i < d->n && cpt < n)
	{
		if(d->cl[i] == id)
			cpt++;
		i++;
	}
	cpt=0;
	for(; i < d->n  && cpt < d->c;i++)
	{
		if(d->cl[i] == id)
		{
			this->date->push_back(d->d[i]);
			++cpt;
		}
	}

	this->calcSCost();
	this->calcTCost();
}

Client::Client(int id, int n, data* d)
{
	this->id = id;
	this->id2 = n;
	this->time = 0;
	this->beta = d->beta[id-1];
	this->eta = d->eta;
	this->timeTransport = d->tau[id-1];
	this->tCost = 0;
	this->sCost = 0;

	// Fill Batch date and nbBatch corresponding to the right client
	int i,cpt=0, nb = 0;

	int* tmpB = new int[d->n];
	double* tmpD = new double[d->n];

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

	this->date = new vector<double>();

	// Copy to the new tables
	for(i=0;i<nb;i++)
		this->date->push_back(tmpD[(this->id2 -1)+i]);

	// init cost
	this->calcSCost();
	this->calcTCost();

	delete tmpB;
	delete tmpD;
}

Client::Client(int id,  data* d, vector<double> *dateIn)
{
	this->id = id;
	this->id2 = 0;
	this->time = 0;
	this->beta = d->beta[id-1];
	this->eta = d->eta;
	this->timeTransport = d->tau[id-1];
	this->tCost = 0;
	this->sCost = 0;

	this->date = new vector<double>();

	for(vector<double>::iterator it = dateIn->begin(); it != dateIn->end();++it)
		this->date->push_back(*it);

    this->calcSCost();
    this->calcTCost();
}

Client::Client(Client& c)
{
	this->id = c.id;
	this->id2 = c.id2;
	this->eta = c.eta;
	this->beta = c.beta;
	this->timeTransport = c.timeTransport;
	this->date = new vector<double>();
	for(vector<double>::iterator d = c.date->begin(); d != c.date->end(); ++d)
		this->date->push_back(*d);
	this->time = c.time;
	this->sCost = c.sCost;
	this->tCost = c.tCost;
}


Client::~Client()
{
	if(this->date->size() > 0)
	{
		delete this->date;
		this->date = 0;
	}
}

void Client::addTime(double toAdd)
{
	this->time += toAdd;
	this->calcSCost();
}

void Client::remTime(double t)
{
	this->time -= t;
	this->calcSCost();
}

void Client::calcTCost()
{
	this->tCost = this->timeTransport * this->eta * 2;
}

void Client::supprAllDate(void)
{
	while(!this->date->empty())
		this->date->pop_back();
}

void Client::addDate(double date)
{
	this->date->push_back(date);
	this->calcSCost();
}

void Client::calcSCost()
{
	this->sCost = 0;
	for(vector<double>::iterator it= this->date->begin(); it != this->date->end(); ++it)
		this->sCost += this->beta * (*it - this->time);
}

double Client::getMinDate()
{
	if(this->date->size() <= 0)
		return -1;

	vector<double>::iterator min = this->date->begin();

	for(vector<double>::iterator it = this->date->begin(); it != this->date->end();++it)
	{
		if(*min > *it)
			min = it;
	}

	return *min;
}

void Client::supprDate(double date)
{
	vector<double>::iterator it = this->date->begin();
	while(it != this->date->end() && (*it) != date)
		++it;

	if(*it == date)
		this->date->erase(it);

	this->calcSCost();
}

void Client::operator =(Client& c)
{
	this->id = c.id;
	this->id2 = c.id2;
	this->eta = c.eta;
	this->beta = c.beta;
	this->timeTransport = c.timeTransport;
	this->date = new vector<double>();
	for(vector<double>::iterator d = c.date->begin(); d != c.date->end(); ++d)
		this->date->push_back(*d);
	this->time = c.time;
	this->sCost = c.sCost;
	this->tCost = c.tCost;
}
