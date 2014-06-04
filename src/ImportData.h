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

#include "data.h"

using namespace std;

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
	 * character of s in val
	 */
	void setValue(string *s, string *toFind, double* val);

	/**
	 * Search the string toFind in s and if there is an
	 * occurrence of toFind in s it extract the value after the equal
	 * character of s in val table
	 */
	void setTable(string *s, string *toFind, int* val);

	/**
	 * Search the string toFind in s and if there is an
	 * occurrence of toFind in s it extract the value after the equal
	 * character of s in val table
	 */
	void setTable(string* s, string* toFind, double* val);

	/**
	 * Search the string toFind in s and if there is an
	 * occurrence of toFind in s it extract the value after the equal
	 * character of s in val table at index i
	 */
	void setValueTable(string* s, string* toFind, int* val, int index);

	/**
	 * Search the string toFind in s and if there is an
	 * occurrence of toFind in s it extract the value after the equal
	 * character of s in val table at index i
	 */
	void setValueTable(string* s, string* toFind, double* val, int index);
};

#endif /* IMPORTDATA_H_ */
