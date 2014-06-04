/*
 * Modification.cpp
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#include "Modification.h"

namespace Calcul {

Modification::Modification(Action* ac, int tDep, int tArr, int g): gain(g), act1(ac), act2(NULL),  t(DEPLACEMENT), tDepart(tDep), tArrive(tArr), tFinal(-1) {

}
Modification::Modification(Action* ac1, Action* ac2, int g, int t, int tNext) : gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(t),tArrive(tNext), tFinal(-1) {

}
Modification::Modification(int tD, int tA, int tF, int g):  gain(g), act1(NULL), act2(NULL),  t(MOVE), tDepart(tD), tArrive(tA), tFinal(tF)
{

}
Modification::~Modification() {
	// TODO Auto-generated destructor stub
}

 Action*& Modification::getAct1() {
	return act1;
}

void Modification::setAct1(Action*& act1) {
	this->act1 = act1;
}

 Action*& Modification::getAct2() {
	return act2;
}

void Modification::setAct2(Action*& act2) {
	this->act2 = act2;
}

int Modification::getGain() {
	return gain;
}

void Modification::setGain(int gain) {
	this->gain = gain;
}

TypeModification Modification::getT()  {
	return t;
}

void Modification::setT(TypeModification t) {
	this->t = t;
}

int Modification::getArrive()  {
	return tArrive;
}

void Modification::setArrive(int arrive) {
	tArrive = arrive;
}

int Modification::getDepart()  {
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
int Modification::getFinal() {
	return tFinal;
}

void Modification::setFinal(int final) {
	tFinal = final;
}
} /* namespace Calcul */


