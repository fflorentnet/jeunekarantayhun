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
enum TypeModification { DEPLACEMENT, FUSION };
class Modification {
private:
	TypeModification t;
	Action* act1;
	Action* act2;
	Action* actFinal;
	int tDepart;
	int tArrive;
	int gain;
public:
	Modification(Action* ac, int tDep, int tArr);
	Modification(Action* ac1, Action* ac2, Action* acF, int tDep);

	virtual ~Modification();
	bool operator==(Modification &m);

};

} /* namespace Calcul */

#endif /* MODIFICATION_H_ */
