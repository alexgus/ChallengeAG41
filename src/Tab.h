/*
 * Tab.h
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#ifndef TAB_H_
#define TAB_H_

#include <cstring>
#include <vector>

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "data.h"
#include "Client.h"
#include "Solution.h"

using namespace std;

/**
 * Create tab for applying little+ algorithm on it.
 */
class Tab
{
public:
	/**
	 * Initialize the class
	 * Default constructor
	 */
	Tab();

	/**
	 * Copy constructor. Copy a state of the algorithm
	 */
	Tab(Tab& t);

	/**
	 * Initialize the class with data extracted
	 */
	Tab(data *d);

	/**
	 * Destroyer of the class.
	 * Deallocate memory
	 */
	virtual ~Tab();

	/**
	 * Override = operator for affectation
	 */
	Tab& operator=(Tab& t);

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
	void addTime(int t);

	/**
	 * Remove time t to the current time for computing right cost
	 * @param t Time to remove
	 */
	void remTime(int t);
	/**
	 * Alias of the remTime method
	 */
	void operator>>(int time);

	/**
	 * Alias of the addTime method
	 */
	void operator<<(int t);

	/**
	 * Get the time of the current matrix
	 * @return The time of the current matrix
	 */
	int getTime() const
	{
		return t;
	}

	/**
	 * Get the way choose at time t
	 * @return Table of way. Length is given by getMat() method.
	 */
	const int* getWay() const
	{
		return way;
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
	 * Print the matrix cost
	 */
	void printCost();

	/**
	 * Return the current solution of the tab
	 * @return The solution
	 */
	const Solution* getSol() const
	{
		return sol;
	}
int getNumberOfDelivery();
private:

	/**
	 * The actual cost
	 */
	double eval;

	/**
	 * Time for computing right cost
	 */
	int t;

	/**
	 * The way choose at time t.
	 */
	int *way;

	/**
	 * List of client
	 */
	vector<Client*> *lClient;

	/**
	 * Solution of the current tab
	 */
	Solution *sol;

	/**
	 * A copy of the data
	 */
	data * d;

};

#endif /* TAB_H_ */
