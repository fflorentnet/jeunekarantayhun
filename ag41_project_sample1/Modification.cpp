/*
 * Modification.cpp
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#include "Modification.h"

namespace Calcul {

Modification::Modification(Action* ac, int tDep, int tArr): act(ac), tDepart(tDep), tArrive(tArr) {
	// TODO Auto-generated constructor stub

}

Modification::~Modification() {
	// TODO Auto-generated destructor stub
}

bool Modification::operator==(Modification &m)
{
	bool b = false;
	if (tDepart == m.tDepart && tArrive == m.tArrive)
		if (act == m.act)
			b = true;
	return b;
}
} /* namespace Calcul */
