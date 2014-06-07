/*
 * Tabou.cpp
 *
 *  Created on: 2 juin 2014
 *      Author: florent
 */

#include "Tabou.h"
#include <deque>
#include <algorithm>
#define MAXTABULISTSIZE 5
namespace Calcul {

Tabou::Tabou(float i): it(i) {
	// TODO Auto-generated constructor stub

}

Tabou::~Tabou() {
	// TODO Auto-generated destructor stub
}
Solution* Tabou::execute(Solution *solInitiale)
{
	Solution* s = solInitiale;
	Solution* sBest = s;

	float i = 0;

	vector<Modification *>::iterator itVModif;
	deque<Modification *> tabuList(50);

	Modification* bestCandidate;
	Modification* temp;
	Solution* sCandidate;
	float max;
	while(i != this->it)
	{
		std::cout << "Iteration " << i << endl;
		max = 0;
		vector<Modification *> candidateList = sBest->listeVoisins();
		if (candidateList.size() > 1)
		{
			for (itVModif= candidateList.begin(); itVModif != candidateList.end(); itVModif++)
			{
				temp = (*itVModif);
				if (find(tabuList.begin(), tabuList.end(), temp) == tabuList.end())
				{
					if (temp->getGain() > max)
					{
						max = temp->getGain();
						bestCandidate = temp;

						std::cout << "bestCandidate found" << endl;
					}
				}
			}
		}
		else
		{
			bestCandidate = candidateList.back();
		}
		sCandidate = sBest->applyModification(bestCandidate);

		if (sCandidate->getValeur() < sBest->getValeur())
		{
			tabuList.push_back(bestCandidate);
			sBest = sCandidate;
			if (tabuList.size() > MAXTABULISTSIZE)
			{
				tabuList.pop_front();
			}
		}
		i++;
	}
	std::cout << "Fin de l'algorithme tabou" << endl;
	return sBest;

}

} /* namespace Calcul */
