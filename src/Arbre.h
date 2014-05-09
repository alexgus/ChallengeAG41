/*
 * Arbre.h
 *
 *  Created on: 9 mai 2014
 *      Author: alexandre
 */

#ifndef ARBRE_H_
#define ARBRE_H_

#include <iostream>

#include "Client.h"

using namespace std;

/**
 * Define the algorithm
 */
class Arbre
{
public:

	Arbre(data *d);

	virtual ~Arbre();

	void start();

private:
	int c;
	int m;
	int n;

	Client *lClient;

	int t;

	void addTime(int t);

	void getMinCost(int* id, int* min);

	void delClient(int id);

	Client& getClient(int id);
};

#endif /* ARBRE_H_ */
