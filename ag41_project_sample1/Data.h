/*
 * Data.h
 *
 *  Created on: May 25, 2014
 *      Author: florent
 */

#ifndef DATA_H_
#define DATA_H_
using namespace std;
#include <vector>
#include <map>
#include "Client.h"
#include "Action.h"
class Data {
	map<pair<Client*, Client*>, int> distanceClients;
	map<Client*, int> distanceFournisseur;
	vector<Client*> listeClient;
	map<int, vector<Action*>* > sol;
public:
	Data();
	virtual ~Data();
	vector<Client*> getListeClient();
	void ajouterClient(Client* c);
	int distanceClient(Client* c);
	void distanceClient(Client* c, int dist);
	int distanceClient(Client* c1, Client* c2);
	void distanceClient(Client* c1, Client* c2, int dist);


};

#endif /* DATA_H_ */
