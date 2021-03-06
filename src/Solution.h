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
	void addWay(Client * c);

	/**
	 * Test Way
	 */
	void testWay(Client * c);

	/**
	 * Create new clients with his own batch which can be delivered later
	 */
	void separateBatch();

	/**
	 * Compute the value of the solution
	 * @return the current evaluation of the solution
	 */
	double evaluate();

	/**
	 * Set time in client
	 * @param t The time to set
	 */
	void setTime(int t);

	/**
	 * Get the current evaluation
	 * @return The evaluation
	 */
	double getEval() const
	{
		return eval;
	}

	 vector<Client*>* getClient() const
	{
		return lClient;
	}

	double getTime() const
	{
		return bTime;
	}

	void operator=(Solution &s);

void printSolution();

	/**
	 * Evaluation of the way
	 */
	double eval;

private:

	/**
	 * Begin time associates to the solution
	 */
	double bTime;

	/**
	 * List of clients
	 */
	vector<Client*> *lClient;

	/**
	 * Define a busy window
	 */
	typedef struct
	{
		double begin;
		double end;
	} window;
};

#endif /* SOLUTION_H_ */
