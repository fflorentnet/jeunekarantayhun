/*
 * Tabou.h
 *
 *  Created on: 2 juin 2014
 *      Author: florent
 */

#ifndef TABOU_H_
#define TABOU_H_
#include "Solution.h"
namespace Calcul {

class Tabou {
private:
	int it;
public:
	Tabou(int i);
	virtual ~Tabou();
	Solution* execute(Solution *solInitiale);
};

} /* namespace Calcul */

#endif /* TABOU_H_ */