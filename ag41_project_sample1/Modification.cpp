/*
 * Modification.cpp
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#include "Modification.h"
#include <sstream>
#include <string>
#include <algorithm>

namespace Calcul {

/*Modification::Modification( Action* ac, double tDep, double tArr, double g):  gain(g), act1(ac), act2(NULL),  t(DEPLACEMENT), tDepart(tDep), tArrive(tArr) {
}*/

Modification::Modification( Action* ac1, Action* ac2, double g, double t, double tNext) :  gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(t),tArrive(tNext) {

}

Modification::Modification( double tD,  double tA, double g, Action* ac1, Action* ac2):   gain(g), act1(ac1), act2(ac2),  t(SWAP), tDepart(tD), tArrive(tA)
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

double Modification::getGain() {
	return gain;
}

void Modification::setGain(double gain) {
	this->gain = gain;
}

TypeModification Modification::getT()  {
	return t;
}

void Modification::setT(TypeModification t) {
	this->t = t;
}

double Modification::getArrive()  {
	return tArrive;
}

void Modification::setArrive(double arrive) {
	tArrive = arrive;
}

double Modification::getDepart()  {
	return tDepart;
}

void Modification::setDepart(double depart) {
	tDepart = depart;
}

/*
 * 	TypeModification t;
	Action* act1;
	Action* act2;
	double tDepart;
	double tArrive;
	double tFinal;
	float gain;
 */
bool Modification::operator==(Modification &m)
		{
	bool b = false;
	if (t == m.t && tDepart == m.tDepart && tArrive == m.tArrive)
		if (act1 == m.act1 && act2 == m.act2 && gain == m.gain)
			b = true;
	return b;
		}
bool Modification::operator==(Modification* m)
		{
	bool b = false;
	if (m != NULL)
	{
		if (t == m->t && gain == m->gain)
		{
			if (t == DEPLACEMENT)
			{
				//gain(g), act1(ac), act2(NULL),  t(DEPLACEMENT), tDepart(tDep), tArrive(tArr), tFinal(-1) {
				if (tDepart == m->tDepart && tArrive == m->tArrive)
				{
					if ((*act1) == m->act1)
					{
						b = true;
					}
				}

			}
			else if (t == FUSION)
			{
				//gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(t),tArrive(tNext), tFinal(-1) {
				if (act1 == NULL || act2 == NULL)
				{

					if (m->act1 == NULL && act1 == NULL)
					{
						if ((*act2) == m->act2)
						{
							b = true;
						}
					}
					else if (m->act2 == NULL && act2 == NULL)
					{
						if ((*act1) == m->act1)
						{
							b = true;
						}
					}
				}
				else
				{

					if ((*act1) == m->act1 && (*act2) == m->act2 && tDepart == m->tDepart && tArrive == m->tArrive)
					{
						b = true;
					}
				}


			}
			else if (t == SWAP)
			{

			}
		}
		/*
		 *
gain(g), act1(ac1), act2(ac2), t(FUSION), tDepart(t),tArrive(tNext), tFinal(-1) {
gain(g), act1(NULL), act2(NULL),  t(MOVE), tDepart(tD), tArrive(tA), tFinal(tF)

		 */

		/*if (t == m->t && tDepart == m->tDepart && tFinal == m->tFinal && tArrive == m->tArrive)
			if (act1 == (m->act1) && act2 == (m->act2) && gain == m->gain)
				b = true;*/
	}
	return b;
		}
/*double Modification::getFinal() {
	return tFinal;
}

void Modification::setFinal(double final) {
	tFinal = final;
}*/

void Modification::toFlux()
{
	std::cout << "################" << endl;
	if (t == Calcul::SWAP)
	{
		std::cout << "SWAP | gain: " << gain << endl << "-> Depart:" << tDepart << endl << "<- Arrivée:" << tArrive << endl;
	}
	else
	{
		std::cout << "FUSION | gain: " << gain << endl;
		std::cout << "-> Depart:" << tDepart << endl;
		std::cout<< "<- Arrivée:" << tArrive << endl;
		std::cout<< "Action 1" << act1->toString() << endl;
		std::cout<< "Action 2" << act2->toString() << endl;
		Action* bis = new Action(act1->getStart(), act2->getEnd(), Donnees::Data::getInstance().getPath(act1->getStart(), act2->getEnd()));
		std::cout << "Action finale: " << bis->toString() << endl;
	}
	std::cout << "################" << endl;
}

bool compareInt (int i,int j) { return (i<j); }

string Modification::getHash()
{
	string s = "";
	std::ostringstream ss;
	string cclientA;
	string cclientB;
	int clientA;
	int clientB;

	if (act1->getStart() == NULL)
		cclientA = "Fournisseur 0";
	else
		cclientA = act1->getStart()->getNom();
	if (act2->getEnd() == NULL)
		cclientB = "Fournisseur 0";
	else
		cclientB = act2->getEnd()->getNom();


	cclientA.erase(remove_if(cclientA.begin(), cclientA.end(), ::isalpha), cclientA.end());
	clientA = atoi (cclientA.c_str());

	cclientB.erase(remove_if(cclientB.begin(), cclientB.end(), ::isalpha), cclientB.end());
	clientB = atoi (cclientB.c_str());

	vector<int> pInt(0);
	pInt.push_back(clientA);
	pInt.push_back(clientB);
	if (t == Calcul::SWAP)
	{
		sort (pInt.begin(), pInt.end(), compareInt);
	//	std::cout  << "1-" << endl << act1->toString() << endl << "2-" << endl << act2->toString() << endl;
		s += "S?";
		ss  << pInt.front();
		//pInt.pop_back();
		ss << "#" << pInt.back();
		s += ss.str();
	}
	else if (t == Calcul::FUSION)
	{
		s += "F?";
		ss << pInt.front() << "#" << pInt.back() << ";" << tDepart;
		s += ss.str();
	}
//	ss << endl << gain;
//	s += "#"+ss.str();
	std::cout << s << endl;
	return s;

}

} /* namespace Calcul */


