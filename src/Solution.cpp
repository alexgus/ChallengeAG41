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
	this->evaluate();
}


double Solution::evaluate()
{
	this->eval = 0;
	for(vector<Client*>::iterator it = this->lClient->begin(); it != this->lClient->end();++it)
		this->eval += (*it)->getFullCost();
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

	cout << endl <<
			"======= Solution :" <<endl<<
			"Begin time : " << this->bTime<<endl<<
			"Evaluation : "<< this->eval<< endl;
}

void Solution::separateBatch()
{
	window *w = new window[this->lClient->size()];
	unsigned int itWin = 0;

	// Create windows
	for(vector<Client*>::iterator it = this->lClient->begin(); it != this->lClient->end();++it)
	{
		w[itWin].begin = (*it)->getTime()-(*it)->getTimeTransport();
		w[itWin].end = (*it)->getTime()+(*it)->getTimeTransport();
		++itWin;
	}

	// Check for all clients
	for(unsigned int itClient = 0; itClient < this->lClient->size();++itClient)
	{
		// Check for all batch
		vector<double> *lDate = this->lClient->at(itClient)->getDate();
		double tDeliver = this->lClient->at(itClient)->getTimeTransport();
		for(unsigned int itDate = 0; itDate < lDate->size();++itDate)
		{
			if((w[0].end + tDeliver) <= lDate->at(itDate))
			{
				// Get the old value of cost
				int oldVal = this->lClient->at(itClient)->getFullCost();

				// Create new client
				Client c = *this->lClient->at(itClient);
				c.supprAllDate();
				c.addDate(lDate->at(itDate));
				this->lClient->insert(this->lClient->begin(),&c);
				--itClient;

				this->lClient->at(itClient+2)->supprDate(lDate->at(itDate));
				--itDate;

				int newCVal = c.getFullCost();
				int newVal = this->lClient->at(itClient)->getFullCost();

				if(oldVal > (newVal+newCVal))
					cout << endl << "WIN !" << endl;
				else
					; // TODO revert change
			}
			else
			{
				itWin=1;
				while(itWin < this->lClient->size() && w[itWin].end <= (this->lClient->at(itClient)->getTime() + this->lClient->at(itClient)->getTimeTransport()))
				{
					if(w[itWin].end <= (lDate->at(itDate) - tDeliver) && w[itWin-1].begin >= (lDate->at(itDate) + tDeliver))
					{
						cout << lDate->at(itDate) << endl;
						// TODO Evaluate for separate or not. Create new client and insert it in toAdd
						break;
					}
					itWin++;
				}
			}
		}
	}
}
