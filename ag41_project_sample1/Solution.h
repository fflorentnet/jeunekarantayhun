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
#include "Client.h"
#include "Action.h"
#include "Data.h"
using namespace std;

class Solution {
private:
	Data* d;
	map<int, vector<Action*>* > sol;
public:
	Solution(Data* dat);
	virtual ~Solution();
	friend ostream& operator<< (ostream& flux, Solution& s);
	int generate();
};

#endif /* SOLUTION_H_ */
