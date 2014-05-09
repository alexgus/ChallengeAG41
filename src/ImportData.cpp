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
	catch(ios_base::failure &f)
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
	string tmpS;

	string n = string("n");
	string m = string("m");
	string c = string("c");
	string eta = string("eta");
	string beta = string("beta");
	string tau = string("tau");
	string cli = string("cli");
	string di = string("di");

	while(!this->cfile.eof())
	{
		getline(this->cfile,tmpS);

		this->setValue(&tmpS, &n, &this->d->n);
		this->setValue(&tmpS, &m, &this->d->m);
		this->setValue(&tmpS, &c, &this->d->c);
		this->setValue(&tmpS, &eta, &this->d->eta);
		this->setValue(&tmpS, &beta, &this->d->beta);
		this->setTable(&tmpS, &tau, this->d->tau);
		this->setTable(&tmpS, &cli, this->d->cl);
		this->setTable(&tmpS, &di, this->d->d);
	}
}

void ImportData::setValue(string *s, string *toFind, int *val)
{
	size_t i, pos;

	pos = s->find(*toFind);
	if(pos != 0 || (*s)[toFind->length()] != '=') // If not find or not corresponding
		return;

	for(i = toFind->length() + 1; i < s->length(); i++)
		*val = ((*val)*10) + ((*s)[i] - '0');
}

void ImportData::setTable(string* s, string* toFind, int* val)
{
	size_t i = 0, pos, cpt = 0;

	pos = s->find(*toFind);
	if(pos != 0 || (*s)[toFind->length()] != '=') // If not find or not corresponding
		return;

	i = toFind->length();
	while(i < s->length() && (cpt < MAX_TAU || cpt < MAX_N))
	{
		for(i = i + 1; (*s)[i] != ' ' && i < s->length(); i++)
			val[cpt] = ((val[cpt])*10) + ((*s)[i] - '0');
		cpt++;
	}
}
