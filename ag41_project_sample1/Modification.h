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
enum TypeModification { DEPLACEMENT, FUSION, SWAP };
class Modification {
private:
	TypeModification t;
	Action* act1;
	Action* act2;
	double tDepart;
	double tArrive;
	//double tFinal;
	double gain;
	Data* d;
public:
	//Modification( Action* ac, double tDep, double tArr, double g);
	Modification( Action* ac1, Action* ac2, double g, double t, double tNext);
	Modification( double tD, double tA, double g, Action* ac1, Action* ac2);

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
	void toFlux();
	string getHash();
};

} /* namespace Calcul */

#endif /* MODIFICATION_H_ */
