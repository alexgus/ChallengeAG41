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

	string customer = string("CUSTOMER");
	string n = string("NBR_PRODUCT");
	string c = string("TRANSPORTER_CAPACITY");
	string eta = string("TRANSPORTER_DELIVERY_COST_ETA");
	string beta = string("CUSTOMER_HOLDING_COSTS");
	string tau = string("TRANSPORTER_DELIVERY_TIME_SUPPLIER_CUSTOMER");
	string cli = string("JOB_CUSTOMER");
	string di = string("JOB_DUE_DATES");

	this->d->m = 0;

	while(!this->cfile.eof())
	{
		getline(this->cfile,tmpS);

		if(tmpS.find(n) >= 0)
		{
			this->setValue(&tmpS, &n, &this->d->n);

			getline(this->cfile,tmpS);
			this->setValue(&tmpS, &c, &this->d->c);
			getline(this->cfile,tmpS);
			this->setValue(&tmpS, &eta, &this->d->eta);

			while(!this->cfile.eof())
			{
				getline(this->cfile,tmpS);
				if(tmpS.find(customer) > 0)
				{
					getline(this->cfile,tmpS);
					this->setValueTable(&tmpS, &beta, this->d->beta, this->d->m);
					getline(this->cfile,tmpS);
					this->setValueTable(&tmpS, &tau, this->d->tau, this->d->m);
					this->d->m++;
				}

				this->setTable(&tmpS, &cli, this->d->cl);
				getline(this->cfile,tmpS);
				this->setTable(&tmpS, &di, this->d->d);
			}
		}
	}
}

void ImportData::setValue(string *s, string *toFind, int *val)
{
	size_t i, pos;

	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	for(i = toFind->length() + pos + 1;( i < s->length()); i++)
		*val = ((*val)*10) + ((*s)[i] - '0');
}

void ImportData::setValue(string* s, string* toFind, double* val)
{
	size_t i,j,pos;

	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	char* tmp = (char*) malloc(sizeof(char)*s->length());

	for(i = 0 ; i < s->length(); i++)
		tmp[i] = '\0';

	j=0;
	for(i = toFind->length() + pos +1; i < s->length(); i++)
	{
		tmp[j] = (*s)[i];
		j++;
	}

	*val = atof(tmp);
}

void ImportData::setTable(string* s, string* toFind, int* val)
{
	size_t i = 0, pos, cpt = 0;

	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	i = toFind->length() + pos;
	while(i < s->length() && (cpt < MAX_TAU || cpt < MAX_N))
	{
		for(i = i + 1; (*s)[i] != ';' && i < s->length(); i++)
			val[cpt] = ((val[cpt])*10) + ((*s)[i] - '0');
		cpt++;
	}
}

void ImportData::setValueTable(string* s, string* toFind, int* val, int index)
{
	size_t i, pos;

	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	for(i = toFind->length() + pos + 1; i < s->length(); i++)
		val[index] = ((val[index])*10) + ((*s)[i] - '0');
}

void ImportData::setValueTable(string* s, string* toFind, double* val, int index)
{
	size_t i,j,pos;

	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	char* tmp = (char*) malloc(sizeof(char)*s->length());

	for(i = 0 ; i < s->length(); i++)
		tmp[i] = '\0';

	j=0;
	for(i = toFind->length() + pos + 1; i < s->length(); i++)
	{
		tmp[j] = (*s)[i];
		j++;
	}

	val[index] = atof(tmp);
}
