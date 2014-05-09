/**
 * ImportData.h
 *
 *  Created on: 8 mai 2014
 *      Author: alexandre
 */

#ifndef IMPORTDATA_H_
#define IMPORTDATA_H_

#include <string>
#include <fstream>

#include <iostream>

#define MAX_TAU 15
#define MAX_N	30

using namespace std;

// FIXME add double value for beta (using ratio claas too)
typedef struct inputData
{
	int n;				// Number batch to deliver
	int m;				// Number of clients (client 0 is the provider)
	int c;				// Capacity of the conveyer
	int eta;			// Constant of the deliver cost
	int beta;			// Storage's cost function h
	int tau[MAX_TAU];	// Travel time between 0 and a client
	int cl[MAX_N];		// Merchandise i to deliver to cl[i]
	int d[MAX_N];		// Date to deliver merchandise i
} data;

/**
 * Class for importing data from a file
 */
class ImportData
{
public:
	const string FILE = "./data.conf";

	/**
	 * Import data from the configuration file
	 */
	ImportData();

	/**
	 * Destroyer of the class
	 */
	virtual ~ImportData();

	/**
	 * Get the data extracted from the file
	 */
	data* getData();

private:
	/**
	 * The data extracted
	 */
	data *d;

	/**
	 * Configuration file stream
	 */
	ifstream cfile;

	/**
	 * Parse the file and extract informations
	 */
	void startParsing();

	/**
	 * Search the string toFind in s and if there is an
	 * occurrence of toFind in s it extract the value after the equal
	 * character of s in val
	 */
	void setValue(string *s, string *toFind, int* val);

	/**
	 * Search the string toFind in s and if there is an
	 * occurrence of toFind in s it extract the value after the equal
	 * character of s in val table
	 */
	void setTable(string *s, string *toFind, int* val);
};

#endif /* IMPORTDATA_H_ */
