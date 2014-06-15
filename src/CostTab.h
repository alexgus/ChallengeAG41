/*
 * Tab.h
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#ifndef TAB_H_
#define TAB_H_

#include <vector>

#include <iostream>
#include <iomanip>

#include <cstring>

#include "data.h"
#include "Client.h"
#include "Solution.h"

using namespace std;

/**
 * Create tab for applying little algorithm on it.
 */
class CostTab
{
public:
	/**
	 * Initialize the class
	 * Default constructor
	 */
	CostTab();

	/**
	 * Copy constructor. Copy a state of the algorithm
	 */
	CostTab(CostTab& t);

	/**
	 * Initialize the class with data extracted
	 */
	CostTab(data *d);

	/**
	 * Destroyer of the class.
	 * Deallocate memory
	 */
	virtual ~CostTab();

	/**
	 * Override = operator for affectation
	 */
	CostTab& operator=(CostTab& t);

	/*
	 * @return the client which has the minimum cost
	 */
	Client* getMinClient();

	/**
	 * @return the minimum cost
	 */
	double getMinVal();

	/*
	 * @return the client which has the maximum cost
	 */
	Client* getMaxClient();

	/**
	 * @return the maximum cost
	 */
	double getMaxVal();

	/**
	 * Get the client with minimum date to deliver
	 */
	Client* getMinClientDate();

	/*
	 * delete the Client from lClient and set -1 to its cost in mat
	 * @param cRem Client to delete and add to the solution
	 */
	void deleteClient(Client* cRem);

	/**
	 * Get the time of the current matrix
	 * @return The time of the current matrix
	 */
	double getTime() const
	{
		return t;
	}

	/**
	 * Get the current evaluation
	 * @return Evaluation at time t
	 */
	double getEval() const
	{
		return eval;
	}

	/**
	 * Return the current solution of the tab
	 * @return The solution
	 */
	Solution* getSol() const
	{
		return sol;
	}

	unsigned int getNumberOfDelivery() const
	{
		return this->lClient->size();
	}

	/**
	 * Print the matrix cost
	 */
	void printCost();

	/*
	 * Calculate cost at perfect time
	 */
	void calculatePerfectTime();

private:

	/**
	 * The actual cost
	 */
	double eval;

	/**
	 * Time for computing right cost
	 */
	double t;

	/**
	 * List of client
	 */
	vector<Client*> *lClient;

	/**
	 * Solution of the current tab
	 */
	Solution *sol;

};

#endif /* TAB_H_ */
