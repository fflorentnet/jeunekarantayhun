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
	std::cout << "Recopie d'une solution" << endl;
	d = s->getData();
	sol = map<double,vector<Action*>* >();
	map<double, vector<Action*>* >::iterator itMSol;
	vector<Action*>::iterator itActions;
	vector<Action*>* vActions;
	Action* pAct;
	double t=0;
	for (itMSol = s->sol.begin(); itMSol != s->sol.end(); ++itMSol)
	{
		t = (*itMSol).first;
		vActions = (*itMSol).second;
		sol[t] = new vector<Action*>();
		for (itActions = vActions->begin(); itActions != vActions->end(); ++itActions)
		{
			if (pAct != NULL)
			{
				pAct = new Action((*itActions));
				sol[t]->push_back(pAct);
			}
		}
	}
	std::cout << "Fin de recopie" << endl;
}
Solution::Solution(Solution& s)
{
	d = s.getData();
	sol = map<double,vector<Action*>* >(s.sol);
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
	map<double, vector<Action*>* >::iterator itMSol;
	map<double, vector<Action*>* > mapTemp;
	vector<Action*>::iterator itAction;

	for (itMSol = s.sol.begin(); itMSol != s.sol.end(); itMSol++)
	{
		if ((*itMSol).second != NULL)
		{
			for (itAction = (*itMSol).second->begin(); itAction != (*itMSol).second->end(); ++itAction)
			{
				flux << (*itMSol).first << " : ";
				flux << (*itAction)->toString() << endl;
			}
		}
	}

	return flux;
}
ostream& operator<<(ostream& flux, Solution* s) {
	map<double, vector<Action*>* >::iterator itMSol;
	map<double, vector<Action*>* > mapTemp;
	vector<Action*>::iterator itAction;

	for (itMSol = s->sol.begin(); itMSol != s->sol.end(); itMSol++)
	{
		if ((*itMSol).second != NULL)
		{
			for (itAction = (*itMSol).second->begin(); itAction != (*itMSol).second->end(); ++itAction)
			{
				flux << (*itMSol).first << " : ";
				flux << (*itAction)->toString() << endl;
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

				ttemp = getData()->getKTransport() * getData()->distanceClient(itAction->getStart(), itAction->getEnd());
				tempDep += ttemp;

			}
			else if (itAction->getType() == Donnees::DEPOT)
			{
				Client* itCli = itAction->getStart();
				Commande* itCom = itAction->getCommande();

				double t = itCli->getKStockage() * abs(temps - itCom->getDate());

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

	std::cout << "Recopie des données" << endl;
	std::cout << "Nombre de clients : " << listeAscClient.size() << endl;

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

	std::cout << "Nombre de clients ayant commandé au moins un produit :"
			<< listeAscClient.size() << endl;

	std::cout << "Tri des elements..." << endl;
	sort(listeAscClient.begin(), listeAscClient.end(), compareClient);
	std::cout << "Tri terminé" << endl;
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

	std::cout << "Calcul" << endl;
	double temps=0;
	/*
	 * On parcourt la liste des clients par ordre de commande : Du dernier à l'avant dernier
	 */
	while (!listeAscClient.empty()) {
		std::cout << "Iteration " << endl;
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
	std::cout << "Fin du calcul" << endl;
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

vector<Modification*> Solution::detectMerge()
{
	vector<Modification*> L;
	double nbrProduit = 0;
	double nbrProduitTheorique = 0;

	map<double, vector<Action*>*>::iterator itActionA;
	double Ta;
	vector<Action*>* La;
	Action* A;

	map<double, vector<Action*>*>::iterator itActionB;
	double Tb;
	vector<Action*>* Lb;
	Action* B;

	map<double, vector<Action*>*>::iterator itActionC;
	vector<Action*>* Lc;
	vector<Action*>::iterator itActionLc;
	Action* C;

	for (itActionA = sol.begin(); itActionA != sol.end(); ++itActionA)
	{
		Ta = (*itActionA).first;
		La = (*itActionA).second;
		if (!La->empty())
		{
			A = La->back();
			if (A != NULL)
			{

				if (A->getType() == Donnees::DEPOT)
				{
					nbrProduit++;

				}
				else if (A->getType() == Donnees::DEPLACEMENT)
				{

					if (A->getStart() == NULL)
						nbrProduit = 0;

					itActionB = itActionA;
					++itActionB;
					if (itActionB != sol.end())
					{
						Tb = (*itActionB).first;
						Lb = (*itActionB).second;
						if (!Lb->empty())
						{
							B = Lb->front();
							if (B != NULL)
							{

								if (B->getType() == Donnees::DEPLACEMENT)
								{

									if (A->getEnd() == 	B->getStart())
									{
										for (itActionC = itActionB; itActionC != sol.end(); ++itActionC)
										{
											Lc = (*itActionC).second;
											for (itActionLc = Lc->begin(); itActionLc != Lc->end(); ++itActionLc)
											{
												C = (*itActionLc);
												if (C->getType() == Donnees::DEPOT)
												{
													nbrProduitTheorique++;
												}
												else if(C->getType() == Donnees::DEPLACEMENT)
												{
													if (C->getEnd() == NULL)
														break;
												}
											}
										}

										if (nbrProduitTheorique <= d->getCapacite())
										{
											double gain = (d->distanceClient(A->getStart(),A->getEnd()) + d->distanceClient(B->getStart(),B->getEnd())) - d->distanceClient(A->getStart(),B->getEnd());
											L.push_back(new Modification(A,B,gain,Ta,Tb));
											//std::cout << "gain:" << gain << endl;
											nbrProduitTheorique = 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	std::cout << "Fin de la liste des fusions possibles" << endl;


	return L;
}

vector<Modification*> Solution::detectMove()
{
	vector<Modification*> vMod;
	map<double, vector<Action*>*>::iterator itSol;
	map<double, vector<Action*>*>::iterator itSolBis;

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
	for (itSol = sol.begin(); itSol != sol.end(); ++itSol)
	{
		t = (*itSol).first;
		//std::cout << "|- detectMove : t : " << t << endl;

		// Construit une liste contenant tous les temps départs d'action de déplacement
		for(itAct = ((*itSol).second)->begin(); itAct != ((*itSol).second)->end(); itAct++)
		{
			aTemp = (*itAct);
			if (aTemp->getType() == Donnees::DEPLACEMENT)
			{
				tLastArrivee = t;
				//std::cout << "|- detectMove : tLastArrivee : " << tLastArrivee << endl;
				tLastDepart = tDepart;
				//std::cout << "|- detectMove : tLastDepart : " << tLastDepart << endl;
				tDepart = t;
				//std::cout << "|- detectMove : tDepart : " << tDepart << endl;
				listeDebut.push_back(t);

				//cCurrent = aTemp->getEnd();
				bChangement = true;
			}
		}

		if (bChangement)
		{
			for(itListeDebut = listeDebut.begin(); itListeDebut != listeDebut.end(); itListeDebut++)
			{
				double temp = (*itListeDebut);
				std::cout << "|- detectMove : temp : " << temp << endl;
				double gain = 0;
				for (itSolBis = sol.begin(); itSolBis != sol.end(); ++itSolBis)
				{
					double ttemp = (*itSolBis).first;
					std::cout << "|- detectMove : ttemp : " << ttemp << endl;
					if (ttemp >= tLastDepart && ttemp < tLastArrivee)
					{
						std::cout << "|- detectMove : ttemp >= tLastDepart && ttemp < tLastArrivee " << endl;
						for(itAct = ((*itSolBis).second)->begin(); itAct != ((*itSolBis).second)->end(); itAct++)
						{
							aTemp = (*itAct);
							if (aTemp->getType() == Donnees::DEPOT)
							{
								double A = (aTemp->getCommande()->getDate() - ttemp) * aTemp->getStart()->getKStockage();
								double B = (aTemp->getCommande()->getDate() - temp) * aTemp->getStart()->getKStockage();
								//gain += aTemp->getStart()->getKStockage()*(aTemp->getCommande()->getDate()-temp);
								gain += B-A;
								std::cout << "|- detectMove : if(Action == Dépot), gain += " << gain << endl;
							}
						}
					}
					vMod.push_back(new Modification(tLastDepart, tLastArrivee, temp, gain));
					std::cout << "|----> detectMove : NEW MODIFICATION" << endl;
					std::cout << "|----> tLastDepart : " << tLastDepart << endl;
					std::cout << "|----> tLastArrivee : " << tLastArrivee << endl;
					std::cout << "|----> temp : " << temp << endl;
					std::cout << "|----> gainMove : " << gain << endl;
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
		mTotal.push_back((*itVModif));
		//(*itVModif)->toFlux();
	}
	return mTotal;

	//return detectMerge();
}
void Solution::applyModification(Modification* m)
{
	//Solution* s = new Solution(this);

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
		//double delay = - d->distanceClient(acA->getStart(), acA->getEnd());
		double delay = 0;


		(sol[m->getDepart()])->pop_back();


		(sol[m->getArrive()])->erase(sol[m->getArrive()]->begin());
		if (sol[m->getArrive()]->size() == 0)
			sol.erase(m->getArrive());
		for (itMSol = sol.begin(); itMSol != sol.end(); itMSol++)
		{
			if ((*itMSol).first <= m->getDepart())
			{
				mapTemp[(*itMSol).first]=(*itMSol).second;
			}

		}
		//std::cout << "XxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxX" << endl;
		for (itClients = pathClients.begin(); itClients != pathClients.end(); ++itClients)
		{
			if ((*itClients) != NULL)
			{
				//std::cout << (*itClients)->getNom() << " -> " << endl;
				itClientSuivant = itClients;
				itClientSuivant++;
				if (mapTemp[m->getDepart()+delay] == NULL)
					mapTemp[m->getDepart()+delay] = new vector<Action*>();
				if (itClientSuivant != pathClients.end())
				{
					A = (*itClients);
					B = (*itClientSuivant);
					if (mapTemp[m->getDepart()+delay] == NULL)
						mapTemp[m->getDepart()+delay] = new vector<Action*>();
					//std::cout << A->getNom() << "&" << B->getNom() << "/" << delay << endl;
					mapTemp[m->getDepart()+delay]->push_back(new Action(A,B));
					delay += d->distanceClient(A,B);
					//(mapTemp[m->getDepart()+delay]) = vAct;
				}
			}
		}
		//std::cout << "XxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxX" << endl;

		delay = delay - (m->getArrive()-m->getDepart());
		for (itMSol = sol.begin(); itMSol != sol.end(); itMSol++)
		{
			double temp = (*itMSol).first;
			if (temp >= m->getArrive())
			{
				mapTemp[temp+delay] = (*itMSol).second;
			}
		}

		double min = std::numeric_limits<double>::infinity();
		for (itMSol = mapTemp.begin(); itMSol != mapTemp.end(); itMSol++)
		{
			double time = (*itMSol).first;
			if ((*itMSol).second != NULL)
			{
				for (itAction = (*itMSol).second->begin(); itAction != (*itMSol).second->end(); ++itAction)
				{
					acA = (*itAction);
					if (acA->getType() == Donnees::DEPOT)
					{
						double temp = acA->getCommande()->getDate()-time;
						if (temp <= min)
							min = temp;
					}
				}
			}
		}
		if (min != 0 && min != std::numeric_limits<double>::infinity())
		{
			std::cout << "Minimum à soustraire:" << min << endl;

			for (itMSol = mapTemp.begin(); itMSol != mapTemp.end(); itMSol++)
			{
				//double time = (*itMSol).first;
				if ((*itMSol).second != NULL)
				{
					for (itAction = (*itMSol).second->begin(); itAction != (*itMSol).second->end(); ++itAction)
					{
						acA = (*itAction);
						if (acA->getType() == Donnees::DEPOT)
						{
							acA = new Action(acA);
							acA->getCommande()->setDate(acA->getCommande()->getDate()-min);
							(*itMSol).second->erase(itAction);
							(*itMSol).second->insert(itAction, acA);
						}
					}
				}
			}
		}
		sol = mapTemp;

		//computeDifference();

	}
	else if(m->getT() == Calcul::MOVE)
	{
		// Déplacement d'Action
		std::cout << "|- Application d'un déplacement de livraison" << endl;
		std::cout << "|- m->getDepart() : " << m->getDepart() << endl;
		std::cout << "|- m->getArrive() : " << m->getArrive() << endl;
		std::cout << "|- m->getFinal() : " << m->getFinal() << endl;
		std::cout << "|- m->getGain() : " << m->getGain() << endl;

		map<double, vector<Action*>* > mapTemp;
		map<double, vector<Action*>* >::iterator itMSol;

		for (itMSol = sol.begin(); itMSol != sol.end(); itMSol++)
		{
			double t = (*itMSol).first;
			vector<Action*>* temp = (*itMSol).second;

			std::cout << "|- FOR-1 : t : " << t << endl;

			// Deux possibilités en fonction du sens du déplacement
			if(m->getDepart() <= m->getFinal()) {
				// Déplacement en avancant dans le temps
				std::cout << "|- 1 - Déplacement en avancant dans le temps " << endl;

				if (t < m->getDepart()) {
					// Pas de mouvement
					std::cout << "|- 1 - t < depart -> on ne bouge rien " << endl;
					mapTemp[t] = temp;
				}
				else if (t >= m->getDepart() && t <= m->getArrive()) {
					// Avancement des Action à déplacer
					std::cout << "|- 1 - t >= m->getDepart() && t <= m->getArrive() " << endl;
					mapTemp[t + (m->getFinal() - m->getDepart())] = temp;
				}
				else if (t > m->getArrive()) {
					if(t >= m->getFinal() && t <= (m->getFinal() + m->getArrive() - m->getDepart())) {
						// Recul des Action qui ont été touchées par le déplacement
						std::cout << "|- 1 - t >= m->getFinal() && t <= (m->getFinal() + m->getArrive() - m->getDepart()) " << endl;
						mapTemp[t - (m->getFinal() - m->getDepart())] = temp;
					}
					else {
						// Pas de mouvement
						mapTemp[t] = temp;
					}
				}
			}
			else if(m->getDepart() > m->getFinal()) {
				// Déplacement en reculant dans le temps
				std::cout << "|- 1 - Déplacement en reculant dans le temps " << endl;

				if (t < m->getFinal()) {
					// Pas de mouvement
					std::cout << "|- 1 - t < m->getFinal() -> on ne bouge rien " << endl;
					mapTemp[t] = temp;
				}
				else if (t >= m->getFinal() && t <= (m->getFinal() + m->getArrive() - m->getDepart())) {
					// Avancement des Action qui ont été touchées par le déplacement
					std::cout << "|- 1 - t >= m->getFinal() && t <= (m->getFinal() + m->getArrive() - m->getDepart()) " << endl;
					mapTemp[t + (m->getDepart() - m->getFinal())] = temp;
				}
				else if (t > (m->getFinal() + m->getArrive() - m->getDepart())) {
					if(t >= m->getDepart() && t <= m->getArrive()) {
						// Recul des Action à déplacer
						std::cout << "|- 1 - t >= m->getDepart() && t <= m->getArrive() " << endl;
						mapTemp[t - (m->getDepart() - m->getFinal())] = temp;
					}
					else {
						// Pas de mouvement
						mapTemp[t] = temp;
					}
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
			double tNext = (*itMSolNext).first;

			vector<Action*>* temp = (*itMSol).second;
			vector<Action*>* tempNext = (*itMSolNext).second;
			vector<Action*>* modif = new vector<Action*>();
			if (itMSolNext != mapTemp.end())
			{
				if (temp != NULL)
				{
					if (temp->size() != 0)
					{
						if (temp->back() != NULL)
						{
							if (temp->back()->getType() == Donnees::DEPLACEMENT)
							{
								if (temp->back()->getEnd() != tempNext->front()->getStart())
								{
									temp->back()->setEnd(NULL);
									modif->push_back(new Action(NULL, tempNext->front()->getStart()));
								}
							}
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

		sol = mapTempBis;
		computeDifference();
		std::cout << "#########################################" << endl;
		std::cout << this << endl;

		std::cout << "Coût total de la solution: " << getValeur() << endl;

		std::cout << "#########################################" << endl;
	}
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
				if ((*itCommandes) != NULL)
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
