/*
 * Arbre.h
 *
 *  Created on: 9 mai 2014
 *      Author: alexandre
 */

#ifndef ARBRE_H_
#define ARBRE_H_

#include "Client.h"

/**
 * Define the algorithm
 */
class Arbre
{
public:

	Arbre(data *d);

	virtual ~Arbre();

private:
	int c;
	int m;
	int n;
	Client *lClient;

};

#endif /* ARBRE_H_ */
