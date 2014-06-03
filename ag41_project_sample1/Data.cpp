/*
 * Data.cpp
 *
 *  Created on: May 25, 2014
 *      Author: florent
 */

#include "Data.h"

namespace Donnees
{
	Data::Data(): kTransport(0) {
		// TODO Auto-generated constructor stub

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
	int Data::distanceClient(Client* c) {
		if (distanceFournisseur.find(c) != distanceFournisseur.end())
			return distanceFournisseur.at(c);
		else
			return -1;
	}
	void Data::distanceClient(Client* c, int dist) {
		distanceFournisseur[c] = dist;
	}
	int Data::distanceClient(Client* c1, Client* c2) {
		pair<Client*, Client*> p(c1, c2);
		if (distanceClients.find(p) != distanceClients.end())
			return distanceClients.at(p);
		else
			return -1;
	}
	void Data::distanceClient(Client* c1, Client* c2, int dist) {
		pair<Client*, Client*> p(c1, c2);
		distanceClients[p] = dist;
	}
	int Data::getKTransport()
	{
		return kTransport;
	}
	void Data::setKTransport(int k)
	{
		kTransport = k;
	}
	vector<Client*> Data::getListeClient()
	{
		return listeClient;
	}

	int Data::getCapacite() const {
		return capacite;
	}

	void Data::setCapacite(int capacite) {
		this->capacite = capacite;
	}
}

