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
	//Insert client to right place
	vector<Client*>::iterator it = this->lClient->begin();

	if(this->lClient->size() == 0)
		this->lClient->push_back(c);
	else
	{
		while(it != this->lClient->end()&& (*it)->getSCost()>= c->getSCost())
			++it;

		if(it!= this->lClient->end())
			this->lClient->insert(it,c);
		else
			this->lClient->push_back(c);
	}

	//Calculate real time for clients
	it = this->lClient->begin()+1;
	double timeTemp= lClient->at(0)->getMinDate();
	double timeTrans = lClient->at(0)->getTimeTransport();
	while(it != this->lClient->end()){
		(*it)->setTime(timeTemp-timeTrans-(*it)->getTimeTransport());
		timeTemp =(*it)->getTime();
		timeTrans=(*it)->getTimeTransport();
		this->bTime = timeTemp-timeTrans;
		++it;
	}

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

void Solution::printSolution()
{
	for(vector<Client*>::iterator it = this->lClient->begin(); it != this->lClient->end();++it)
	{
		cout << "Client " <<(*it)->getId() << " " << (*it)->getId2() << endl
				<< "t=" <<(*it)->getTime() << endl
				<< "Tcost=" <<(*it)->getTCost() <<endl
				<< "Scost="<<(*it)->getSCost() <<endl
				<< "Fcost="<<(*it)->getFullCost() <<endl;
		cout << endl;
	}
}

void Solution::separateBatch()
{
	vector<Client*> *toAdd = new vector<Client*>();
	window *w = new window[this->lClient->size()];
	unsigned int i = 0;

	// Create windows
	for(vector<Client*>::iterator it = this->lClient->begin(); it != this->lClient->end();++it)
	{
		w[i].begin = (*it)->getTime()-(*it)->getTimeTransport();
		w[i].end = (*it)->getTime()+(*it)->getTimeTransport();
		++i;
	}

	// Check for all clients
	for(vector<Client*>::iterator it = this->lClient->begin(); it != this->lClient->end();++it)
	{
		// Check for all batch
		vector<double> *b = (*it)->getDate();
		double tDeliver = (*it)->getTimeTransport();
		for(vector<double>::iterator date = b->begin(); date != b->end();++date)
		{
			if((w[0].end + tDeliver) <= *date)
			{
				cout << *date << endl;
				// TODO Evaluate for separate or not
				Client *c = (*it);
				(*it)->supprDate(*date);
				c->supprAllDate();
				c->addDate(*date);
				toAdd->push_back(c);
			}
			else
			{
				i=1;
				while(i < this->lClient->size() && w[i].end <= ((*it)->getTime() + (*it)->getTimeTransport()))
				{
					if(w[i].end <= (*date - tDeliver) && w[i-1].begin >= (*date + tDeliver))
					{
						cout << *date << endl;
						// TODO Evaluate for separate or not. Create new client and insert it in toAdd
						break;
					}
					i++;
				}
			}
		}
	}

	// TODO Insert toAdd in list of Client
}
