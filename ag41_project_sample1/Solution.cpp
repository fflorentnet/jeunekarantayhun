/*
 * Solution.cpp
 *
 *  Created on: May 17, 2014
 *      Author: florent
 */

#include "Solution.h"
#include <algorithm>
#include <limits>
#include <cmath>
namespace Calcul
{
Solution::Solution() {
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
				ttemp = date - aTemp->distance();
				if (ttemp < min)
				{
					min = ttemp;
				}
			}
		}
	}
	min = min + Donnees::Data::getInstance().distanceClient((*sol.begin()).second->front()->getEnd());
	map<double, vector<Action*>* > tempSol;
	for (itMap = sol.begin() ; itMap != sol.end() ; itMap++)
	{
		vTemp = (*itMap).second;
		date = (*itMap).first;
		//vector<Action* >* veActions = new vector();
		tempSol[date-min] = vTemp;
		for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
		{
			if ((*itAction)->getType() == Donnees::DEPOT)
				(*itAction)->getCommande()->setDate((*itAction)->getCommande()->getDate() - min);
		}

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
				if ((*itAction) != NULL)
				{
					flux << (*itMSol).first << " : ";
					flux << (*itAction)->toString();
					if ((*itAction)->getType() == Donnees::DEPLACEMENT)
						flux << " (distance :" << (*itAction)->distance() << ")" << endl;
					else
						flux << endl;
				}
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
			if (itAction != NULL)
			{
				if (itAction->getType() == Donnees::DEPLACEMENT)
				{
					tempDep += Donnees::Data::getInstance().getKTransport() * itAction->distance();
				}
				else if (itAction->getType() == Donnees::DEPOT)
				{
					Client* itCli = itAction->getStart();
					Commande* itCom = itAction->getCommande();

					double t = itCli->getKStockage() * abs(temps - itCom->getDate());
					tempStock += t;
				}
			}
		}
	}
	std::cout << "Coût de deplacement: " << tempDep << endl;
	std::cout << "Coût de stockage: " << tempStock << endl;

	return (tempDep+tempStock);
}
double Solution::generate() {
	vector<Client*> listeAscClient = Donnees::Data::getInstance().getListeClient();

	vector<double> t;

	std::cout << "Recopie des données" << endl;
	std::cout << "Nombre de clients : " << listeAscClient.size() << endl;

	vector<Commande*>::iterator itComm;

	vector<Client*> pathNull(0);

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
	double temp = commLast->getDate()-Donnees::Data::getInstance().distanceClient(cLast);
	t.push_back(temp);

	if (sol[temp] == NULL)
		sol[temp] = new vector<Action*>(0);
	sol[temp]->push_back(new Action((Client*)0, cLast,pathNull));

	if (sol[temp+Donnees::Data::getInstance().distanceClient(cLast)] == NULL)
		sol[temp+Donnees::Data::getInstance().distanceClient(cLast)] = new vector<Action*>(0);

	for (itComm = cLast->getCommande()->begin();itComm != cLast->getCommande()->end(); itComm++) {
		commTemp = (Commande*) (*itComm);
		sol[temp+Donnees::Data::getInstance().distanceClient(cLast)]->push_back(new Action(cLast, commTemp));

	}

	sol[temp+Donnees::Data::getInstance().distanceClient(cLast)]->push_back(new Action(cLast, (Client*)0,pathNull));

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

			double tempsDernierClientVisite = t.back();
			//Si on a le temps de visiter le client, puis d'aller au fournisseur
			if (commTemp->getDate()+Donnees::Data::getInstance().distanceClient(cCurrent) >= tempsDernierClientVisite) {

				temps = tempsDernierClientVisite - 2*Donnees::Data::getInstance().distanceClient(cCurrent);

				if (sol[temps] == NULL)
					sol[temps] = new vector<Action*>(0);
				sol[temps]->push_back(new Action((Client*)0, cCurrent, pathNull));
				t.push_back(temps);
				double retour = temps+Donnees::Data::getInstance().distanceClient(cCurrent);

				if (sol[retour] == NULL)
					sol[retour] = new vector<Action*>(0);

				for (itComm = cCurrent->getCommande()->begin(); itComm != cCurrent->getCommande()->end(); itComm++) {
					commTemp = (Commande*) (*itComm);
					sol[retour]->push_back(new Action(cCurrent, commTemp));
				}

				sol[retour]->push_back(new Action(cCurrent,(Client*)0, pathNull));
				t.push_back(temps);

			}
			else {
				temps = cCurrent->premiereCommande()->getDate();

				if (sol[temps] == NULL)
					sol[temps] = new vector<Action*>(0);

				sol[temps]->push_back(new Action((Client*)0, cCurrent,pathNull));

				for (itComm = cCurrent->getCommande()->begin();	itComm != cCurrent->getCommande()->end(); itComm++) {
					commTemp = cCurrent->premiereCommande();
					sol[temps]->push_back(new Action(cCurrent, commTemp));
				}

				t.push_back(temps);
			}
		}
		listeAscClient.pop_back();
	}
	map<double, vector<Action*>* >::iterator itMap;
	map<double, vector<Action*>* >::iterator itMapNext;
	vector<Action*> *itVec;
	vector<Action*> *itVecNext;
	Action* A;
	Action* B;
	pathNull.push_back((Client*)NULL);
	map<double,vector<Action*>* > tempSol;
	for (itMap = sol.begin(); itMap != sol.end(); ++itMap)
	{
		itMapNext = itMap;
		++itMapNext;

		temps = (*itMap).first;
		itVec = (*itMap).second;

		if (itMapNext != sol.end())
		{
			itVecNext = (*itMapNext).second;

			tempSol[temps] = new vector<Action*>();
			B = itVecNext->front();

			while(!itVec->empty())
			{
				A = itVec->front();
				if (A->getType() == B->getType() && A->getType() == Donnees::DEPLACEMENT)
				{
					if (A->getEnd() == B->getStart())
					{
						itVecNext->erase(itVecNext->begin());
						tempSol[temps]->push_back(new Action(A->getStart(),B->getEnd(),pathNull));
					}
				}
				else
				{
					tempSol[temps]->push_back(A);
				}
				itVec->erase(itVec->begin());
			}
		}
		else
		{
			tempSol[temps] = new vector<Action*>();
			while(!itVec->empty())
			{
				A = itVec->front();
				tempSol[temps]->push_back(A);
				itVec->erase(itVec->begin());
			}
		}
	}

	sol = tempSol;
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

	map<double, vector<Action*>*>::iterator itActionA;
	double Ta;
	vector<Action*>* La;
	Action* A;

	map<double, vector<Action*>*>::iterator itActionB;
	double Tb;
	vector<Action*>* Lb;
	Action* B;

	double gain=0;
	for (itActionA = sol.begin(); itActionA != sol.end(); ++itActionA)
	{
		gain = 0;
		Ta = (*itActionA).first;
		La = (*itActionA).second;
		if (!La->empty())
		{
			A = La->back();

			if (A->getType() == Donnees::DEPLACEMENT)
			{

				gain = A->distance() - Donnees::Data::getInstance().distanceClient(A->getStart(),A->getEnd());
				Tb = Ta + A->distance();

				if (gain != 0)
					L.push_back(new Modification(A,A,gain,Ta,Tb));

			}
		}
		//std::cout << "gain:" << gain << endl;
	}
	std::cout << "Fin de la liste des fusions possibles" << endl;
	vector<Modification*> tempListe;

	/*
	 * On retire les Modification qui ne respectent pas la contrainte de capacité
	 */
	Modification* M;
	Action* C;
	vector<Action*>::iterator itLb;
	while(!L.empty())
	{
		M = L.back();
		A = M->getAct1();
		B = M->getAct2();
		double nbrProduitPreB = 0;
		double nbrProduitPostB = 0;
		bool bPasse = false;
		bool fournisseurAtteint=false;
		/*map<double, vector<Action*>*>::iterator itActionB;
		double Tb;
		vector<Action*>* Lb;*/
		for (itActionB = sol.begin(); itActionB != sol.end() ; ++itActionB)
		{
			Lb = (*itActionB).second;
			for (itLb = Lb->begin(); itLb != Lb->end(); ++itLb)
			{
				if (fournisseurAtteint)
					break;
				C = (*itLb);
				if (C == B)
				{
					bPasse=true;
				}
				if (C != A && C != B)
				{
					if (C->getType() == Donnees::DEPLACEMENT)
					{
						if (C->contientFournisseur())
						{
							if (bPasse)
							{

								std::cout << nbrProduitPreB << " | C:" << C->toString() << endl;
								fournisseurAtteint=true;
							}
							else
							{
								nbrProduitPreB = 0;
							}
						}
					}
					else
					{
						if (bPasse)
						{
							nbrProduitPostB++;
						}
						else
						{
							nbrProduitPreB++;
						}
					}
				}
			}
		}

		if (nbrProduitPreB+nbrProduitPostB <= Donnees::Data::getInstance().getCapacite())
		{
			tempListe.push_back(M);
			//std::cout << "Modification acceptée :" << endl;
			//M->toFlux();
		}


		L.pop_back();
	}
	return tempListe;
}

vector<Modification*> Solution::detectMove()
{
	vector<Modification*> vMod;
	map<double, vector<Action*>*>::iterator itSol;
	map<double, vector<Action*>*>::iterator itSolBis;

	vector<Action*>* pvActions;
	vector<Action*>::iterator itActions;
	Action* A;

	double temps;
	double tInit;
	double tFinal;

	for (itSol = sol.begin(); itSol != sol.end(); ++itSol)
	{
		temps = (*itSol).first;
		pvActions = new vector<Action*>();
		pvActions->assign((*itSol).second->begin(), (*itSol).second->end());

		for (itSolBis = sol.begin(); itSolBis != sol.end(); ++itSolBis)
		{

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
		(*itVModif)->toFlux();
	}
	return mTotal;

	//return detectMerge();
}
void Solution::applyModification(Modification* m)
{

	if (m->getT() == Calcul::FUSION)
	{
		std::cout << "Depart :" << m->getDepart() << " | Arrive :" << m->getArrive() << endl;

		Action* acA = m->getAct1();
		Action* acB = m->getAct2();

		vector<Client*> pathClients = Donnees::Data::getInstance().getPath(acA->getStart(), acB->getEnd());
		vector<Client*>::iterator itClients;
		vector<Client*>::iterator itClientSuivant;
		map<double, vector<Action*>* >::iterator itMSol;
		map<double, vector<Action*>* > mapTemp;
		vector<Action*>::iterator itAction;

		double delay = - (m->getArrive()-m->getDepart()) + Donnees::Data::getInstance().distanceClient(acA->getStart(), acB->getEnd());

		std::cout << "delay | " << delay << endl;

		(sol[m->getDepart()])->pop_back();
		(sol[m->getDepart()])->push_back(new Action(acA->getStart(), acB->getEnd(), Donnees::Data::getInstance().getPath(acA->getStart(), acB->getEnd())));


		for (itMSol = sol.begin(); itMSol != sol.end(); itMSol++)
		{
			if ((*itMSol).first <= m->getDepart())
			{
				mapTemp[(*itMSol).first]=(*itMSol).second;
			}
		}
		mapTemp[m->getDepart()] = sol[m->getDepart()];
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
		//	std::cout << "|____ Min:" << min << endl;
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
	for (itClient = Donnees::Data::getInstance().getListeClient().begin(); itClient != Donnees::Data::getInstance().getListeClient().end(); ++itClient)
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
