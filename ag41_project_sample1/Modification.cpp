/*
 * Modification.cpp
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#include "Modification.h"

namespace Calcul {

Modification::Modification(Action* ac, float tDep, float tArr, float g): gain(g), act1(ac), act2(NULL),  t(DEPLACEMENT), tDepart(tDep), tArrive(tArr), tFinal(-1) {

}
Modification::Modification(Action* ac1, Action* ac2, float g, float t, float tNext) : gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(t),tArrive(tNext), tFinal(-1) {

}
Modification::Modification(float tD, float tA, float tF, float g):  gain(g), act1(NULL), act2(NULL),  t(MOVE), tDepart(tD), tArrive(tA), tFinal(tF)
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

float Modification::getGain() {
	return gain;
}

void Modification::setGain(float gain) {
	this->gain = gain;
}

TypeModification Modification::getT()  {
	return t;
}

void Modification::setT(TypeModification t) {
	this->t = t;
}

float Modification::getArrive()  {
	return tArrive;
}

void Modification::setArrive(float arrive) {
	tArrive = arrive;
}

float Modification::getDepart()  {
	return tDepart;
}

void Modification::setDepart(float depart) {
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
float Modification::getFinal() {
	return tFinal;
}

void Modification::setFinal(float final) {
	tFinal = final;
}
} /* namespace Calcul */


