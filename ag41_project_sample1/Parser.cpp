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

	ifstream file(path.c_str(), ios::in);

	if(file) {
		string line;
		vector<string> fields;

		while(getline(file,line)) {

			line.erase(std::remove(line.begin(),line.end(),' '),line.end()); // remove space

			fields = split( line, ":");

			for(int i=0; i < fields.size(); i++)
				cout << fields.at(i) << endl;
		}
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
