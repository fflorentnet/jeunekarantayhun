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
	private:
		map<pair<Client*, Client*>, int> distanceClients;
		map<pair<Client*, Client*>, vector<Client*> > Chemins;
		map<pair<Client*, Client*>, Client*> mNext;

		map<Client*, int> distanceFournisseur;
		vector<Client*> listeClient;
		map<int, vector<Action*>* > sol;
		int kTransport;
		int capacite;
		void Next();
	public:
		Data();
		virtual ~Data();
		Data(Data &d);
		vector<Client*> getListeClient();
		void ajouterClient(Client* c);
		int distanceClient(Client* c);
		void distanceClient(Client* c, int dist);
		int distanceClient(Client* c1, Client* c2);
		void distanceClient(Client* c1, Client* c2, int dist);
		int getKTransport();
		void setKTransport(int k);
		int getCapacite() const;
		void setCapacite(int capacite);
		void floydWarshall();
};
}
#endif /* DATA_H_ */
