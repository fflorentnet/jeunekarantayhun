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
#include <limits>

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
	int MAXTABULISTSIZE = 10;
	double max;
	bool b = false;
	bool bSol = false;
	while(i != this->it)
	{
		bSol = false;
		//std::cout << "######################################" << endl;
		//std::cout << "sBest:" << endl << sBest << endl;
		//std::cout << "######################################" << endl;
		bestCandidate = NULL;
		//std::cout << "Iteration " << i << endl;
		max = std::numeric_limits<double>::infinity();
		max = - max;
		candidateList = s->listeVoisins();
		if (candidateList.size() > 1)
		{
			for (itVModif= candidateList.begin(); itVModif != candidateList.end(); itVModif++)
			{
				temp = (*itVModif);
				b = false;
				//temp->toFlux();
				for (itTabu = tabuList.begin(); itTabu != tabuList.end(); ++itTabu)
				{
					rechercheTemp = (*itTabu);
					if (rechercheTemp != NULL)
					{
						if (temp->getHash() == rechercheTemp->getHash())
						{
							//std::cout << "Les modifications sont identiques" << endl;
							b = true;
							break;
						}
					}

				}
				if (temp->getGain() > max && !b)
				{
					max = temp->getGain();
					bestCandidate = temp;
					////std::cout << "bestCandidate found" << endl;
					bestCandidate->toFlux();
				}

			}
			bSol = true;
		}
		else
		{
			bestCandidate = candidateList.back();
			//bSol = true;
		}
		if (bSol)
		{
			////std::cout << "On applique la meilleure modification possible" << endl;
			////std::cout << "Best candidat:" << endl;

			if (bestCandidate != NULL)
			{
				//	sCandidate = new Solution(s);
				bestCandidate->toFlux();

				s->applyModification(bestCandidate);
				//s = sCandidate;
				//tabuList.push_back(bestCandidate);
				////std::cout << "La modification a été appliquée" << endl;
				std::cout << endl << "sCandidate : " << s->getValeur() << " | sBest : " << sBest->getValeur() << endl;

				/*//std::cout << "######################################" << endl;
				 */
				std::cout << "sCandidate:" << endl << s << endl;

				//std::cout << "######################################" << endl;
				//std::cout << "sBest:" << endl << sBest << endl;
				//std::cout << "######################################" << endl;*/


				if (s->getValeur() <= sBest->getValeur())
				{
					//std::cout << "bestSolution found" << endl;
					tabuList.push_back(bestCandidate);
					sBest = new Solution(s);
					if (tabuList.size() >= MAXTABULISTSIZE)
					{
						tabuList.pop_front();
					}
				}
			}
			else
			{
				std::cout << "Nombre d'iteration: " << i << endl;
				return sBest;
			}
		}
		i++;
	}

	std::cout << "Nombre d'iteration: " << i << endl;
	std::cout << "Fin de l'algorithme tabou" << endl;
	return sBest;

}

} /* namespace Calcul */
