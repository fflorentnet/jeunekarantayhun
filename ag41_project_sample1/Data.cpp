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
		return std::numeric_limits<int>::infinity();
}
void Data::distanceClient(Client* c, int dist) {
	distanceFournisseur[c] = dist;
}
int Data::distanceClient(Client* c1, Client* c2) {
	if (c2 == NULL)
		return distanceClient(c1);
	if (c1 == NULL)
		return distanceClient(c2);
	pair<Client*, Client*> p(c1, c2);
	if (distanceClients.find(p) != distanceClients.end())
		return distanceClients.at(p);
	else
		return std::numeric_limits<int>::infinity();
}
void Data::distanceClient(Client* c1, Client* c2, int dist) {
	pair<Client*, Client*> p(c1, c2);
	distanceClients[p] = dist;
	pair<Client*, Client*> p2(c2, c1);
	distanceClients[p2] = dist;
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
/*
 * let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
let next be a |V| × |V| array of vertex indices initialized to null

	procedure FloydWarshallWithPathReconstruction ()
	for each edge (u,v)
	  dist[u][v] ← w(u,v)  // the weight of the edge (u,v)
	  next[u][v] ← v
	for k from 1 to |V| // standard Floyd-Warshall implementation
	  for i from 1 to |V|
		 for j from 1 to |V|
			if dist[i][k] + dist[k][j] < dist[i][j] then
			   dist[i][j] ← dist[i][k] + dist[k][j]
			   next[i][j] ← next[i][k]
 *
 */
void Data::floydWarshall()
{
	vector<Client*>::iterator k;
	vector<Client*>::iterator i;
	vector<Client*>::iterator j;
	map<pair<Client*, Client*>, int>::iterator itDistance;

	/*for (itDistance = distanceClients.begin(); itDistance != distanceClients.end(); ++itDistance)
	{
		mNext[(*itDistance).first] = (*itDistance).first.first;
	}*/
	Client* cK;
	Client* cI;
	Client* cJ;
	for (k = listeClient.begin(); k != listeClient.end(); ++k)
	{
		for (i = listeClient.begin(); i != listeClient.end(); ++i)
		{
			for (j = listeClient.begin(); j != listeClient.end(); ++j)
			{
				cK = (*k);
				cI = (*i);
				cJ = (*j);
				if ((distanceClient(cI,cK) + distanceClient(cK,cJ)) < distanceClient(cI,cJ))
				{
					distanceClient(cI,cJ,(distanceClient(cI,cK) + distanceClient(cK,cJ)));
					std::cout << "test" << endl;
					/*
					pair<Client*, Client*> p((*i), (*j));
					pair<Client*, Client*> p2((*i), (*k));
					mNext[p] = mNext[p2];
					*/
				}

			}

		}
	}
	//Next();
}
void Data::Next()
{
	/*
	 *
procedure Path(u, v)
   if next[u][v] = null then
       return []
   path = [u]
   while u ≠ v
       u ← next[u][v]
       path.append(u)
   return path
	 */
	vector<Client*>::iterator i;
	vector<Client*>::iterator j;
	Client* u;
	Client* v;

	pair<Client*, Client*> p;
	for (i = listeClient.begin(); i != listeClient.end(); ++i)
	{
		for (j = listeClient.begin(); j != listeClient.end(); ++j)
		{
			u = (*i);
			v = (*j);
			vector<Client*> vCli;
			vCli.push_back(u);
			while (u != v)
			{
				p = pair<Client*, Client*>(u,v);
				u = mNext[p];
				vCli.push_back(u);
			}
			Chemins[pair<Client*, Client*>((*i),(*j))]=vCli;
		}
	}
}
}

