/*
 * Solution.h
 *
 *  Created on: May 17, 2014
 *      Author: florent
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_
#include <map>
#include <utility>
#include <vector>
#include "Data.h"
#include "Modification.h"
using namespace Donnees;

namespace Calcul
{
	class Solution {
	private:
		Data* d;
		map<float, vector<Action*>* > sol;
	public:
		Solution(Data* dat);
		Solution(Solution *s);
		virtual ~Solution();
		bool operator<(Solution& s);
		friend ostream& operator<< (ostream& flux, Solution& s);
		friend ostream& operator<< (ostream& flux, Solution* s);

		float generate();
		float getValeur();
		Data* getData();
		float computeDifference();
		Modification* deplacerAction(Action* ac, float tAct, float tDema);
		vector<Modification*> detectMove();
		vector<Modification*> detectMerge();
		vector<Modification*> listeVoisins();
		Solution* applyModification(Modification* m);
	};
}
#endif /* SOLUTION_H_ */
