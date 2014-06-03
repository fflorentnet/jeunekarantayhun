/*
 * Tabou.cpp
 *
 *  Created on: 2 juin 2014
 *      Author: florent
 */

#include "Tabou.h"
#include <deque>
#include <algorithm>
#define MAXTABULISTSIZE 500
namespace Calcul {

Tabou::Tabou(int i): it(i) {
	// TODO Auto-generated constructor stub

}

Tabou::~Tabou() {
	// TODO Auto-generated destructor stub
}
/*
 *    s ← s0
2:   sBest ← s
3:   tabuList ← null
4:   while (not stoppingCondition())
5:      candidateList ← null
6:      for(sCandidate in sNeighborhood)
7:           if(not containsTabuElements(sCandidate, tabuList))
8:                 candidateList ← candidateList + sCandidate
9:           end
10:     end
11:     sCandidate ← LocateBestCandidate(candidateList)
12:     if(fitness(sCandidate) > fitness(sBest))
13:          tabuList ← featureDifferences(sCandidate, sBest)
14:          sBest ← sCandidate
15:          while(size(tabuList) > maxTabuListSize)
16:               ExpireFeatures(tabuList)
17:          end
18:     end
19:  end
20:  return(sBest)
 */
Solution* Tabou::execute(Solution *solInitiale)
{
	Solution* s = solInitiale;
	Solution* sBest = s;

	int i = 0;

	vector<Modification *>::iterator itVModif;
	deque<Modification *> tabuList(50);

	Modification* bestCandidate;
	Modification* temp;
	Solution* sCandidate;
	int max;
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

		if (sCandidate < sBest)
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
