/*
 * Client.h
 *
 *  Created on: May 15, 2014
 *      Author: florent
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <vector>
#include <string>

class Commande;

using namespace std;

class Client {
private:
	vector<Commande*> *listeCommande;
	string nom;
public:
	Commande* derniereCommande() const;
	Commande* premiereCommande() const;
	Client(string s);
	vector<Commande*>* getCommande();
	void addCommande(Commande* c);
	virtual ~Client();
	string getNom() const;
	void setNom(string s);
    friend ostream& operator<< (ostream& flux, Client& c);
};

#endif /* CLIENT_H_ */