/*
 * Parser.h
 *
 *  Created on: 2 juin 2014
 *      Author: benjamin
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Data.h"
using namespace Donnees;

class Parser {
public:
	Parser();
	virtual ~Parser();

	void parseFile(std::string path);
	vector<string> split(string str, string separator);
};

#endif /* PARSER_H_ */
