/*
 * Parser.cpp
 *
 *  Created on: 2 juin 2014
 *      Author: benjamin
 */

#include "Parser.h"

using namespace std;

Parser::Parser() {
}
Parser::~Parser() {
}

void Parser::parseFile(string path) {
	vector<Client*> vectClient;
	vector<Produit*> vectProduit;
	vector<Commande*> vectCommande;

	ifstream file(path.c_str(), ios::in);

	if (file) {
		string line;
		vector<string> fields, fields2;

		while (getline(file, line)) {

			// Formatage de la ligne
			line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // remove space
			fields = split(line, ":");

			// Affichage du fichier
			//for(double i=0; i < fields.size(); i++)
			//	cout << fields.at(i) << endl;

			// Recuperation des donnees
			if (!fields.empty()) {

				if (fields.at(0) == "NBR_PRODUCT") {
					for (double i = 0; i < atoi(fields.at(1).c_str()); i++) {
						ostringstream oss;
						oss << i;
						string name = "Produit " + oss.str();
						Produit* p = new Produit(name);
						vectProduit.push_back(p);
					}
				}

				if (fields.at(0) == "TRANSPORTER_CAPACITY") {
					Data::getInstance().setCapacite(atof(fields.at(1).c_str()));
				}

				if (fields.at(0) == "TRANSPORTER_DELIVERY_COST_ETA") {
					Data::getInstance().setKTransport(atof(fields.at(1).c_str()));
				}

				if (fields.at(0) == "CUSTOMER") {
					Client* c = new Client("Client " + fields.at(1));
					vectClient.push_back(c);

					getline(file, line);
					line.erase(std::remove(line.begin(), line.end(), ' '),
							line.end()); // remove space
					fields = split(line, ":");

					if (fields.at(0) == "CUSTOMER_HOLDING_COSTS")
						c->setKStockage(atof(fields.at(1).c_str()));

					Data::getInstance().ajouterClient(c);

					getline(file, line);
					line.erase(std::remove(line.begin(), line.end(), ' '),
							line.end()); // remove space
					fields = split(line, ":");

					if (fields.at(0)
							== "TRANSPORTER_DELIVERY_TIME_SUPPLIER_CUSTOMER")
						Data::getInstance().distanceClient(c, atof(fields.at(1).c_str()));
				}

				if (fields.at(0) == "JOB_CUSTOMER") {
					fields = split(fields.at(1), ";");

					getline(file, line);
					line.erase(std::remove(line.begin(), line.end(), ' '),
							line.end()); // remove space
					fields2 = split(line, ":");
					fields2 = split(fields2.at(1), ";");

					for (double i = 0; i < fields.size(); i++) {
						if(i<vectProduit.size()) {
							Commande* co = new Commande(vectProduit.at(i),
									atof(fields2.at(i).c_str()));
							vectCommande.push_back(co);

							double numClient = atoi(fields.at(i).c_str()) - 1;
							vectClient.at(numClient)->addCommande(co);
						}
					}
				}

				if (fields.at(0) == "TIME_CUSTOMER_CUSTOMER") {
					fields = split(fields.at(1), ";");

					double numClient1 = atoi(fields.at(0).c_str()) - 1;
					double numClient2 = atoi(fields.at(1).c_str()) - 1;
					double tempsDeplacement = atoi(fields.at(2).c_str());

					Data::getInstance().distanceClient(vectClient.at(numClient1),
							vectClient.at(numClient2), tempsDeplacement);
				}
			}
		}

		/*
		// Vérification
		// produit
		for(int i=0; i < vectProduit.size(); i++)
			cout << vectProduit.at(i)->getNom() << endl;

		// transporteur
		cout << "TRANSPORTER_CAPACITY : " << Data::getInstance().getCapacite() << endl;
		cout << "TRANSPORTER_DELIVERY_COST_ETA : " << Data::getInstance().getKTransport() << endl;

		// client
		for(int i=0; i < vectClient.size(); i++) {
			cout << vectClient.at(i)->getNom() << " - " <<
			vectClient.at(i)->getKStockage() << " - " <<
			Data::getInstance().getDistanceFournisseurClient(vectClient.at(i)) << endl;

			for(int j=0; j < vectClient.at(i)->getCommande()->size(); j++) {
				cout << "Commande : " << vectClient.at(i)->getCommande()->at(j)->getProduit()->getNom() << " - " <<
				vectClient.at(i)->getCommande()->at(j)->getDate() << endl;
			}
		}
		cout << endl;

		// commande
		for(int i=0; i < vectCommande.size(); i++)
			cout << "Commande : " << vectCommande.at(i)->getProduit()->getNom() << " - " <<
			vectCommande.at(i)->getDate() << endl;
		cout << endl;

		// distance entre client
		for(int i=0; i < vectClient.size()-1; i++) {
			cout << "Distance client" << i << " , client" << i+1 << " : " <<
			Data::getInstance().distanceClient(vectClient.at(i),vectClient.at(i+1)) << endl;
		}
		cout << "Distance client" << 0 << " , client" << vectClient.size()-1 << " : " <<
			Data::getInstance().distanceClient(vectClient.at(0),vectClient.at(vectClient.size()-1)) << endl;
		cout << endl;
		*/
	}

	file.close();

}

vector<string> Parser::split(string str, string separator) {

	vector<string> results;
	int found = str.find_first_of(separator);

	while (found != string::npos) {
		if (found > 0) {
			results.push_back(str.substr(0, found));
		}
		str = str.substr(found + 1);
		found = str.find_first_of(separator);
	}
	if (str.length() > 0) {
		results.push_back(str);
	}
	return results;
}
