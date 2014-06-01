/*
 * Modification.cpp
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#include "Modification.h"

namespace Calcul {

Modification::Modification(Action* ac, int tDep, int tArr): act(ac), tDepart(tDep), tArrive(tArr) {
}

Modification::~Modification() {
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
