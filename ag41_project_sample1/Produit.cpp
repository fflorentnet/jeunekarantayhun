/*
 * Produit.cpp
 *
 *  Created on: May 15, 2014
 *      Author: florent
 */

#include "Produit.h"

Produit::Produit(string i): nom(i) {
	// TODO Auto-generated constructor stub

}

Produit::~Produit() {
	// TODO Auto-generated destructor stub
}

string Produit::getNom() const {
	return nom;
}

void Produit::setNom(string id) {
	this->nom = nom;
}
