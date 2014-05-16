/*
 * Client.h
 *
 *  Created on: 15 mai 2014
 *      Author: alexandre
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "data.h"

/**
 * Define class container for batch
 */
class Client
{
public:
	Client();
	Client(int i, int j, data* d);
	virtual ~Client();
};

#endif /* CLIENT_H_ */
