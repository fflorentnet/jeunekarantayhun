/*
 * Data.cpp
 *
 *  Created on: May 25, 2014
 *      Author: florent
 */

#include "Data.h"
#include <limits>

namespace Donnees
{
Data::Data(): kTransport(0) {
	// TODO Auto-generated constructor stub
	listeClient.push_back((Client*)0);

}

Data::~Data() {
	// TODO Auto-generated destructor stub
}
Data::Data(Data &d)
{
	distanceClients = this->distanceClients;
	distanceFournisseur = this->distanceFournisseur;
	listeClient =  this->listeClient;
	sol = this->sol;
}
void Data::ajouterClient(Client* c) {
	listeClient.push_back(c);
}
double Data::distanceClient(Client* c) {
	if (distanceFournisseur.find(c) != distanceFournisseur.end())
		return distanceFournisseur.at(c);
	else
		return std::numeric_limits<double>::infinity();
}
void Data::distanceClient(Client* c, double dist) {
	distanceFournisseur[c] = dist;
}
double Data::distanceClient(Client* c1, Client* c2) {
	if (c2 == NULL)
		return distanceClient(c1);
	if (c1 == NULL)
		return distanceClient(c2);
	pair<Client*, Client*> p(c1, c2);
	if (distanceClients.find(p) != distanceClients.end())
		return distanceClients.at(p);
	else
		return std::numeric_limits<double>::infinity();
}
void Data::distanceClient(Client* c1, Client* c2, double dist) {
	pair<Client*, Client*> p(c1, c2);
	distanceClients[p] = dist;
	pair<Client*, Client*> p2(c2, c1);
	distanceClients[p2] = dist;
}
double Data::getKTransport()
{
	return kTransport;
}
void Data::setKTransport(double k)
{
	kTransport = k;
}
vector<Client*> Data::getListeClient()
{
	return listeClient;
}

double Data::getCapacite() const {
	return capacite;
}

void Data::setCapacite(double capacite) {
	this->capacite = capacite;
}
vector<Client*> Data::getPath(Client* a, Client* b)
{
	vector<Client*> temp = Chemins[pair<Client*, Client*>(a,b)];
	temp.insert(temp.begin(), a);
	return temp;
}
void Data::floydWarshall()
{
	vector<Client*>::iterator k;
	vector<Client*>::iterator i;
	vector<Client*>::iterator j;
	map<pair<Client*, Client*>, double>::iterator itDistance;

	Client* cK;
	Client* cI;
	Client* cJ;
	for (k = listeClient.begin(); k != listeClient.end(); ++k)
	{
		mNext[std::pair<Client*,Client*>((Client*)NULL, (*k))] = (*k);
		mNext[std::pair<Client*,Client*>((*k),(Client*)NULL)] = (Client*)NULL;
	}

	for (itDistance = distanceClients.begin(); itDistance != distanceClients.end(); ++itDistance)
	{
			mNext[(*itDistance).first] = (*itDistance).first.second;
	}
	for (k = listeClient.begin(); k != listeClient.end(); ++k)
	{
		for (i = listeClient.begin(); i != listeClient.end(); ++i)
		{
			for (j = listeClient.begin(); j != listeClient.end(); ++j)
			{
				cK = (*k);
				cI = (*i);
				cJ = (*j);
				if (cI != cJ)
				{
					if (distanceClient(cI,cK) != std::numeric_limits<double>::infinity()&&  distanceClient(cK,cJ) != std::numeric_limits<double>::infinity())
					{
						if ((distanceClient(cI,cK) + distanceClient(cK,cJ)) <= distanceClient(cI,cJ))
						{

							distanceClient(cI,cJ,(distanceClient(cI,cK) + distanceClient(cK,cJ)));
							pair<Client*, Client*> p((*i), (*j));
							pair<Client*, Client*> p2((*i), (*k));
							mNext[p] = mNext[p2];

						}
					}
				}
			}

		}
	}
	Next();
}
void Data::toString()
{
	vector<Client*>::iterator i;
	vector<Client*>::iterator j;
	Client* I;
	Client* J;
	std::cout << "\t";
	for (j = listeClient.begin(); j != listeClient.end(); ++j)
	{
		J = (*j);
		if (J != NULL)
			std::cout << J->getNom() << "\t";
	}
	std::cout << endl;
	for (i = listeClient.begin(); i != listeClient.end(); ++i)
	{
		I = (*i);

		if (I != NULL)
		{
			std::cout << I->getNom() << "\t";
			for (j = listeClient.begin(); j != listeClient.end(); ++j)
			{
				J = (*j);
				if (J != NULL)
				{
					std::cout << distanceClient(I,J) << "\t\t";
				}
			}
			std::cout << endl;
		}
	}

	std::cout << "\tFournisseur" << endl;
	for (i = listeClient.begin(); i != listeClient.end(); ++i)
	{

		I = (*i);
		if (I != NULL)
		{
			std::cout << I->getNom() << "\t";
			std::cout << distanceClient(I) << endl;
		}
	}


	vector<Client*> vCli;
	vector<Client*>::iterator k;

	//std::cout << "Chemin:" << endl;
	for (i = listeClient.begin(); i != listeClient.end(); ++i)
	{
		I = (*i);

		if (I != NULL)
		{

			for (j = listeClient.begin(); j != listeClient.end(); ++j)
			{
				J = (*j);
				if (J != NULL)
				{
					if (I != J)
					{
						std::cout << "Debut -> " << I->getNom() << " -> ";
						vCli = Chemins[pair<Client*, Client*>(I,J)];
						for (k = vCli.begin(); k != vCli.end(); ++k)
						{
							if ((*k) != NULL)
								std::cout << (*k)->getNom() << " -> ";
							else
								std::cout << "Fournisseur -> ";
						}
						std::cout << "Fin" << endl;
					}
				}
			}
		}
	}
}
void Data::Next()
{
	vector<Client*>::iterator i;
	vector<Client*>::iterator j;
	Client* u;
	Client* uBis;
	Client* v;
	pair<Client*, Client*> p;
	for (i = listeClient.begin(); i != listeClient.end(); ++i)
	{
		for (j = listeClient.begin(); j != listeClient.end(); ++j)
		{
			u = (*i);
			v = (*j);

			vector<Client*> vCli;
			p = pair<Client*, Client*>(u,v);
			u = mNext[p];
			vCli.push_back(u);
			while (u != v)
			{
				uBis = u;
				p = pair<Client*, Client*>(u,v);
				u = mNext[p];
				vCli.push_back(u);
				if (uBis == u)
					break;

			}
			Chemins[pair<Client*, Client*>((*i),(*j))]=vCli;
		}
	}
}
}

