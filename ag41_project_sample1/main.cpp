#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Commande.h"
#include "Solution.h"
#include "Client.h"
#include "Produit.h"
#include "Tabou.h"
using namespace Donnees;
using namespace Calcul;


float calculCout(double i)
{
	return 3 * (float)i / 2;
}
void jeuEssai1()
{
	Client* c1 = new Client("Client 1");
	Client* c2 = new Client("Client 2");
	Client* c3 = new Client("Client 3");
	Client* c4 = new Client("Client 4");

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

	c1->setKStockage(calculCout(1));
	c2->setKStockage(calculCout(2));

	c3->setKStockage(calculCout(3));

	std::cout << "Affichage des clients:" << endl;
	//std::cout << c1 << c2 << c3 << c4 << c5;
	/*Data &d = Donnees::Data::getInstance();
	Solution s();

	Donnees::Data::getInstance().ajouterClient(c1);
	Donnees::Data::getInstance().ajouterClient(c2);
	Donnees::Data::getInstance().ajouterClient(c3);
	Donnees::Data::getInstance().ajouterClient(c4);

	Donnees::Data::getInstance().distanceClient(c1, 100);
	Donnees::Data::getInstance().distanceClient(c2, 100);
	Donnees::Data::getInstance().distanceClient(c3, 100);
	Donnees::Data::getInstance().distanceClient(c4, 100);

	Donnees::Data::getInstance().setKTransport(2);

	std::cout << "Generation de la solution:" << endl;
	s.generate();
	std::cout << s << endl;
	std::cout << "Difference de sol: " << s.computeDifference() << endl;
	std::cout << s << endl;
	std::cout << "Coût total de la solution: " << s.getValeur() << endl;
	std::cout << "Fini"<<"\n";*/
}
void jeuEssai2()
{
	Client* c1 = new Client("Client 1");
	Client* c2 = new Client("Client 2");
	Client* c3 = new Client("Client 3");
	Client* c4 = new Client("Client 4");

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
	c2->addCommande(co2);
	c3->addCommande(co3);
	c4->addCommande(co4);
	c4->addCommande(co5);

	c1->setKStockage(calculCout(1));
	c2->setKStockage(calculCout(2));
	c3->setKStockage(calculCout(3));
	c4->setKStockage(calculCout(4));

	std::cout << "Affichage des clients:" << endl;
	//std::cout << c1 << c2 << c3 << c4 << c5;
	//d = new Data();
	Donnees::Data::getInstance().setCapacite(5);
	Solution* s = new Solution();

	Donnees::Data::getInstance().ajouterClient(c1);
	Donnees::Data::getInstance().ajouterClient(c2);
	Donnees::Data::getInstance().ajouterClient(c3);
	Donnees::Data::getInstance().ajouterClient(c4);

	Donnees::Data::getInstance().distanceClient(c1, 100);
	Donnees::Data::getInstance().distanceClient(c2, 100);
	Donnees::Data::getInstance().distanceClient(c3, 100);
	Donnees::Data::getInstance().distanceClient(c4, 100);

	Donnees::Data::getInstance().distanceClient(c1,c2, 10);
	Donnees::Data::getInstance().distanceClient(c2,c3, 140);
	Donnees::Data::getInstance().distanceClient(c3,c4, 10);

	Donnees::Data::getInstance().distanceClient(c2,c1, 10);
	Donnees::Data::getInstance().distanceClient(c3,c2, 140);
	Donnees::Data::getInstance().distanceClient(c4,c3, 10);


	Donnees::Data::getInstance().setKTransport(2);

	std::cout << "reGeneration de la solution:" << endl;
	s->generate();

	std::cout << "Application d'un Floyd-Warshall:" << endl;
	Donnees::Data::getInstance().floydWarshall();
	Donnees::Data::getInstance().toString();
	std::cout << "terminé" << endl;
	std::cout << s << endl;


	std::cout << "Difference de sol: " << s->computeDifference() << endl;
	std::cout << s << endl;

	std::cout << "Coût total de la solution: " << s->getValeur() << endl;
	std::cout << "Fini"<<"\n";


	Tabou* t = new Tabou(10);
	s = t->execute(s);
	std::cout << s << endl;
	std::cout << "Coût total de la solution: " << s->getValeur() << endl;
	std::cout << Donnees::Data::getInstance().distanceClient(c1,c3) << endl;
	if (s->check())
			std::cout << "La solution est valide" << endl;
	else
			std::cout << "La solution est fausse" << endl;


}
int main(void)
{
    std::ofstream out("ag41.log");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
	jeuEssai2();
    std::cout.rdbuf(coutbuf); //reset to standard output again
	return 0;
}
