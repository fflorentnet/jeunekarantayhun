#include <stdlib.h>
#include <iostream>

#include "Commande.h"
#include "Solution.h"
#include "Client.h"
#include "Produit.h"

int main(void)
{
	Client* c1 = new Client("Client 1");
	Client* c2 = new Client("Client 2");
	Client* c3 = new Client("Client 3");
	Client* c4 = new Client("Client 4");
	Client* c5 = new Client("Client 5");

	Produit* p1 = new Produit("Produit 1");
	Produit* p2 = new Produit("Produit 2");
	Produit* p3 = new Produit("Produit 3");
	Produit* p4 = new Produit("Produit 4");
	Produit* p5 = new Produit("Produit 5");

	Commande* co1 = new Commande(p1, 250);
	Commande* co2 = new Commande(p2, 250);
	Commande* co3 = new Commande(p3, 240);
	Commande* co4 = new Commande(p4, 300);
	Commande* co5 = new Commande(p5, 340);

	c1->addCommande(co1);
	c1->addCommande(co2);

	c3->addCommande(co3);
	c3->addCommande(co4);
	c3->addCommande(co5);

	std::cout << "Affichage des clients:" << endl;
	//std::cout << c1 << c2 << c3 << c4 << c5;

	Solution s;
	s.ajouterClient(c1);
	s.ajouterClient(c2);
	s.ajouterClient(c3);
	s.ajouterClient(c4);
	s.ajouterClient(c5);

	s.distanceClient(c1, 100);
	s.distanceClient(c2, 100);
	s.distanceClient(c3, 100);
	s.distanceClient(c4, 100);
	s.distanceClient(c5, 100);

	std::cout << "Generation de la solution:" << endl;
	s.generate();
	std::cout << s << endl;
	std::cout << "Fini"<<"\n";
	return 0;
}
