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
	Commande::Commande(Produit* pro, float d): p(pro), date(d){
	}

	Commande::~Commande() {
		// TODO Auto-generated destructor stub
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

	float Commande::getDate()
	{
		return date;
	}
	void Commande::setDate(float d)
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
	bool Commande::operator==(Commande & c)
	{
		bool b = true;
		if (c.date != this->date)
			return false;
		else
			if (c.p != this->p)
				return false;
		return true;
	}
}
