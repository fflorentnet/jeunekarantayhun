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
	int tDepart;
	int tArrive;
	int gain;
public:
	Modification(Action* ac, int tDep, int tArr, int g);
	Modification(Action* ac1, Action* ac2, int g);

	virtual ~Modification();
	bool operator==(Modification &m);
	const Action*& getAct1() const;
	void setAct1(const Action*& act1);
	const Action*& getAct2() const;
	void setAct2(const Action*& act2);
	int getGain() const;
	void setGain(int gain);
	TypeModification getT() const;
	void setT(TypeModification t);
	int getArrive() const;
	void setArrive(int arrive);
	int getDepart() const;
	void setDepart(int depart);
};

} /* namespace Calcul */

#endif /* MODIFICATION_H_ */
