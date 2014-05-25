/*
 * Client.h
 *
 *  Created on: 15 mai 2014
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
	 * @param id Id of Client
	 * @param n The client nb n with the same id
	 * @param d Data to initialize
	 */
	Client(int id, int n, data *d);

	/**
	 * Destroyer of the class
	 */
	virtual ~Client();

	/**
	 * Get id of the client
	 */
	int getId();

	/**
	 * The time passed
	 */
	void addTime(const int toAdd);

	/**
	 * Remove time for avoid problems when calculating cost
	 */
	void remTime(int t);

	/**
	 * Return the transport Cost
	 */
	int getTCost();

	/**
	 * Return the storage cost
	 */
	double getSCost();

	/**
	 * Return the storage cost + transport cost
	 */
	double getFullCost();

	/**
	 * Get the time to go to the client
	 */
	int getTimeTransport();

	/**
	 * Return the minimum date for delivering a batch
	 */
	int getMinDate();

	/**
	 * Add time to batch delivery date
	 * @param Time to add
	 */
	void addTimeToDate(int t);

	/**
	 * Remove time to batch delivery date
	 * @param Time to remove
	 */
	void remTimeToDate(int t);

	/**
	 * Delete batch
	 */
	void delBatch(int id);

private:

	/**
	 * Id of the client
	 */
	int id;

	/**
	 * Id2 of the client. This number correspond to the n client with id
	 */
	int id2;

	/**
	 * Storage multiplier
	 */
	double beta;

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
	double sCost;

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
