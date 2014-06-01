/*
 * Commande.cpp
 *
 *  Created on: May 15, 2014
 *      Author: florent
 */

#include "Commande.h"
#include "Produit.h"
#include <iostream>
#include <sstream>
#include <string>


namespace Donnees
{
	Commande::Commande(Produit* pro, int d): p(pro), date(d){
	}

	Commande::~Commande() {
	}
	Commande::Commande(Commande &c)
	{
		p = c.getProduit();
		date = c.getDate();
	}

	ostream& operator<<(ostream &flux, Commande* c)
	{

		stringstream ss1;
		stringstream ss2;
		ss1 << c->getDate();

		flux << "Date de livraison de " << c->getProduit()->getNom() << " : " << ss1.str();
		return flux;
	}

	int Commande::getDate()
	{
		return date;
	}
	void Commande::setDate(int d)
	{
		date = d;
	}
	Produit* Commande::getProduit()
	{
		return p;
	}
	void Commande::setProduit(Produit* p)
	{
		this->p = p;
	}
}
