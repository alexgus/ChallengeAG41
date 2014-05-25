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
	 * Check if the ways choose make an Hamiltonian path
	 */
	bool checkHamiltonian();

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
	 * List of clients
	 */
	vector<Client*> *lClient;
};

#endif /* SOLUTION_H_ */
