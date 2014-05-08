/*
 * ImportData.cpp
 *
 *  Created on: 8 mai 2014
 *      Author: alexandre
 */

#include "ImportData.h"

ImportData::ImportData()
{
	// Allocate memory for data
	this->d = (data*) malloc(sizeof(data));

	// Open and parse the configuration file
	try
	{
		this->cfile.open(this->FILE.c_str(),fstream::in);
	}
	catch(ios_base::failure f)
	{
		cout << "Error opening " << this->FILE << " :" << f.what() << endl;
	}

	// Check the file
	if(!this->cfile.good())
		cout << "The file " << this->FILE << " is not opened, void or there is fs error" << endl;
	else
		this->startParsing();
}

ImportData::~ImportData()
{
	// Free the memory
	free(this->d);
	// Close file
	this->cfile.close();
}

data* ImportData::getData()
{
	return this->d;
}

void ImportData::startParsing()
{
	string tmp;

	while(!this->cfile.eof())
	{
		getline(this->cfile,tmp);
		cout << tmp << endl;
	}

}
