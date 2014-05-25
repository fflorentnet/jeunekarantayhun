/*
 * Solution.cpp
 *
 *  Created on: May 17, 2014
 *      Author: florent
 */

#include "Solution.h"
#include "Commande.h"
#include <algorithm>
Solution::Solution(Data* dat): d(dat) {
	// TODO Auto-generated constructor stub

}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}ostream& operator<<(ostream& flux, Solution& s) {
	map<int, vector<Action*>* >::iterator itMap;
	vector<Action*>* vTemp;
	vector<Action*>::iterator itAction;
	Action* aTemp;
	int date=0;

	for (itMap = s.sol.begin() ; itMap != s.sol.end() ; itMap++)
	{
		vTemp = (*itMap).second;
		date = (*itMap).first;
		char *temp = "A la date : ";
		flux << temp << date << endl;

		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
		{
			aTemp = (*itAction);
			if (aTemp->getType() == DEPOT)
			{
				flux << "Depot de " << aTemp->getCommande()->getProduit()->getNom() << " chez " << aTemp->getStart()->getNom() << endl;
			}
			else if (aTemp->getType() == DEPLACEMENT)
			{
				Client* start = aTemp->getStart();
				if (start == (Client*)0)
					flux << "Deplacement du fournisseur à " << aTemp->getEnd()->getNom() << endl;
				else
					flux << "Deplacement de " << aTemp->getStart()->getNom() << " à " << aTemp->getEnd()->getNom() << endl;
			}
		}

	}

	return flux;
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
	vector<Client*> listeAscClient = d->getListeClient();

	vector<int> t;

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
	int temp = commLast->getDate();
	t.push_back(temp);

	if (sol[temp] == NULL)
		sol[temp] = new vector<Action*>();
	sol[temp]->push_back(new Action((Client*)0, cLast));

	for (itComm = cLast->getCommande()->begin();itComm != cLast->getCommande()->end(); itComm++) {
		commTemp = (Commande*) (*itComm);
		sol[temp]->push_back(new Action(cLast, commTemp));

	}
	listeAscClient.pop_back();

	cout << "Calcul" << endl;
	int temps=0;
	while (!listeAscClient.empty()) {
		cout << "Iteration " << endl;
		cCurrent = (Client*) listeAscClient.back();
		commTemp = cCurrent->derniereCommande();
		if (commTemp != NULL) {
			int ttemp = t.back();
			if (commTemp->getDate() > ttemp) {

				temps = ttemp - 2 * d->distanceClient(cCurrent);

				if (sol[temps] == NULL)
					sol[temps] = new vector<Action*>();

				sol[temps]->push_back(new Action((Client*)0, cCurrent));
				t.push_back(temps);

				for (itComm = cCurrent->getCommande()->begin(); itComm != cCurrent->getCommande()->end(); itComm++) {
					commTemp = (Commande*) (*itComm);
					sol[temps]->push_back(new Action(cCurrent, commTemp));
				}
			}
			else {
				temps = cCurrent->premiereCommande()->getDate();

				if (sol[temps] == NULL)
					sol[temps] = new vector<Action*>();

				sol[temps]->push_back(new Action((Client*)0, cCurrent));

				for (itComm = cCurrent->getCommande()->begin();	itComm != cCurrent->getCommande()->end(); itComm++) {
					commTemp = cCurrent->premiereCommande();
					sol[temps]->push_back(new Action(cCurrent, commTemp));
				}

				t.push_back(temps);
			}
		}
		listeAscClient.pop_back();
	}
	cout << "Fin du calcul" << endl;
	return 0;
}

