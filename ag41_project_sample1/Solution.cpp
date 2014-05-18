/*
 * Solution.cpp
 *
 *  Created on: May 17, 2014
 *      Author: florent
 */

#include "Solution.h"
#include "Commande.h"
#include <algorithm>
Solution::Solution() {
	// TODO Auto-generated constructor stub

}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}
void Solution::ajouterClient(Client* c) {
	listeClient.push_back(c);
}
int Solution::distanceClient(Client* c) {
	if (distanceFournisseur.find(c) != distanceFournisseur.end())
		return distanceFournisseur.at(c);
	else
		return -1;
}
void Solution::distanceClient(Client* c, int dist) {
	distanceFournisseur[c] = dist;
}
int Solution::distanceClient(Client* c1, Client* c2) {
	pair<Client*, Client*> p(c1, c2);
	if (distanceClients.find(p) != distanceClients.end())
		return distanceClients.at(p);
	else
		return -1;
}
void Solution::distanceClient(Client* c1, Client* c2, int dist) {
	pair<Client*, Client*> p(c1, c2);
	distanceClients[p] = dist;
}
ostream& operator<<(ostream& flux, Solution& s) {
	map<int, vector<Action*>* >::iterator itMap;
	vector<Action*>* vTemp;
	vector<Action*>::iterator itAction;
	Action* aTemp;
	int date=0;

	for (itMap = s.sol.begin() ; itMap != s.sol.end() ; itMap++)
	{
		vTemp = (*itMap).second;
		date = (*itMap).first;
		flux << "A la date " << date << ":" << endl;

		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
		{
			aTemp = (*itAction);
			if (aTemp->getType() == Action::DEPOT)
			{
				flux << "Depot de " << aTemp->getCommande()->getProduit()->getNom() << " chez " << aTemp->getStart()->getNom() << endl;
			}
			else if (aTemp->getType() == Action::DEPLACEMENT)
			{
				flux << "Deplachement de " << aTemp->getStart()->getNom() << " à " << aTemp->getEnd()->getNom() << endl;
			}
		}

		return flux;
	}

}
bool compareClient(Client* c1, Client* c2) {
	Commande* co1 = (*c1).derniereCommande();
	Commande* co2 = (*c2).derniereCommande();
	if (co1 == (Commande*) 0 || co2 == (Commande*) 0)
		return false;
	int d1 = co1->getDate();
	int d2 = co2->getDate();

	return (d1 < d2);
}
int Solution::generate() {
	vector<Client*> listeAscClient = listeClient;
	vector<pair<string, int> > t;
	cout << "Recopie des données" << endl;
	cout << "Nombre de clients : " << listeAscClient.size() << endl;
	vector<Commande*>::iterator itComm;

	vector<Client*>::iterator itC;
	for (itC = listeAscClient.begin(); itC != listeAscClient.end(); itC++) {
		Client* c = (Client*) (*itC);
		if (c->derniereCommande() == (Commande*) 0) {
			listeAscClient.erase(
					std::remove(listeAscClient.begin(), listeAscClient.end(),
							c), listeAscClient.end());
			itC = listeAscClient.begin(); // Faudra penser à optimiser ça. un jour.
		}
	}
	int i = listeAscClient.size();

	cout << "Nombre de clients ayant commandé au moins un produit :"
			<< listeAscClient.size() << endl;

	cout << "Tri des elements..." << endl;
	sort(listeAscClient.begin(), listeAscClient.end(), compareClient);
	cout << "Tri terminé" << endl;
	Client* cLast = (Client*) listeAscClient.back();
	Client* cCurrent;
	Commande* commTemp;
	Commande* commLast = (Commande*) cLast->premiereCommande();
	string stemp = cLast->getNom() + "," + (commLast->getProduit())->getNom();
	int temp = commLast->getDate();

	pair<string, int> ptemp(stemp, temp);

	t.push_back(ptemp);
	for (itComm = cLast->getCommande()->begin();
			itComm != cLast->getCommande()->end(); itComm++) {
		commTemp = (Commande*) (*itComm);
		stemp = cLast->getNom() + "," + ((*itComm)->getProduit())->getNom();
		t.push_back(ptemp);
	}
	listeAscClient.pop_back();
	int j = 0;

	cout << "Calcul" << endl;
	int temps=0;
	while (!listeAscClient.empty()) {
		cout << "Iteration " << j << "\n";
		cCurrent = (Client*) listeAscClient.back();
		commTemp = cCurrent->derniereCommande();
		if (commTemp != NULL) {
			ptemp = t.back();
			int ttemp = ptemp.second;
			if (commTemp->getDate() > ttemp) {
				temps = ttemp - 2 * distanceClient(cCurrent);
				sol[temps]->push_back(new Action(cLast, cCurrent));
				for (itComm = cCurrent->getCommande()->begin();
						itComm != cCurrent->getCommande()->end(); itComm++) {
					commTemp = (Commande*) (*itComm);
					stemp = cCurrent->getNom() + ","
							+ commTemp->getProduit()->getNom();

					ptemp = make_pair(stemp,temps);
					t.push_back(ptemp);

					sol[temps]->push_back(new Action(cCurrent, commTemp));
				}
			} else {

				temps = cCurrent->premiereCommande()->getDate();
				sol[temps]->push_back(new Action(cLast, cCurrent));

				for (itComm = cCurrent->getCommande()->begin();
						itComm != cCurrent->getCommande()->end(); itComm++) {
					stemp = cCurrent->getNom() + ","
							+ (*itComm)->getProduit()->getNom();
					commTemp = cCurrent->premiereCommande();
					ptemp = make_pair(stemp, commTemp->getDate());
					t.push_back(ptemp);
					sol[temps]->push_back(new Action(cCurrent, commTemp));
				}
			}
		}
		listeAscClient.pop_back();
	}
	vector<pair<string, int> >::iterator it;

	for (it = t.begin(); it != t.end(); it++) {
		ptemp = (*it);
		string te = ptemp.first;
		int tem = ptemp.second;
		cout << "t(" << te << ") = " << tem << endl;
		i--;
	}
	cout << "----------------";
	return 0;
}

