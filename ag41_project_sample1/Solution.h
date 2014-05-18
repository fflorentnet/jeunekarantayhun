/*
 * Solution.h
 *
 *  Created on: May 17, 2014
 *      Author: florent
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_
#include <map>
#include <utility>
#include <vector>
#include "Client.h"
#include "Action.h"

using namespace std;

class Solution {
private:
	map<pair<Client*, Client*>, int> distanceClients;
	map<Client*, int> distanceFournisseur;
	vector<Client*> listeClient;
	map<int, vector<Action*>* > sol;
public:
	Solution();
	virtual ~Solution();

	void ajouterClient(Client* c);
	int distanceClient(Client* c);
	void distanceClient(Client* c, int dist);
	int distanceClient(Client* c1, Client* c2);
	void distanceClient(Client* c1, Client* c2, int dist);
	friend ostream& operator<< (ostream& flux, Solution& s);


	int generate();
};

#endif /* SOLUTION_H_ */
