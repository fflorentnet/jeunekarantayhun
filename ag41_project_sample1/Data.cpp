/*
 * Data.cpp
 *
 * Rassemble les donnees du probleme
 *
 *  Created on: May 25, 2014
 *      Author: florent
 */

#include "Data.h"

namespace Donnees {
Data::Data() :
		kTransport(0) {
}

Data::~Data() {
}
Data::Data(Data &d) {
	distanceClients = this->distanceClients;
	distanceFournisseur = this->distanceFournisseur;
	listeClient = this->listeClient;
	sol = this->sol;
}
void Data::ajouterClient(Client* c) {
	listeClient.push_back(c);
}
double Data::distanceClient(Client* c) {
	if (distanceFournisseur.find(c) != distanceFournisseur.end())
		return distanceFournisseur.at(c);
	else
		return -1;
}
void Data::distanceClient(Client* c, double dist) {
	distanceFournisseur[c] = dist;
}
double Data::distanceClient(Client* c1, Client* c2) {
	pair<Client*, Client*> p(c1, c2);
	if (distanceClients.find(p) != distanceClients.end())
		return distanceClients.at(p);
	else
		return -1;
}
void Data::distanceClient(Client* c1, Client* c2, double dist) {
	pair<Client*, Client*> p(c1, c2);
	distanceClients[p] = dist;
}
double Data::getKTransport() {
	return kTransport;
}
void Data::setKTransport(double k) {
	kTransport = k;
}
vector<Client*> Data::getListeClient() {
	return listeClient;
}
}
