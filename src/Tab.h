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

#include "data.h"
#include "Client.h"

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
	 * Get the minimum of the line
	 * @param i The line to check
	 * @param j The current column to exclude from the min. -1 if no exclude
	 * @return the min of the line
	 */
	double getMinLine(int i, int j);

	/**
	 * Get the minimum of the column
	 * @param i The current columns to exclude from the min. -1 if no exclude
	 * @param j The column to check
	 * @return the min of the column
	 */
	double getMinCol(int j, int i);

	/**
	 * Subtract n to the entire matrix
	 * @param n Number to subtract
	 */
	void subtract(double n);

	/**
	 * Subtract n to the entire matrix
	 * Alias of the subtract method
	 * @param n Number to subtract
	 */
	void operator-(double n);

	/**
	 * Compute the max penalty
	 * @return the max penalty
	 */
	int maxPenality();

	/**
	 * Delete way (entry of the tab)
	 */
	void deleteWay();

	/**
	 * Compute cost in the matrix
	 */
	void computeCost();

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
	 * Check if the ways choose make an Hamiltonian path
	 */
	bool checkHamiltonian();

	/**
	 * Get the matrix at time t
	 * @return The matrix at time t
	 */
	double** getMat() const
	{
		return mat;
	}

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
	void printMatrix();

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
	 * Size of the matrix
	 */
	int nbClients;

	/**
	 * The data matrix with cost
	 */
	double **mat;

	/**
	 * The way choose at time t.
	 */
	int *way;

	/**
	 * List of clients
	 */
	vector<Client*> lClient;

	/**
	 * A copy of the data
	 */
	data * d;

};

#endif /* TAB_H_ */
