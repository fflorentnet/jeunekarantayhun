/*
 * Produit.h
 *
 *  Created on: May 15, 2014
 *      Author: florent
 */

#ifndef PRODUIT_H_
#define PRODUIT_H_
#include <string>
using namespace std;
class Produit {
private:
	string nom;
public:
	Produit(string i);
	virtual ~Produit();
	string getNom() const;
	void setNom(string id);
}
;

#endif /* PRODUIT_H_ */
