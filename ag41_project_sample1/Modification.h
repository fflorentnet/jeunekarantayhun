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
	Modification(Action* ac1, Action* ac2, int g, int t, int tNext);

	virtual ~Modification();
	bool operator==(Modification &m);
	 Action*& getAct1() ;
	void setAct1( Action*& act1);
	 Action*& getAct2() ;
	void setAct2( Action*& act2);
	int getGain() ;
	void setGain(int gain);
	TypeModification getT() ;
	void setT(TypeModification t);
	int getArrive() ;
	void setArrive(int arrive);
	int getDepart() ;
	void setDepart(int depart);
};

} /* namespace Calcul */

#endif /* MODIFICATION_H_ */
