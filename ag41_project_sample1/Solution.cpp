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
		sol = map<float, vector<Action*>* >(s->sol);
	}
	Data* Solution::getData()
	{
		return d;
	}
	float Solution::computeDifference()
	{
		map<float, vector<Action*>* >::iterator itMap;
		vector<Action*>* vTemp;
		vector<Action*>::iterator itAction;
		Action* aTemp;
		float date=0;
		float min = 1500000;

		for (itMap = sol.begin() ; itMap != sol.end() ; itMap++)
		{
			vTemp = (*itMap).second;
			date = (*itMap).first;
			for (itAction = vTemp->begin(); itAction != vTemp->end(); itAction++)
			{
				aTemp = (*itAction);
				float ttemp = 0;
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
		map<float, vector<Action*>* > tempSol;
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
		map<float, vector<Action*>* >::iterator itMap;
		vector<Action*>* vTemp;
		vector<Action*>::iterator itAction;
		Action* aTemp;
		float date=0;

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
					float ttemp = 0;
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
			map<float, vector<Action*>* >::iterator itMap;
			vector<Action*>* vTemp;
			vector<Action*>::iterator itAction;
			Action* aTemp;
			float date=0;

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
						float ttemp = 0;
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
		float d1 = co1->getDate();
		float d2 = co2->getDate();

		return (d1 < d2);
	}
	float Solution::getValeur() {

		// Calcul des coûts de déplacement:
		float tempDep = 0;
		float tempStock = 0;

		vector<Action*> *veListeAction;
		Action* itAction;

		map<float, vector<Action*>* >::iterator itSol;
		vector<Action*>::iterator itAct;

		for (itSol=sol.begin(); itSol != sol.end(); itSol++)
		{
			float temps = (*itSol).first;
			veListeAction = (*itSol).second;
			for (itAct = veListeAction->begin(); itAct != veListeAction->end(); itAct++)
			{
				itAction = (*itAct);
				if (itAction->getType() == Donnees::DEPLACEMENT)
				{
					float ttemp = 0;
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
					float tprim = temps;
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
	float Solution::generate() {
		vector<Client*> listeAscClient = d->getListeClient();

		vector<float> t;

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
		float temp = commLast->getDate();
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
		float temps=0;
		/*
		 * On parcourt la liste des clients par ordre de commande : Du dernier à l'avant dernier
		 */
		while (!listeAscClient.empty()) {
			cout << "Iteration " << endl;
			cCurrent = (Client*) listeAscClient.back();
			commTemp = cCurrent->derniereCommande();
			if (commTemp != NULL) {

				float ttemp = t.back();
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
					float retour = ttemp - d->distanceClient(cCurrent);

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

	Modification* Solution::deplacerAction(Action* ac, float tAct, float tDema)
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

		float t = 0;
		float tNext;
		float min = 100000;
		map<float, vector<Action*>* >::iterator itSol;
		map<float, vector<Action*>* >::iterator itNextSol;

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
				 * 		On stocke la modification et on passe à la suite
				 */
				if (pAct->getType() == Donnees::DEPLACEMENT && pNextAct->getType() == Donnees::DEPLACEMENT)
				{
					if (pAct->getEnd() == pNextAct->getStart())
					{
						if ( (d->distanceClient(pAct->getStart(),pNextAct->getEnd()) != -1))
						{
							float gain = d->distanceClient(pAct->getStart(),pNextAct->getEnd()) - (d->distanceClient(pAct->getStart()))+(d->distanceClient(pNextAct->getEnd()));
							std::cout << "Gain: "<< gain << endl;
							if (gain <= min)
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
		map<float, vector<Action*>* >::iterator itSol;
		map<float, vector<Action*>* >::iterator itSolBis;

		vector<Action*>::iterator itAct;
		Action* aTemp;

		vector<float> listeDebut;
		vector<float>::iterator itListeDebut;
		float tDepart = 0 ;
		float tLastDepart = 0 ;
		float tLastArrivee = 0;
		float t;
		bool bChangement = false;


		//Client* cCurrent;
		for(itSol = sol.begin(); itSol != sol.end(); itSol++)
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
					float temp = (*itListeDebut);
					//std::cout << "|- detectMove : temp : " << temp << endl;
					float gain = 0;
					for(itSolBis = sol.begin(); itSolBis != sol.end(); itSolBis++)
					{
						float ttemp = (*itSolBis).first;
						//std::cout << "|- detectMove : ttemp : " << ttemp << endl;
						if (ttemp >= tLastDepart && ttemp < tLastArrivee)
						{
							//std::cout << "|- detectMove : ttemp >= tLastDepart && ttemp < tLastArrivee " << endl;
							for(itAct = ((*itSolBis).second)->begin(); itAct != ((*itSolBis).second)->end(); itAct++)
							{
								aTemp = (*itAct);
								if (aTemp->getType() == Donnees::DEPOT)
								{
									gain += aTemp->getStart()->getKStockage()*(aTemp->getCommande()->getDate()-(ttemp-temp));
									//std::cout << "|- detectMove : if(Action == Dépot), gain += " << gain << endl;
								}
							}
						}
						vMod.push_back(new Modification(tLastDepart, tLastArrivee, temp, gain));
						//std::cout << "|----> detectMove : NEW MODIFICATION" << endl;
						//std::cout << "|----> tLastDepart : " << tLastDepart << endl;
						//std::cout << "|----> tLastArrivee : " << tLastArrivee << endl;
						//std::cout << "|----> temp : " << temp << endl;
						//std::cout << "|----> gain : " << gain << endl;
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

		//std::cout << "|- LISTE VOISINS" << endl;

		for (itVModif = merge.begin(); itVModif != merge.end(); itVModif++) {
			mTotal.push_back((*itVModif));
			//std::cout << "|-> MERGE:" << endl;
			//std::cout << "|----> getDepart : " << (*itVModif)->getDepart() << endl;
			//std::cout << "|----> getArrive : " << (*itVModif)->getArrive() << endl;
			//std::cout << "|----> getFinal : " << (*itVModif)->getFinal() << endl;
			//std::cout << "|----> getGain : " << (*itVModif)->getGain() << endl;
		}

		for (itVModif = move.begin(); itVModif != move.end(); itVModif++) {
			mTotal.push_back((*itVModif));
			//std::cout << "|-> MOVE:" << endl;
			//std::cout << "|----> getDepart : " << (*itVModif)->getDepart() << endl;
			//std::cout << "|----> getArrive : " << (*itVModif)->getArrive() << endl;
			//std::cout << "|----> getFinal : " << (*itVModif)->getFinal() << endl;
			//std::cout << "|----> getGain : " << (*itVModif)->getGain() << endl;
		}

		return mTotal;
	}
	Solution* Solution::applyModification(Modification* m)
	{
		Solution* s = new Solution(this);


		if (m->getT() == Calcul::FUSION)
		{

			std::cout << "Application d'une fusion de deplacement"  << endl;

			//(Action* ac1, Action* ac2, float g) : gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(-1),tArrive(-1) {
			Action* acA = m->getAct1();
			Action* acB = m->getAct2();
			std::cout  << acB->getEnd()->getNom() << endl;
			(s->sol[m->getArrive()])->insert((s->sol[m->getArrive()])->begin()+1 ,new Action(acA->getStart(),acB->getEnd()));


			std::cout << "tDepart:" << (m->getDepart() + d->distanceClient(m->getAct2()->getEnd())) << endl;


			s->sol.erase(s->sol.find((m->getDepart())));


			(s->sol[(m->getDepart() + d->distanceClient(m->getAct2()->getEnd()))])->erase((s->sol[(m->getDepart() + d->distanceClient(m->getAct2()->getEnd()))])->begin());
			float g =  (d->distanceClient(acA->getStart()) + d->distanceClient(acB->getEnd())) - d->distanceClient(acA->getStart(),acB->getEnd());
			float tTemp;

			map<float, vector<Action*>* >::iterator itMSol;
			map<float, vector<Action*>* > mapTemp;


			for (itMSol = s->sol.begin(); itMSol != s->sol.end(); itMSol++)
			{
				if ((*itMSol).first < m->getArrive())
				{
					tTemp = (*itMSol).first + g;
				}
				else
					tTemp = (*itMSol).first;
				mapTemp[tTemp] = (*itMSol).second;
			}
			s->sol = mapTemp;

			s->computeDifference();

			std::cout << s << endl;
		}
		else if(m->getT() == Calcul::MOVE)
		{
			// Déplacement d'Action
			std::cout << "|- Application d'un déplacement de livraison"  << endl;
			std::cout << "|- m->getDepart() : " << m->getDepart() << endl;
			std::cout << "|- m->getArrive() : " << m->getArrive() << endl;
			std::cout << "|- m->getFinal() : " << m->getFinal() << endl;
			std::cout << "|- m->getGain() : " << m->getGain() << endl;

			map<float, vector<Action*>* > mapTemp;
			map<float, vector<Action*>* >::iterator itMSol;

			for (itMSol = s->sol.begin(); itMSol != s->sol.end(); itMSol++)
			{
				float t = (*itMSol).first;
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

			map<float, vector<Action*>* >::iterator itMSolNext;
			map<float, vector<Action*>* > mapTempBis;
			float decal = 0;
			bool bAdd = false;
			for (itMSol = mapTemp.begin(); itMSol != mapTemp.end(); itMSol++)
			{
				itMSolNext = itMSol;
				itMSolNext++;
				float t = (*itMSol).first;
				float tNext = (*itMSolNext).first;

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

			s->sol = mapTempBis;
			s->computeDifference();
			std::cout << "#########################################" << endl;
			std::cout << s << endl;

			std::cout << "Coût total de la solution: " << s->getValeur() << endl;

			std::cout << "#########################################" << endl;
		}
		return s;
	}

}
