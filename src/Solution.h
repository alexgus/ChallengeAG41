/*
 * Solution.h
 *
 *  Created on: 25 mai 2014
 *      Author: alexandre
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <iostream>

#include "data.h"
#include "Client.h"

using namespace std;

/**
 * Define a solution of the problem and evaluate it
 */
class Solution
{
public:

	/**
	 * Default constructors of the class.
	 */
	Solution();

	/**
	 * Initialize class
	 */
	Solution(vector<Client*> *lClient);

	/**
	 * Destroyer of the class.
	 * Deallocate memory allocated by the class
	 */
	virtual ~Solution();

	/**
	 * Add way in the tab
	 * @param The number of client in the list
	 */
	void addWay(int i);

	/**
	 * Delete the way nb i in solution tab.
	 * @param The i-eme way to delete
	 */
	void deleteWay(int i);

	/**
	 * Delete the last way from the solution tab
	 */
	void deleteLastWay();

	/**
	 * Check if the ways choose make an Hamiltonian path
	 * @return true if hamiltonian false otherwise
	 */
	bool checkHamiltonian();

	/**
	 * Compute the value of the solution
	 * @return the current evaluation of the solution
	 */
	double evaluate();

	/**
	 * Get the current evaluation
	 * @return The evaluation
	 */
	double getEval() const
	{
		return eval;
	}

	/**
	 * Get the current nb of client in the solution's tab
	 * @return The nb of current client in the solution's tab
	 */
	int getNbW() const
	{
		return nbW;
	}

	/**
	 * Get the solution's tab
	 * @return The solution's tab
	 */
	int* getWay() const
	{
		return way;
	}

private:

	/**
	 * Evaluation of the way
	 */
	double eval;

	/**
	 * The way tab to follow
	 */
	int *way;

	/**
	 * the current nb of way in the tab
	 */
	int nbW;

	/**
	 * List of clients
	 */
	vector<Client*> *lClient;
};

#endif /* SOLUTION_H_ */
