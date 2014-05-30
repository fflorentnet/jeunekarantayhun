/*
 * Client.cpp
 *
 *  Created on: May 15, 2014
 *      Author: florent
 */

#include "Client.h"
#include "Commande.h"
#include <string>
#include <iostream>

namespace Donnees
{
	Client::Client(string n): nom(n) {
		// TODO Auto-generated constructor stub
		listeCommande = new vector<Commande*>();
	}

	Client::~Client() {
		// TODO Auto-generated destructor stub
	}

	void Client::addCommande(Commande* c)
	{
		listeCommande->push_back(c);
	}
	ostream& operator<< (ostream& flux, Client& c) {
		int i = 0;
		flux << "Nom: " << c.getNom() << "\n";
		Commande* premiereCommande = c.premiereCommande();
		Commande* derniereCommande = c.derniereCommande();

		if (premiereCommande != (Commande*)0)
		{
				flux << "Première commande à livrer :" << "\n";
				flux << premiereCommande << "\n";
		}
		else
			i++;
		if (derniereCommande != (Commande*)0)
		{
			flux << "Derniere commande à livrer :" << "\n";
			flux << derniereCommande << "\n";
		}
		else
			i++;
		if (i == 2)
		{
			flux << "Il n'y a aucune commande pour ce client." << "\n";
		}
		flux << "-------------------------------------"<<"\n";
		return flux;
	}

	Commande* Client::derniereCommande() const
	{
		int dateMax = 0;
		int date;
		Commande* c = (Commande*)0;
		Commande* temp = (Commande*)0;
		std::vector<Commande*>::const_iterator it;
		for (it = listeCommande->begin(); it != listeCommande->end(); it++)
		{
			temp = (Commande*) (*it);
			date = temp->getDate();
			if (date > dateMax)
			{
				c = temp;
				dateMax = date;
			}
		}
		return c;
	}
	Commande* Client::premiereCommande() const
	{
		int dateMin = -1;
		int date;
		Commande* c = (Commande*)0;
		Commande* temp = (Commande*)0;
		std::vector<Commande*>::const_iterator it;
		for (it = listeCommande->begin(); it != listeCommande->end(); it++)
		{
			temp = (Commande*)(*it);
			date = temp->getDate();
			if (date < dateMin || dateMin == -1)
			{
				c = temp;
				dateMin = date;
			}
		}
		return c;
	}

	string Client::getNom() const
	{
		return nom;
	}

	void Client::setNom(string s)
	{
		nom = s;
	}
	vector<Commande*>* Client::getCommande()
	{
		return listeCommande;
	}
	float Client::getKStockage()
	{
		return kStockage;
	}
	void Client::setKStockage(float k)
	{
		kStockage = k;
	}
}
