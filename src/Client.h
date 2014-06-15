/*
 * Client.h
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <vector>

#include "data.h"

using namespace std;

/**
 * Define a Client with the products he wants
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
	 * Add time to the current time
	 */
	void addTime(const double toAdd);

	/**
	 * Remove time to avoid problems when calculating cost
	 */
	void remTime(double t);

	/**
	 * Return the minimum date for delivering a batch
	 */
	double getMinDate();

	/**
	 * Get id of client
	 */
	int getId() const
	{
		return id;
	}

	/**
	 * Get id2 of client
	 */
	int getId2() const
	{
		return id2;
	}

	/**
	 * Get the time multiplier
	 */
	double getEta() const
	{
		return eta;
	}

	/**
	 * Return the transport Cost
	 */
	double getTCost() const
	{
		return tCost;
	}

	/**
	 * Return the storage cost
	 */
	double getSCost() const
	{
		return sCost;
	}

	/**
	 * Return the storage cost + transport cost
	 */
	double getFullCost() const
	{
		return (tCost + sCost);
	}

	/**
	 * Get the time to go to the client
	 */
	double getTimeTransport() const
	{
		return timeTransport;
	}

	/**
	 * Set time current time of client
	 */
	void setTime(double t)
	{
		this->time = t;
		this->calcSCost();
	}

	double getTime() const
	{
		return time;
	}

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
	double eta;

	/**
	 * Time to go from the deliverer to this clients
	 */
	double timeTransport;

	/**
	 * transport cost
	 */
	double tCost;

	/**
	 * Storage cost
	 */
	double sCost;

	/**
	 * Vector to stock batch and id of the batch
	 */
	vector<double> *date;

	/**
	 * Actual time
	 */
	double time;

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
