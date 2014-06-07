/*
 * Produit.cpp
 *
 *  Created on: May 15, 2014
 *      Author: florent
 */

#include "Produit.h"
namespace Donnees {
Produit::Produit(string i) :
		nom(i) {
}

Produit::~Produit() {
}

string Produit::getNom() const {
	return nom;
}

void Produit::setNom(string id) {
	this->nom = nom;
}
}
