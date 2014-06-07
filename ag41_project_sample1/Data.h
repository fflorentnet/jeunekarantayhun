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
namespace Donnees
{
	class Data {
		map<pair<Client*, Client*>, float> distanceClients;
		map<Client*, float> distanceFournisseur;
		vector<Client*> listeClient;
		map<float, vector<Action*>* > sol;
		float kTransport;
		float capacite;
	public:
		Data();
		virtual ~Data();
		Data(Data &d);
		vector<Client*> getListeClient();
		void ajouterClient(Client* c);
		float distanceClient(Client* c);
		void distanceClient(Client* c, float dist);
		float distanceClient(Client* c1, Client* c2);
		void distanceClient(Client* c1, Client* c2, float dist);
		float getKTransport();
		void setKTransport(float k);
	float getCapacite() const;
	void setCapacite(float capacite);
};
}
#endif /* DATA_H_ */
