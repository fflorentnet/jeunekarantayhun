/*
 * Commande.h
 *
 *  Created on: May 15, 2014
 *      Author: florent
 */

#ifndef COMMANDE_H_
#define COMMANDE_H_
#include <iostream>
#include "Produit.h"

using namespace std;
namespace Donnees
{
	class Commande {
	private:
		Produit* p;
		int date;
	public:
		Commande(Produit* pro, int d);
		Commande(Commande &c);
		virtual ~Commande();
		int getDate();
		void setDate(int d);
		Produit* getProduit();
		void setProduit(Produit* p);
		friend ostream& operator<<(ostream &flux, Commande* c);
		bool operator==(Commande & c);
	};
}
#endif /* COMMANDE_H_ */
