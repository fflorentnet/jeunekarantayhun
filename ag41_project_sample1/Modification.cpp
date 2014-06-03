/*
 * Modification.cpp
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#include "Modification.h"

namespace Calcul {

Modification::Modification(Action* ac, int tDep, int tArr, int g): gain(g), act1(ac), act2(NULL),  t(DEPLACEMENT), tDepart(tDep), tArrive(tArr) {
	// TODO Auto-generated constructor stub

}
Modification::Modification(Action* ac1, Action* ac2, int g) : gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(-1),tArrive(-1) {

}

Modification::~Modification() {
	// TODO Auto-generated destructor stub
}

const Action*& Modification::getAct1() const {
	return act1;
}

void Modification::setAct1(const Action*& act1) {
	this->act1 = act1;
}

const Action*& Modification::getAct2() const {
	return act2;
}

void Modification::setAct2(const Action*& act2) {
	this->act2 = act2;
}

int Modification::getGain() const {
	return gain;
}

void Modification::setGain(int gain) {
	this->gain = gain;
}

TypeModification Modification::getT() const {
	return t;
}

void Modification::setT(TypeModification t) {
	this->t = t;
}

int Modification::getArrive() const {
	return tArrive;
}

void Modification::setArrive(int arrive) {
	tArrive = arrive;
}

int Modification::getDepart() const {
	return tDepart;
}

void Modification::setDepart(int depart) {
	tDepart = depart;
}

bool Modification::operator==(Modification &m)
{
	bool b = false;
	if (tDepart == m.tDepart && tArrive == m.tArrive)
		if (act1 == m.act1)
			b = true;
	return b;
}
} /* namespace Calcul */
