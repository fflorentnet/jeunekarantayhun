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
namespace Donnees {
class Data {
	map<pair<Client*, Client*>, double> distanceClients;
	map<Client*, double> distanceFournisseur;
	vector<Client*> listeClient;
	map<double, vector<Action*>*> sol;
	double kTransport;
public:
	Data();
	virtual ~Data();
	Data(Data &d);
	vector<Client*> getListeClient();
	void ajouterClient(Client* c);
	double distanceClient(Client* c);
	void distanceClient(Client* c, double dist);
	double distanceClient(Client* c1, Client* c2);
	void distanceClient(Client* c1, Client* c2, double dist);
	double getKTransport();
	void setKTransport(double k);

};
}
#endif /* DATA_H_ */
