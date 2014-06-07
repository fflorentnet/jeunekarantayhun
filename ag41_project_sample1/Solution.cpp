/*
 * Solution.cpp
 *
 *  Created on: May 17, 2014
 *      Author: florent
 */

/**
 * Conseil de Papa Caminada : Hill Climbing (Heuristique d'exploration maximale, recherche aléatoire)
 */
#include "Solution.h"
#include <algorithm>
#include <cmath>
namespace Calcul {
Solution::Solution(Data* dat) :
		d(dat) {
}
Solution::~Solution() {
}
bool Solution::operator<(Solution& s) {
	return (this->getValeur() < s.getValeur());
}
Solution::Solution(Solution &s) {
	d = s.getData();
	sol = s.sol;
}
Data* Solution::getData() {
	return d;
}

/*
 * Calcul la difference entre le temps 0 et la date du premier depart du livreur
 * et met a jour la solution
 * ( permet d'eviter les dates negatives )
 */
double Solution::computeDifference() {
	map<double, vector<Action*>*>::iterator itMap;
	vector<Action*>* vTemp;
	vector<Action*>::iterator itAction;
	Action* aTemp;
	double date = 0;
	double min = 1500000;

	for (itMap = sol.begin(); itMap != sol.end(); itMap++) {
		vTemp = (*itMap).second;
		date = (*itMap).first;
		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++) {
			aTemp = (*itAction);
			double ttemp = 0;
			if (aTemp->getType() == DEPLACEMENT) {
				Client* start = aTemp->getStart();
				Client* end = aTemp->getEnd();
				if (start == (Client*) 0) {
					ttemp = date - getData()->distanceClient(end);
				} else if (end == (Client*) 0) {
					ttemp = date - getData()->distanceClient(start);
				} else {

					ttemp = date - getData()->distanceClient(start, end);
				}
				//flux << "----> (Parti à " << ttemp << ")" << endl;
				if (ttemp < min) {
					min = ttemp;
				}
			}
		}
	}
	map<double, vector<Action*>*> tempSol;
	for (itMap = sol.begin(); itMap != sol.end(); itMap++) {
		vTemp = (*itMap).second;
		date = (*itMap).first;
		//vector<Action* >* veActions = new vector();
		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++) {
			if ((*itAction)->getType() == DEPOT)
				(*itAction)->getCommande()->setDate(
						(*itAction)->getCommande()->getDate() - min);
		}
		tempSol[date - min] = vTemp;
	}
	sol = tempSol;
	return min;
}

/*
 * @return le flux de l'ensemble des livraisons effectuées dans cette solution
 */
ostream& operator<<(ostream& flux, Solution& s) {
	map<double, vector<Action*>*>::iterator itMap;
	vector<Action*>* vTemp;
	vector<Action*>::iterator itAction;
	Action* aTemp;
	double date = 0;

	for (itMap = s.sol.begin(); itMap != s.sol.end(); itMap++) {
		vTemp = (*itMap).second;
		date = (*itMap).first;
		string temp = "A la date : ";
		flux << temp << date << endl;

		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++) {
			aTemp = (*itAction);
			if (aTemp->getType() == DEPOT) {
				flux << "Depot de "
						<< aTemp->getCommande()->getProduit()->getNom()
						<< " chez " << aTemp->getStart()->getNom() << endl;
				flux << "---> Produit demandé à "
						<< aTemp->getCommande()->getDate() << endl;
			} else if (aTemp->getType() == DEPLACEMENT) {
				Client* start = aTemp->getStart();
				Client* end = aTemp->getEnd();
				double ttemp = 0;
				if (start == (Client*) 0) {
					flux << "Deplacement terminé du fournisseur à "
							<< end->getNom() << endl;
					ttemp = date - s.getData()->distanceClient(end);
				} else if (end == (Client*) 0) {
					flux << "Deplacement terminé de " << start->getNom()
							<< " au fournisseur" << endl;
					ttemp = date - s.getData()->distanceClient(start);
				} else {

					flux << "Deplacement terminé de " << start->getNom()
							<< " à " << end->getNom() << endl;
					ttemp = date - s.getData()->distanceClient(start, end);
				}
				flux << "----> (Déplacement commencé à " << ttemp << ")"
						<< endl;
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
	double d1 = co1->getDate();
	double d2 = co2->getDate();

	return (d1 < d2);
}

double Solution::getValeur() {

	// Calcul des coûts de déplacement:
	double tempDep = 0;
	double tempStock = 0;

	vector<Action*> *veListeAction;
	Action* itAction;

	map<double, vector<Action*>*>::iterator itSol;
	vector<Action*>::iterator itAct;

	for (itSol = sol.begin(); itSol != sol.end(); itSol++) {
		double temps = (*itSol).first;
		veListeAction = (*itSol).second;
		for (itAct = veListeAction->begin(); itAct != veListeAction->end();
				itAct++) {
			itAction = (*itAct);
			if (itAction->getType() == DEPLACEMENT) {
				double ttemp = 0;
				if (itAction->getEnd() == (Client*) 0) {
					ttemp = getData()->getKTransport()
							* getData()->distanceClient(itAction->getStart());
					tempDep += ttemp;
				} else if (itAction->getStart() == (Client*) 0) {
					ttemp = getData()->getKTransport()
							* getData()->distanceClient(itAction->getEnd());
					tempDep += ttemp;
				} else {
					ttemp = getData()->getKTransport()
							* getData()->distanceClient(itAction->getStart(),
									itAction->getEnd());
					std::cout << ttemp << endl;
					tempDep += ttemp;
				}
			} else if (itAction->getType() == DEPOT) {
				Client* itCli = itAction->getStart();
				Commande* itCom = itAction->getCommande();
				double tprim = temps;
				double t = itCli->getKStockage() * abs(tprim - itCom->getDate());
				//std::cout << itCli->getKStockage() << "*" << itCli->getNom() << "/" << itCom->getProduit()->getNom() << "(" << itCom->getDate() << " - " << temps << ") d" << t << endl;
				tempStock += t;
			}
		}
	}
	std::cout << "Coût de deplacement: " << tempDep << endl;
	std::cout << "Coût de stockage: " << tempStock << endl;

	return (tempDep + tempStock);
}

/*
 * Genere une solution en attribuant les livraisons successivement en partant du dernier client
 */
double Solution::generate() {
	vector<Client*> listeAscClient = d->getListeClient();

	vector<double> t;

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

	cout << "Nombre de clients ayant commandé au moins un produit :"
			<< listeAscClient.size() << endl;

	cout << "Tri des elements..." << endl;
	sort(listeAscClient.begin(), listeAscClient.end(), compareClient);
	cout << "Tri terminé" << endl;

	Client* cLast = (Client*) listeAscClient.back();
	Client* cCurrent;
	Commande* commTemp;
	Commande* commLast = (Commande*) cLast->premiereCommande();

	double temp = commLast->getDate();
	t.push_back(temp);

	if (sol[temp] == NULL)
		sol[temp] = new vector<Action*>();
	sol[temp]->push_back(new Action((Client*) 0, cLast));

	for (itComm = cLast->getCommande()->begin();
			itComm != cLast->getCommande()->end(); itComm++) {
		commTemp = (Commande*) (*itComm);
		sol[temp]->push_back(new Action(cLast, commTemp));
	}

	sol[temp + d->distanceClient(cLast)] = new vector<Action*>();
	sol[temp + d->distanceClient(cLast)]->push_back(
			new Action(cLast, (Client*) 0));

	listeAscClient.pop_back();

	cout << "Calcul" << endl;
	double temps = 0;

	// On parcourt la liste des clients par ordre de commande : Du dernier à l'avant dernier
	while (!listeAscClient.empty()) {
		cout << "Iteration " << endl;
		cCurrent = (Client*) listeAscClient.back();
		commTemp = cCurrent->derniereCommande();

		if (commTemp != NULL) {

			double ttemp = t.back();
			if (commTemp->getDate() + d->distanceClient(cCurrent) > ttemp) {

				temps = ttemp - 2 * d->distanceClient(cCurrent);

				if (sol[temps] == NULL)
					sol[temps] = new vector<Action*>();

				sol[temps]->push_back(new Action((Client*) 0, cCurrent));
				t.push_back(temps);

				for (itComm = cCurrent->getCommande()->begin();
						itComm != cCurrent->getCommande()->end(); itComm++) {
					commTemp = (Commande*) (*itComm);
					sol[temps]->push_back(new Action(cCurrent, commTemp));
				}
				double retour = ttemp - d->distanceClient(cCurrent);

				if (sol[retour] == NULL)
					sol[retour] = new vector<Action*>();

				sol[retour]->insert(sol[retour]->begin(),
						new Action(cCurrent, (Client*) 0));
				//sol[retour]->push_back(new Action(cCurrent,(Client*)0));
				t.push_back(temps);

			} else {
				temps = cCurrent->premiereCommande()->getDate();

				if (sol[temps] == NULL)
					sol[temps] = new vector<Action*>();

				sol[temps]->push_back(new Action((Client*) 0, cCurrent));

				for (itComm = cCurrent->getCommande()->begin();
						itComm != cCurrent->getCommande()->end(); itComm++) {
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

Modification* Solution::deplacerAction(Action* ac, double tAct, double tDema) {
	Modification* m = NULL;
	if (sol[tAct]) {
		vector<Action*>* pVecSol = sol[tAct];
		//vector<Action *>::iterator pos = find(pVecSol->begin(), pVecSol->end(), ac) - pVecSol->begin();
		pVecSol->erase(std::remove(pVecSol->begin(), pVecSol->end(), ac),
				pVecSol->end());
		if (sol[tDema] == NULL)
			sol[tDema] = new vector<Action*>();
		sol[tDema]->push_back(ac);
		m = new Modification(ac, tAct, tDema);
	}
	return m;
}
Modification* Solution::meilleurMouvement() {
	Modification* m = NULL;

	return m;
}
}
