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
	this->bTime = 0;
	this->lClient = new vector<Client*>();
}

Solution::Solution(vector<Client*>* lClient)
{
	this->eval = 0;
	this->bTime = 0;
	this->lClient = new vector<Client*>;
}

Solution::~Solution()
{
	delete this->lClient;
}

void Solution::addWay(Client* c)
{
	vector<Client*>::iterator it = this->lClient->begin();
	while(it != this->lClient->end()&& (*it)->getSCost()>= c->getSCost())
		++it;

	if(it!= this->lClient->end())
		this->lClient->insert(it,c);
	else if (this->lClient->size()== 0)
		this->lClient->push_back(c);
}

double Solution::evaluate()
{
	unsigned int i = this->lClient->size();
	Client *c = this->lClient->at(i-1);
	int t;
	int tCost = 0, sCost = 0;

// Find the right t
	// Initialize
	c = this->lClient->at(this->lClient->size()-1);
	this->bTime = c->getMinDate();
	this->bTime -= (c->getTCost()/2)/c->getEta();

	// Iterate over the vector decreasingly
	for(i=i-1; i > 0; i--)
	{
		c = this->lClient->at(i);
		this->bTime -= (c->getTCost()/2)/c->getEta();

		if(c->getMinDate() < this->bTime)
			this->bTime = c->getMinDate();

		this->bTime -= (c->getTCost()/2)/c->getEta();
	}
	t = this->bTime;
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

void Solution::setTime(int t)
{
	unsigned int i;

	for(i=0;i<this->lClient->size();i++)
		this->lClient->at(i)->setTime(t);
}
