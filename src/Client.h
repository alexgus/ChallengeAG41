/*
 * Client.h
 *
 *  Created on: 9 mai 2014
 *      Author: alexandre
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <cstdlib>

#include "data.h"

/**
 * Define a Client with his products wanted
 */
class Client
{
public:

	/**
	 * Default constructor
	 */
	Client();

	/**
	 * Initialize the client with the id and data
	 */
	Client(int id, data *d);

	/**
	 * Destroyer of the class
	 */
	virtual ~Client();

	/**
	 * The time passed
	 */
	void addTime(const int toAdd);

	/**
	 * Return the transport Cost
	 */
	int getTCost();

	/**
	 * Return the storage cost
	 */
	int getSCost();

	/**
	 * Return the storage cost + transport cost
	 */
	int getFullCost();

	/**
	 * Delete some batch
	 */
	void delBatch(int *id);

private:

	/**
	 * Id of the client
	 */
	int id;

	/**
	 * Storage multiplier
	 */
	int beta;

	/**
	 * Transport multiplier
	 */
	int eta;

	/**
	 * Time to go from the deliverer to this clients
	 */
	int timeTransport;

	/**
	 * transport cost
	 */
	int tCost;

	/**
	 * Storage cost
	 */
	int sCost;

	/**
	 * Number of batch asked by the client
	 */
	int nbBatch;

	/**
	 * Id of batch asked
	 */
	int *batch;

	/**
	 * Date to have the batch
	 */
	int *date;

	/**
	 * Actual time
	 */
	int t;

	/**
	 * Calculate transport cost
	 */
	void calcTCost();

	/**
	 * Calculate storage cost
	 */
	void calcSCost();
};

#endif /* CLIENT_H_ */
