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
		map<double, vector<Action*>* > sol;
	public:
		Solution();
		Solution(Solution* s);
		Solution(Solution& s);
		virtual ~Solution();
		bool operator<(Solution& s);

		friend ostream& operator<< (ostream& flux, Solution& s);
		friend ostream& operator<< (ostream& flux, Solution* s);

		double generate();
		double getValeur();
		Data* getData();
		double computeDifference();
		vector<Modification*> detectMove();
		vector<Modification*> detectFusion();
		vector<Modification*> detectJonction();
		vector<Modification*> detectSplit();
		vector<Modification*> listeVoisins();
		bool check();
		void applyModification(Modification* m);
	};
}
#endif /* SOLUTION_H_ */
