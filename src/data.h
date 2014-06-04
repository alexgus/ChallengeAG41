/*
 * data.h
 *
 *  Created on: 9 mai 2014
 *      Author: alexandre
 */

#ifndef DATA_H_
#define DATA_H_

#define SETW 8

#define MAX_TAU 150
#define MAX_N	300

typedef struct inputData
{
	int    n;			 // Number batch to deliver
	int    m;			 // Number of clients (client 0 is the provider)
	int    c;			 // Capacity of the conveyer
	int    eta;			 // Constant of the deliver cost
	double beta[MAX_TAU];// Storage's cost function h
	int    tau[MAX_TAU]; // Travel time between 0 and a client
	int    cl[MAX_N];	 // Merchandise i to deliver to cl[i]
	int    d[MAX_N];	 // Date to deliver merchandise i
} data;

#endif /* DATA_H_ */
