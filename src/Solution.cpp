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
	this->lClient = 0;
	this->nbW = 0;
}

Solution::Solution(vector<Client*>* lClient)
{
	this->eval = 0;
	this->lClient = lClient;
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

void Solution::addWay(int i)
{
	this->way[this->nbW] = i;
	this->nbW++;
	this->evaluate();
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
