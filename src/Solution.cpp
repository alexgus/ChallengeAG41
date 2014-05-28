/*
 * Solution.cpp
 *
 *  Created on: 25 mai 2014
 *      Author: alexandre
 */

#include "Solution.h"

Solution::Solution()
{
	this->eval = 0;
	this->way = 0;
	this->lClient = new vector<Client*>();
	this->nbW = 0;
}

Solution::Solution(vector<Client*>* lClient)
{
	this->eval = 0;
	this->lClient = new vector<Client*>;
	this->way = new int[this->lClient->size()];
	this->nbW = 0;

	unsigned int i;
	for(i=0;i<this->lClient->size();i++)
		this->way[i] = -1;
}

Solution::~Solution()
{
	if(this->way != 0)
		delete this->way;
}

void Solution::addWay(Client* c)
{
	this->lClient->push_back(c);
	/*
	this->way[this->nbW] = i;
	this->nbW++;
	this->evaluate();
	*/
}

bool Solution::checkHamiltonian()
{
	unsigned int i,j;
	for(i=0;i<this->lClient->size();i++)
	{
		if(this->way[i] != -1)
		{
			j=0;
			while(j<this->lClient->size() && this->way[i] != this->way[j])
				j++;
			if(this->way[j] == this->way[i])
				return false;
		}
	}
	return true;
}

double Solution::evaluate()
{
	unsigned int i = this->lClient->size();
	int t;
	Client *c = this->lClient->at(i-1);
	int tCost = 0, sCost = 0;

// Find the right t
	// Initialize
	c = this->lClient->at(this->lClient->size()-1);
	t = c->getMinDate();
	this->setTime((c->getTCost()/2)/c->getEta());
	t -= (c->getTCost()/2)/c->getEta();

	// Iterate over the vector decreasingly
	for(i=i-1; i > 0; i--)
	{
		c = this->lClient->at(i);
		t -= (c->getTCost()/2)/c->getEta();

		if(c->getMinDate() < t)
			t = c->getMinDate();

		t -= (c->getTCost()/2)/c->getEta();
	}
	// t is now corresponding to serve all clients correctly and it's placed in the first client

	// Iterate for compute the evaluation
	for(i = 0; i < this->lClient->size(); i++)
	{
		c = this->lClient->at(i);
		t += (c->getTCost()/2)/c->getEta();
		c->setTime(t);
		tCost += c->getTCost();
		sCost += c->getSCost();
		t += ((c->getTCost()/2)/c->getEta());
	}

	this->eval = tCost + sCost;

	return this->eval;
}

void Solution::deleteWay(int i)
{
	this->way[i] = -1;
}

void Solution::deleteLastWay()
{
	this->way[this->nbW-1] = -1;
	this->nbW--;
}

void Solution::setTime(int t)
{
	unsigned int i;

	for(i=0;i<this->lClient->size();i++)
		this->lClient->at(i)->setTime(t);
}
