/*
 * Modification.h
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#ifndef MODIFICATION_H_
#define MODIFICATION_H_
#include "Action.h"
using namespace Donnees;
namespace Calcul {
class Modification {
private:
	Action* act;
	int tDepart;
	int tArrive;
public:
	Modification(Action* ac, int tDep, int tArr);
	virtual ~Modification();
	bool operator==(Modification &m);

};

} /* namespace Calcul */

#endif /* MODIFICATION_H_ */
