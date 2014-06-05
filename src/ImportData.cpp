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
	bool setNbCust = false;
	string tmpS;
	char *str;
	char *str2;
	char *tok;
	int numCLient;

	string customer = string("CUSTOMER");
	string n = string("NBR_PRODUCT");
	string c = string("TRANSPORTER_CAPACITY");
	string eta = string("TRANSPORTER_DELIVERY_COST_ETA");
	string beta = string("CUSTOMER_HOLDING_COSTS");
	string tau = string("TRANSPORTER_DELIVERY_TIME_SUPPLIER_CUSTOMER");
	string cli = string("JOB_CUSTOMER");
	string di = string("JOB_DUE_DATES");
	string nbCust = string("NBR_CUSTOMER");
	string CustToCust = string("TIME_CUSTOMER_CUSTOMER");

	this->d->m = 0;

	while(!this->cfile.eof())
	{
		getline(this->cfile,tmpS);

		if(tmpS.find(n) >= 0)
		{
			this->setValue(&tmpS, &n, &this->d->n);

			getline(this->cfile,tmpS);
			if(tmpS.find(nbCust) >= 0)
			{
				this->setValue(&tmpS, &nbCust, &this->d->m);
				getline(this->cfile,tmpS);
				setNbCust = true;
			}

			this->setValue(&tmpS, &c, &this->d->c);
			getline(this->cfile,tmpS);
			this->setValue(&tmpS, &eta, &this->d->eta);

			while(!this->cfile.eof())
			{
				getline(this->cfile,tmpS);

				int test1 = tmpS.find(cli);
				int test2 = tmpS.find(di);
				int test3 = tmpS.find(customer);
				int test4 = tmpS.find(CustToCust);
				if(test1 >= 0)
					this->setTable(&tmpS, &cli, this->d->cl);
				else if(test2 >= 0)
					this->setTable(&tmpS, &di, this->d->d);
				else if(test3 >= 0 && test4 < 0)
				{
					str = const_cast<char*>(tmpS.c_str());
					tok = strtok(str,":");
					str = NULL;
					tok = strtok(str,":");
					str2 = tok;
					tok = strtok(str2,";");
					numCLient = atoi(tok);

					getline(this->cfile,tmpS);
					this->setValue(&tmpS, &beta, &(this->d->beta[numCLient-1]));
					getline(this->cfile,tmpS);
					this->setValue(&tmpS, &tau, &(this->d->tau[numCLient-1]));
					if(!setNbCust)
						this->d->m++;
				}
			}
			if(!setNbCust)
				this->d->m--;
		}
	}
}

void ImportData::setValue(string *s, string *toFind, int *val)
{
	size_t pos;
	char *str = const_cast<char*>(s->c_str());
	char *str2;
	char *tok;


	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	tok = strtok(str,":");
	str = NULL;
	tok = strtok(str,":");
	str2 = tok;
	tok = strtok(str2,";");

	*val = atoi(tok);
}

void ImportData::setValue(string* s, string* toFind, double* val)
{
	size_t pos;
	char *str = const_cast<char*>(s->c_str());
	char *str2;
	char *tok;


	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	tok = strtok(str,":");
	str = NULL;
	tok = strtok(str,":");
	str2 = tok;
	tok = strtok(str2,";");

	*val = atof(tok);
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

void ImportData::setTable(string* s, string* toFind, double* val)
{
	size_t i = 0, j, pos, cpt = 0;
	char* tmp;

	pos = s->find(*toFind);
	if(pos < 0) // If not find or not corresponding
		return;

	i = toFind->length() + pos;
	for(i = i + 1; (*s)[i] != ';' && i < s->length(); i++)
	{
		tmp = (char*) malloc(sizeof(char)*s->length());
		for(j=0;j<s->length();j++)
			tmp[j] = '\0';
		j=0;
		for(; i < s->length() && (*s)[i] != ';'; i++)
		{
			tmp[j] = (*s)[i];
			j++;
		}

		val[cpt] = atof(tmp);
		free(tmp);
		cpt++;
	}
}
