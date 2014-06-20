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
	 * @param d Data to initialize
	 */
	Client(int id, data *d);

	/**
	 * Initialize the client with the id and data
	 * @param id Id of Client
	 * @param n The client nb n with the same id
	 * @param d Data to initialize
	 */
	Client(int id, int n, data *d);

	/**
	 * Initialize the client with the id and data
	 * @param id Id of Client
	 * @param n The client nb n with the same id
	 * @param d Data to initialize
	 */
	Client(int id, data *d, int n);

	/**
	 * Initialize the client with the id and data
	 * @param id Id of Client
	 * @param n The client nb n with the same id
	 * @param d Data to initialize
	 */
	Client(int id, data *d, vector<double> *date);

	/**
	 * Copy constructor
	 */
	Client(Client& c);

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
	 * Suppress date in lit of batch
	 */
	void supprDate(double date);

	/**
	 * Suppressed all batch for this client
	 */
	void supprAllDate(void);

	/**
	 * Add date in list of batch
	 * @param date Date to add
	 */
	void addDate(double date);

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

	vector<double>* getDate() const
	{
		return date;
	}

	unsigned int getNbBatch() const
	{
		return this->date->size();
	}

	/**
	 * Define the behavior of = operator.
	 * Copy a Client
	 */
	void operator=(Client& c);

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
