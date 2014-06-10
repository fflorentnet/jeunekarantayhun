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
#include <limits>
#include <cmath>
namespace Calcul
{
Solution::Solution(Data* dat): d(dat) {
	// TODO Auto-generated constructor stub

}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}

bool Solution::operator<(Solution& s)
{
	return (this->getValeur() < s.getValeur());
}
Solution::Solution(Solution* s)
{
	d = s->getData();
	sol = map<double,vector<Action*>* >(s->sol);
}
Data* Solution::getData()
{
	return d;
}
double Solution::computeDifference()
{
	map<double, vector<Action*>* >::iterator itMap;
	vector<Action*>* vTemp;
	vector<Action*>::iterator itAction;
	Action* aTemp;
	double date=0;
	double min = 1500000;

	for (itMap = sol.begin() ; itMap != sol.end() ; itMap++)
	{
		vTemp = (*itMap).second;
		date = (*itMap).first;
		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
		{
			aTemp = (*itAction);
			double ttemp = 0;
			if (aTemp->getType() == Donnees::DEPLACEMENT)
			{
				Client* start = aTemp->getStart();
				Client* end = aTemp->getEnd();
				if (start == (Client*)0)
				{
					ttemp = date - getData()->distanceClient(end);
				}
				else if (end == (Client*)0){
					ttemp = date - getData()->distanceClient(start);
				}
				else{

					ttemp = date - getData()->distanceClient(start, end);
				}
				//flux << "----> (Parti à " << ttemp << ")" << endl;
				if (ttemp < min)
				{
					min = ttemp;
				}
			}
		}
	}
	map<double, vector<Action*>* > tempSol;
	for (itMap = sol.begin() ; itMap != sol.end() ; itMap++)
	{
		vTemp = (*itMap).second;
		date = (*itMap).first;
		//vector<Action* >* veActions = new vector();
		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
		{
			if ((*itAction)->getType() == Donnees::DEPOT)
				(*itAction)->getCommande()->setDate((*itAction)->getCommande()->getDate() - min);
		}
		tempSol[date-min] = vTemp;
	}
	sol = tempSol;
	return min;
}
ostream& operator<<(ostream& flux, Solution& s) {
	map<double, vector<Action*>* >::iterator itMap;
	vector<Action*>* vTemp;
	vector<Action*>::iterator itAction;
	Action* aTemp;
	double date=0;

	for (itMap = s.sol.begin() ; itMap != s.sol.end() ; itMap++)
	{
		vTemp = (*itMap).second;
		date = (*itMap).first;
		string temp = "A la date : ";
		flux << temp << date << endl;

		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
		{
			aTemp = (*itAction);
			if (aTemp->getType() == Donnees::DEPOT)
			{
				flux << "Depot de " << aTemp->getCommande()->getProduit()->getNom() << " chez " << aTemp->getStart()->getNom() << endl;
				flux << "---> Produit demandé à " << aTemp->getCommande()->getDate() << endl;
			}
			else if (aTemp->getType() == Donnees::DEPLACEMENT)
			{
				Client* start = aTemp->getStart();
				Client* end = aTemp->getEnd();
				double ttemp = 0;
				if (start == (Client*)0)
				{
					flux << "Deplacement terminé du fournisseur à " << end->getNom() << endl;
					ttemp = date - s.getData()->distanceClient(end);
				}
				else if (end == (Client*)0){
					flux << "Deplacement terminé de " << start->getNom() << " au fournisseur" << endl;
					ttemp = date - s.getData()->distanceClient(start);
				}
				else{

					flux << "Deplacement terminé de " << start->getNom() << " à " << end->getNom() << endl;
					ttemp = date - s.getData()->distanceClient(start, end);
				}
				flux << "----> (Déplacement commencé à " << ttemp << ")" << endl;
			}
		}

	}

	return flux;
}
ostream& operator<<(ostream& flux, Solution* s) {
	map<double, vector<Action*>* >::iterator itMap;
	vector<Action*>* vTemp;
	vector<Action*>::iterator itAction;
	Action* aTemp;
	double date=0;

	for (itMap = s->sol.begin() ; itMap != s->sol.end() ; itMap++)
	{
		vTemp = (*itMap).second;
		date = (*itMap).first;
		string temp = "A la date : ";
		flux << temp << date << endl;

		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
		{
			aTemp = (*itAction);
			if (aTemp->getType() == Donnees::DEPOT)
			{
				flux << "Depot de " << aTemp->getCommande()->getProduit()->getNom() << " chez " << aTemp->getStart()->getNom() << endl;
				flux << "---> Produit demandé à " << aTemp->getCommande()->getDate() << endl;
			}
			else if (aTemp->getType() == Donnees::DEPLACEMENT)
			{
				Client* start = aTemp->getStart();
				Client* end = aTemp->getEnd();
				double ttemp = 0;
				if (start == (Client*)0)
				{
					flux << "Deplacement terminé du fournisseur à " << end->getNom() << endl;
					ttemp = date - s->getData()->distanceClient(end);
				}
				else if (end == (Client*)0){
					flux << "Deplacement terminé de " << start->getNom() << " au fournisseur" << endl;
					ttemp = date - s->getData()->distanceClient(start);
				}
				else{

					flux << "Deplacement terminé de " << start->getNom() << " à " << end->getNom() << endl;
					ttemp = date - s->getData()->distanceClient(start, end);
				}
				flux << "----> (Déplacement commencé à " << ttemp << ")" << endl;
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
	float tempDep = 0;
	float tempStock = 0;

	vector<Action*> *veListeAction;
	Action* itAction;

	map<double, vector<Action*>* >::iterator itSol;
	vector<Action*>::iterator itAct;

	for (itSol=sol.begin(); itSol != sol.end(); itSol++)
	{
		double temps = (*itSol).first;
		veListeAction = (*itSol).second;
		for (itAct = veListeAction->begin(); itAct != veListeAction->end(); itAct++)
		{
			itAction = (*itAct);
			if (itAction->getType() == Donnees::DEPLACEMENT)
			{
				double ttemp = 0;
				if (itAction->getEnd() == (Client*)0)
				{
					ttemp = getData()->getKTransport() * getData()->distanceClient(itAction->getStart());
					tempDep += ttemp;
				}
				else if (itAction->getStart() == (Client*)0)
				{
					ttemp = getData()->getKTransport() * getData()->distanceClient(itAction->getEnd());
					tempDep += ttemp;
				}
				else
				{
					ttemp = getData()->getKTransport() * getData()->distanceClient(itAction->getStart(), itAction->getEnd());
					std::cout << ttemp << endl;
					tempDep += ttemp;
				}
			}
			else if (itAction->getType() == Donnees::DEPOT)
			{
				Client* itCli = itAction->getStart();
				Commande* itCom = itAction->getCommande();
				double tprim = temps;
				float t = itCli->getKStockage() * abs(tprim - itCom->getDate());
				//std::cout << itCli->getKStockage() << "*" << itCli->getNom() << "/" << itCom->getProduit()->getNom() << "(" << itCom->getDate() << " - " << temps << ") d" << t << endl;
				tempStock += t;
			}
		}
	}
	std::cout << "Coût de deplacement: " << tempDep << endl;
	std::cout << "Coût de stockage: " << tempStock << endl;

	return (tempDep+tempStock);
}
double Solution::generate() {
	vector<Client*> listeAscClient = d->getListeClient();

	vector<double> t;

	cout << "Recopie des données" << endl;
	cout << "Nombre de clients : " << listeAscClient.size() << endl;

	vector<Commande*>::iterator itComm;

	vector<Client*>::iterator itC;
	for (itC = listeAscClient.begin(); itC != listeAscClient.end(); itC++) {
		Client* c = (Client*) (*itC);
		if (c != NULL)
		{
			if (c->derniereCommande() == (Commande*) 0) {
				listeAscClient.erase(
						std::remove(listeAscClient.begin(), listeAscClient.end(),
								c), listeAscClient.end());
				itC = listeAscClient.begin(); // Faudra penser à optimiser ça. un jour.
			}
		}
		else
			listeAscClient.erase(itC);
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
	sol[temp]->push_back(new Action((Client*)0, cLast));

	for (itComm = cLast->getCommande()->begin();itComm != cLast->getCommande()->end(); itComm++) {
		commTemp = (Commande*) (*itComm);
		sol[temp]->push_back(new Action(cLast, commTemp));

	}

	sol[temp+d->distanceClient(cLast)] = new vector<Action*>();
	sol[temp+d->distanceClient(cLast)]->push_back(new Action(cLast, (Client*)0));

	listeAscClient.pop_back();

	cout << "Calcul" << endl;
	double temps=0;
	/*
	 * On parcourt la liste des clients par ordre de commande : Du dernier à l'avant dernier
	 */
	while (!listeAscClient.empty()) {
		cout << "Iteration " << endl;
		cCurrent = (Client*) listeAscClient.back();
		commTemp = cCurrent->derniereCommande();
		if (commTemp != NULL) {

			double ttemp = t.back();
			if (commTemp->getDate()+d->distanceClient(cCurrent) > ttemp) {

				temps = ttemp - 2*d->distanceClient(cCurrent);

				if (sol[temps] == NULL)
					sol[temps] = new vector<Action*>();

				sol[temps]->push_back(new Action((Client*)0, cCurrent));
				t.push_back(temps);

				for (itComm = cCurrent->getCommande()->begin(); itComm != cCurrent->getCommande()->end(); itComm++) {
					commTemp = (Commande*) (*itComm);
					sol[temps]->push_back(new Action(cCurrent, commTemp));
				}
				double retour = ttemp - d->distanceClient(cCurrent);

				if (sol[retour] == NULL)
					sol[retour] = new vector<Action*>();

				sol[retour]->insert(sol[retour]->begin(), new Action(cCurrent,(Client*)0));
				//sol[retour]->push_back(new Action(cCurrent,(Client*)0));
				t.push_back(temps);

			}
			else {
				temps = cCurrent->premiereCommande()->getDate() ;

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

Modification* Solution::deplacerAction(Action* ac, double tAct, double tDema)
{
	Modification* m = NULL;
	if (sol[tAct])
	{
		vector<Action* >* pVecSol = sol[tAct];
		//vector<Action *>::iterator pos = find(pVecSol->begin(), pVecSol->end(), ac) - pVecSol->begin();
		pVecSol->erase(std::remove(pVecSol->begin(), pVecSol->end(), ac), pVecSol->end());
		if (sol[tDema] == NULL)
			sol[tDema] = new vector<Action*>();
		sol[tDema]->push_back(ac);
		m = new Modification(ac, tAct, tDema, 0);
	}
	return m;
}

/*
 * A IMPLEMENTER : gestion de la capacité
 */
vector<Modification*> Solution::detectMerge()
{
	vector<Modification*> vMod;

	double t = 0;
	double tNext;
	double min = std::numeric_limits<double>::infinity();
	map<double, vector<Action*>* >::iterator itSol;
	map<double, vector<Action*>* >::iterator itNextSol;

	vector<Action*>* pVecAct = NULL;
	vector<Action*>* pNextVecAct = NULL;
	Action* pAct;
	Action* pNextAct;
	Action* pActTemp;

	vector<Action*>::iterator itVActTemp;

	for(itSol = sol.begin(); itSol != sol.end(); itSol++)
	{
		t = (*itSol).first;
		pVecAct = (*itSol).second;
		for (itVActTemp = pVecAct->begin(); itVActTemp != pVecAct->end(); itVActTemp++)
		{
			pActTemp = (*itVActTemp);
			if (pActTemp->getType() == Donnees::DEPOT)
			{
				if ((pActTemp->getCommande()->getDate() - t) <= min)
					min = (pActTemp->getCommande()->getDate() - t);
			}
		}
		itNextSol = itSol;
		itNextSol++;
		if (itNextSol != sol.end())
		{
			pNextVecAct = (*itNextSol).second;
			tNext = (*itNextSol).first;
		}
		if (pNextVecAct != NULL)
		{
			pAct = pVecAct->back();
			pNextAct = pNextVecAct->front();
			/*
			 * On vérifie que les deux actions sont bien des déplacements
			 * puis on regarde si la destination de la première action est l'origine de la seconde action
			 * S'il existe une route entre les deux clients
			 * On stocke la modification et on passe à la suite
			 */
			if (pAct->getType() == Donnees::DEPLACEMENT && pNextAct->getType() == Donnees::DEPLACEMENT)
			{
				if (pAct->getEnd() == pNextAct->getStart())
				{
					if ( (d->distanceClient(pAct->getStart(),pNextAct->getEnd()) < std::numeric_limits<double>::infinity()))
					{
						double gain = d->distanceClient(pAct->getStart(),pNextAct->getEnd()) - (d->distanceClient(pAct->getStart()))+(d->distanceClient(pNextAct->getEnd()));
						std::cout << "Gain: "<< gain << endl;
						if (gain < min)
							vMod.push_back(new Modification(pAct, pNextAct, gain, t, tNext));
					}
				}
			}
		}
	}
	return vMod;
}

vector<Modification*> Solution::detectMove()
{
	vector<Modification*> vMod;
	map<double, vector<Action*>* >::iterator itSol;
	map<double, vector<Action*>* >::iterator itSolBis;

	vector<Action*>::iterator itAct;
	Action* aTemp;

	vector<double> listeDebut;
	vector<double>::iterator itListeDebut;
	double tDepart = 0 ;
	double tLastDepart = 0 ;
	double tLastArrivee = 0;
	double t;
	bool bChangement = false;


	//Client* cCurrent;
	for(itSol = sol.begin(); itSol != sol.end(); itSol++)
	{
		t = (*itSol).first;
		for(itAct = ((*itSol).second)->begin(); itAct != ((*itSol).second)->end(); itAct++)
		{
			aTemp = (*itAct);
			if (aTemp->getType() == Donnees::DEPLACEMENT)
			{
				tLastArrivee = t;
				tLastDepart = tDepart;
				tDepart = t-d->distanceClient(aTemp->getStart(),aTemp->getEnd());

				//cCurrent = aTemp->getEnd();
				bChangement = true;
			}
		}
		listeDebut.push_back(t);
		if (bChangement)
		{
			for(itListeDebut = listeDebut.begin(); itListeDebut != listeDebut.end(); itListeDebut++)
			{
				double temp = (*itListeDebut);
				double gain = 0;
				for(itSolBis = sol.begin(); itSolBis != sol.end(); itSolBis++)
				{
					double ttemp = (*itSolBis).first;
					if (ttemp >= tLastDepart)
					{
						for(itAct = ((*itSolBis).second)->begin(); itAct != ((*itSolBis).second)->end(); itAct++)
						{
							aTemp = (*itAct);
							if (aTemp->getType() == Donnees::DEPOT)
							{
								gain += aTemp->getStart()->getKStockage()*(aTemp->getCommande()->getDate()-(ttemp-temp));
							}
						}
					}
					vMod.push_back(new Modification(tLastDepart, tLastArrivee, temp, gain));
				}
			}
			bChangement = false;
		}
	}
	return vMod;

}

vector<Modification*> Solution::listeVoisins()
{

	vector<Modification*> mTotal;
	vector<Modification*> merge = detectMerge();
	vector<Modification*> move = detectMove();
	vector<Modification *>::iterator itVModif;

	for (itVModif = merge.begin(); itVModif != merge.end(); itVModif++)
		mTotal.push_back((*itVModif));
	for (itVModif = move.begin(); itVModif != move.end(); itVModif++)
	{
		//	mTotal.push_back((*itVModif));
		//(*itVModif)->toFlux();
	}
	return mTotal;

	//return detectMerge();
}
Solution* Solution::applyModification(Modification* m)
{
	Solution* s = new Solution(this);


	if (m->getT() == Calcul::FUSION)
	{
		std::cout << "Depart :" << m->getDepart() << " | Arrive :" << m->getArrive() << endl;

		//(Action* ac1, Action* ac2, double g) : gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(-1),tArrive(-1) {
		Action* acA = m->getAct1();
		Action* acB = m->getAct2();
		Client* A;
		Client* B;
		vector<Client*> pathClients = d->getPath(acA->getStart(), acB->getEnd());
		vector<Client*>::iterator itClients;
		vector<Client*>::iterator itClientSuivant;

		map<double, vector<Action*>* >::iterator itMSol;
		map<double, vector<Action*>* > mapTemp;
		vector<Action*>::iterator itAction;
		double delay = 0;
		/*		double g =  (d->distanceClient(acA->getStart()) + d->distanceClient(acB->getEnd())) - d->distanceClient(acA->getStart(),acB->getEnd());
		double tTemp;
		 */

		/*
 		(s->sol[m->getArrive()])->insert((s->sol[m->getArrive()])->begin()+1 ,new Action(acA->getStart(),acB->getEnd()));
		s->sol.erase(s->sol.find((m->getDepart())));
		(s->sol[(m->getDepart() + d->distanceClient(m->getAct2()->getEnd()))])->erase((s->sol[(m->getDepart() + d->distanceClient(m->getAct2()->getEnd()))])->begin());
*/
		vector<Action*>* vAct = (s->sol[m->getDepart()]);
		vAct->erase(find(vAct->begin(), vAct->end(), m->getAct1()));
		vAct = (s->sol[m->getArrive()]);
		vAct->erase(find(vAct->begin(), vAct->end(), m->getAct2()));
		for (itMSol = s->sol.begin(); itMSol != s->sol.end(); itMSol++)
		{
				if ((*itMSol).first <= m->getDepart())
				{
					mapTemp[(*itMSol).first]=(*itMSol).second;
				}

		}

		for (itClients = pathClients.begin(); itClients != pathClients.end(); ++itClients)
		{
			std::cout << (*itClients)->getNom() << " -> ";
			itClientSuivant = itClients;
			++itClientSuivant;
			vAct = (mapTemp[m->getDepart()+delay]);
			if (vAct == NULL)
				vAct = new vector<Action*>();
			if (itClientSuivant != pathClients.end())
			{
				A = (*itClients);
				B = (*itClientSuivant);
				vAct->push_back(new Action(A,B));
				delay += d->distanceClient(A,B);
			}

		}
		std::cout << endl;
		for (itMSol = mapTemp.begin(); itMSol != mapTemp.end(); itMSol++)
		{

			if ((*itMSol).second != NULL)
			{

				for (itAction = (*itMSol).second->begin(); itAction != (*itMSol).second->end(); ++itAction)
				{
					std::cout << (*itMSol).first << " : ";
					if (m->getAct1() == (*itAction) ||  (*itAction) == m->getAct2())
						std::cout << " /!\\ " ;
					std::cout << (*itAction)->toString() << endl;
				}
			}
		}

		//s->sol = mapTemp;
		s->computeDifference();

	}
	else if(m->getT() == Calcul::MOVE)
	{
		double diff = m->getArrive()-m->getDepart();
		map<double, vector<Action*>* > mapTemp;
		map<double, vector<Action*>* >::iterator itMSol;
		for (itMSol = s->sol.begin(); itMSol != s->sol.end(); itMSol++)
		{
			double t = (*itMSol).first;
			vector<Action*>* temp = (*itMSol).second;

			if (t < m->getFinal())
			{
				mapTemp[t-diff] = temp;
			}
			else if (t == m->getFinal() && t < m->getFinal()+diff)
			{
				mapTemp[t] = temp;
			}
			else
			{
				if (t < m->getArrive())
				{
					mapTemp[t-diff] = temp;

				}
				else
				{
					mapTemp[t-diff] = temp;
				}
			}
		}

		map<double, vector<Action*>* >::iterator itMSolNext;
		map<double, vector<Action*>* > mapTempBis;
		double decal = 0;
		bool bAdd = false;
		for (itMSol = mapTemp.begin(); itMSol != mapTemp.end(); itMSol++)
		{
			itMSolNext = itMSol;
			itMSolNext++;
			double t = (*itMSol).first;

			vector<Action*>* temp = (*itMSol).second;
			vector<Action*>* modif = new vector<Action*>();
			double tNext = (*itMSolNext).first;
			vector<Action*>* tempNext = (*itMSolNext).second;

			if (itMSolNext != mapTemp.end())
			{

				if (temp != NULL)
				{
					if (temp->back()->getType() == Donnees::DEPLACEMENT)
					{
						if (temp->back()->getEnd() != tempNext->front()->getStart())
						{
							temp->back()->setEnd(NULL);
							modif->push_back(new Action(NULL, tempNext->front()->getStart()));
							bAdd = true;

						}
					}
				}
			}
			mapTempBis[t+decal] = temp;
			if (bAdd)
			{
				decal += d->distanceClient(tempNext->front()->getStart());
				mapTempBis[t+decal] = modif;
				bAdd = false;
			}
		}

		s->sol = mapTempBis;
		//s->computeDifference();
		std::cout << "#########################################" << endl;
		std::cout << s << endl;

		std::cout << "Coût total de la solution: " << s->getValeur() << endl;

		std::cout << "#########################################" << endl;
	}
	return s;
}

bool Solution::check()
{
	bool b=true;
	map<Commande*, bool> commandesEffectuees;
	map<Commande*, bool>::iterator itCommandesEffectuees;
	vector<Commande*>::iterator itCommandes;
	vector<Client*>::iterator itClient;

	map<double, vector<Action*>* >::iterator itSolution;

	vector<Action*>::iterator itAction;
	Client* currentClient = NULL;
	double temps;
	vector<Action*>* listeActions;
	Action* action;
	Commande* comm;

	std::cout << "Creation de la liste des commandes à faire" << endl;
	for (itClient = d->getListeClient().begin(); itClient != d->getListeClient().end(); ++itClient)
	{
		if ((*itClient) != NULL)
		{
			for (itCommandes = ((*itClient)->getCommande())->begin(); itCommandes != ((*itClient)->getCommande())->end(); ++itCommandes)
			{
				commandesEffectuees[(*itCommandes)] = false;
			}
		}
	}
	std::cout << "Liste créée" << endl;
	for (itSolution = sol.begin(); itSolution != sol.end(); ++itSolution)
	{
		temps = (*itSolution).first;
		listeActions = (*itSolution).second;
		for (itAction = listeActions->begin(); itAction != listeActions->end(); ++itAction)
		{
			action = (*itAction);
			if (action->getType() == Donnees::DEPLACEMENT)
			{
				if (action->getStart() == currentClient)
				{
					currentClient = action->getEnd();
				}
				else
				{
					b=false;
					break;
				}
			}
			if (action->getType() == Donnees::DEPOT)
			{
				if (action->getStart() == currentClient)
				{
					comm = action->getCommande();
					if (comm->getDate() >= temps)
					{
						commandesEffectuees[comm] = true;
					}
					else
					{
						b=false;
						break;
					}
				}
				else
				{
					b=false;
					break;
				}
			}
		}
	}
	bool c;
	for (itCommandesEffectuees = commandesEffectuees.begin(); itCommandesEffectuees != commandesEffectuees.end(); ++itCommandesEffectuees)
	{
		c = (*itCommandesEffectuees).second;
		if (!c)
		{
			b=false;
			break;
		}
	}
	return b;
}

}
