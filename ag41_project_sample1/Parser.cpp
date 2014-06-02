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

Data* Parser::parseFile(string path) {

	Data* d = new Data();
	vector<Client*> vectClient;
	vector<Produit*> vectProduit;
	vector<Commande*> vectCommande;

	ifstream file(path.c_str(), ios::in);

	if(file) {
		string line;
		vector<string> fields, fields2;

		while(getline(file,line)) {

			// Formatage de la ligne
			line.erase(std::remove(line.begin(),line.end(),' '),line.end()); // remove space
			fields = split( line, ":");

			// Affichage
			//for(int i=0; i < fields.size(); i++)
			//	cout << fields.at(i) << endl;

			// Recuperation des donnees
			if(!fields.empty()) {

				if(fields.at(0) == "NBR_PRODUCT") {
					for(int i=0; i < atoi( fields.at(1).c_str()); i++) {
						Produit* p = new Produit("Produit "+i);
						vectProduit.push_back(p);
					}
				}

				if(fields.at(0) == "TRANSPORTER_CAPACITY") {
					// A implementer
				}

				if(fields.at(0) == "TRANSPORTER_DELIVERY_COST_ETA") {
					d->setKTransport( atof( fields.at(1).c_str()));
				}

				if(fields.at(0) == "CUSTOMER") {
					Client* c = new Client("Client "+fields.at(1));
					vectClient.push_back(c);

					getline(file,line);
					line.erase(std::remove(line.begin(),line.end(),' '),line.end()); // remove space
					fields = split( line, ":");

					if(fields.at(0) == "CUSTOMER_HOLDING_COSTS")
						c->setKStockage( atof( fields.at(1).c_str()));

					d->ajouterClient(c);

					getline(file,line);
					line.erase(std::remove(line.begin(),line.end(),' '),line.end()); // remove space
					fields = split( line, ":");

					if(fields.at(0) == "TRANSPORTER_DELIVERY_TIME_SUPPLIER_CUSTOMER")
						d->distanceClient(c, atof( fields.at(1).c_str()));
				}

				if(fields.at(0) == "JOB_CUSTOMER") {
					fields = split( fields.at(1), ";");

					getline(file,line);
					line.erase(std::remove(line.begin(),line.end(),' '),line.end()); // remove space
					fields2 = split( line, ":");
					fields2 = split( fields2.at(1), ";");

					for(int i=0; i < fields.size(); i++) {
						Commande* co = new Commande( vectProduit.at(i), atof( fields2.at(i).c_str()));
						vectCommande.push_back(co);

						int numClient = atoi( fields.at(i).c_str()) - 1;
						vectClient.at(numClient)->addCommande(co);
						vectClient.at(numClient)->setKStockage( 3 * (float)numClient / 2 );
					}
				}

				if(fields.at(0) == "TIME_CUSTOMER_CUSTOMER") {
					fields = split( fields.at(1), ";");

					int numClient1 = atoi( fields.at(0).c_str()) - 1;
					int numClient2 = atoi( fields.at(1).c_str()) - 1;
					int tempsDeplacement = atoi( fields.at(2).c_str());

					d->distanceClient(vectClient.at(numClient1),vectClient.at(numClient2), tempsDeplacement);
				}
			}
		}
		cout << endl;

		//cout << "Cout transport : " << d->getKTransport();
	}

	file.close();

	return d;
}

vector<string> Parser::split(string str, string separator){

	vector<string> results;
	int found = str.find_first_of(separator);

	while(found != string::npos) {
		if(found > 0){
			results.push_back(str.substr(0,found));
		}
		str = str.substr(found+1);
		found = str.find_first_of(separator);
	}
	if(str.length() > 0) {
		results.push_back(str);
	}
	return results;
}