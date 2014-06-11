/*
 * Tabou.cpp
 *
 *  Created on: 2 juin 2014
 *      Author: florent
 */

#include "Tabou.h"
#include <deque>
#include <algorithm>
#include <cmath>
#define MAXTABULISTSIZE 15
namespace Calcul {

Tabou::Tabou(double i): it(i) {
	// TODO Auto-generated constructor stub

}

Tabou::~Tabou() {
	// TODO Auto-generated destructor stub
}
Solution* Tabou::execute(Solution *solInitiale)
{
	Solution* s = solInitiale;
	Solution* sBest = s;

	double i = 0;

	vector<Modification *>::iterator itVModif;
	deque<Modification *> tabuList(0);
	deque<Modification *>::iterator itTabu;
	vector<Modification *> candidateList;

	Modification* bestCandidate;
	Modification* temp;
	Modification* rechercheTemp;
	Solution* sCandidate;
	float max;
	bool b = false;
	bool bSol = false;
	while(i != this->it)
	{
		bSol = false;
		std::cout << "######################################" << endl;
		std::cout << "sBest:" << endl << sBest << endl;
		std::cout << "######################################" << endl;

		std::cout << "Iteration " << i << endl;
		max = 0;

		candidateList = sBest->listeVoisins();
		if (candidateList.size() >= 1)
		{
			for (itVModif= candidateList.begin(); itVModif != candidateList.end(); itVModif++)
			{
				temp = (*itVModif);
				b = false;
				temp->toFlux();
				for (itTabu = tabuList.begin(); itTabu != tabuList.end(); ++itTabu)
				{
					rechercheTemp = (*itTabu);
					std::cout << "Comparaison des modifications" << endl;

					if ((*temp) == rechercheTemp)
					{
						std::cout << "Les modifications sont identiques" << endl;
						b = true;
						break;
					}
				}
				if (abs(temp->getGain()) >= max && !b)
				{
					max = temp->getGain();
					bestCandidate = temp;
					std::cout << "bestCandidate found" << endl;
				}
			}
			bSol = true;
		}
		else
		{
			bestCandidate = candidateList.back();
			bSol = true;
		}
		if (bSol)
		{
			std::cout << "On applique la meilleure modification posible" << endl;
			sCandidate = new Solution(sBest);
			sCandidate->applyModification(bestCandidate);
			std::cout << "La modification a été appliquée" << endl;
			std::cout << endl << "sCandidate : " << sCandidate->getValeur() << " | sBest : " << sBest->getValeur() << endl;

			std::cout << "######################################" << endl;
			std::cout << "sCandidate:" << endl << sCandidate << endl;

			std::cout << "######################################" << endl;
			std::cout << "sBest:" << endl << sBest << endl;
			std::cout << "######################################" << endl;


			if (sCandidate->getValeur() <= sBest->getValeur())
			{
				std::cout << "bestSolution found" << endl;
				tabuList.push_back(bestCandidate);
				sBest = sCandidate;
				if (tabuList.size() > MAXTABULISTSIZE)
				{
					tabuList.pop_front();
				}
			}
		}
		i++;
	}
	std::cout << "Fin de l'algorithme tabou" << endl;
	return sBest;

}

} /* namespace Calcul */
