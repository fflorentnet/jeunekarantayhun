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
using namespace Donnees;

namespace Calcul
{
	class Solution {
	private:
		Data* d;
		map<int, vector<Action*>* > sol;
	public:
		Solution(Data* dat);
		Solution(Solution &s);
		virtual ~Solution();
		bool operator<(Solution& s);
		friend ostream& operator<< (ostream& flux, Solution& s);
		int generate();
		int getValeur();
		Data* getData();
		int computeDifference();
		Modification* deplacerAction(Action* ac, int tAct, int tDema);
	};
}
#endif /* SOLUTION_H_ */
