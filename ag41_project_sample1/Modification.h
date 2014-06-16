/*
 * Modification.h
 *
 *  Created on: 27 mai 2014
 *      Author: florent
 */

#ifndef MODIFICATION_H_
#define MODIFICATION_H_
#include "Action.h"
#include "Data.h"
using namespace Donnees;
namespace Calcul {
enum TypeModification { DEPLACEMENT, FUSION, MOVE };
class Modification {
private:
	TypeModification t;
	Action* act1;
	Action* act2;
	double tDepart;
	double tArrive;
	double tFinal;
	float gain;
	Data* d;
public:
	Modification(Data* dd, Action* ac, double tDep, double tArr, float g);
	Modification(Data* dd, Action* ac1, Action* ac2, float g, double t, double tNext);
	Modification(Data* dd, double tD, double tA, double tF, float g);

	virtual ~Modification();
	bool operator==(Modification &m);
	bool operator==(Modification* m);
	 Action*& getAct1() ;

	void setAct1( Action*& act1);
	 Action*& getAct2() ;
	void setAct2( Action*& act2);
	double getGain() ;
	void setGain(double gain);
	TypeModification getT() ;
	void setT(TypeModification t);
	double getArrive() ;
	void setArrive(double arrive);
	double getDepart() ;
	void setDepart(double depart);
	double getFinal();
	void setFinal(double final);
	void toFlux();

};

} /* namespace Calcul */

#endif /* MODIFICATION_H_ */
