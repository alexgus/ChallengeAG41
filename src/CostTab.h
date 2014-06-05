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

	/**
	 * Get the index of the minimum
	 * @return the index of the column where the min is located
	 */
	int getMinIndexLine();

	/*
	 * @return the client which has the minimum cost
	 */
	Client* getMinClientLine();

	/*
	 * @return the minimum cost
	 */
	double getMinValLine();

	/*
	 * delete the Client from lClient and set -1 to its cost in mat
	 * @param numClient id of the client
	 */
	void deleteClientOrder(int numClient);

	/**
	 * Add time t to the current time for computing right cost.
	 * @param t Time to add
	 */
	void addTime(double t);

	/**
	 * Remove time t to the current time for computing right cost
	 * @param t Time to remove
	 */
	void remTime(double t);

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
