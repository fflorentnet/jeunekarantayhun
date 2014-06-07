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
enum TypeModification { DEPLACEMENT, FUSION, MOVE };
class Modification {
private:
	TypeModification t;
	Action* act1;
	Action* act2;
	float tDepart;
	float tArrive;
	float tFinal;
	float gain;
public:
	Modification(Action* ac, float tDep, float tArr, float g);
	Modification(Action* ac1, Action* ac2, float g, float t, float tNext);
	Modification(float tD, float tA, float tF, float g);

	virtual ~Modification();
	bool operator==(Modification &m);
	 Action*& getAct1() ;
	void setAct1( Action*& act1);
	 Action*& getAct2() ;
	void setAct2( Action*& act2);
	float getGain() ;
	void setGain(float gain);
	TypeModification getT() ;
	void setT(TypeModification t);
	float getArrive() ;
	void setArrive(float arrive);
	float getDepart() ;
	void setDepart(float depart);
	float getFinal();
	void setFinal(float final);
};

} /* namespace Calcul */

#endif /* MODIFICATION_H_ */
