/*
 * Action.cpp
 *
 *  Created on: May 18, 2014
 *      Author: florent
 */

#include "Action.h"


Action::~Action() {
	// TODO Auto-generated destructor stub
}

Action::Action(Client* s, Client* e): start(s), end(e), t(DEPLACEMENT){

}
Action::Action(Client* cli, Commande* co) : start(cli), comm(co), t(DEPOT) {

}
Action::TypeAction Action::getType()
{
	return t;
}
Client* Action::getStart()
{
	return start;
}
Client* Action::getEnd()
{
	if (t == Action::DEPLACEMENT)
		return end;
	else
		return (Client*)0;
}
Commande* Action::getCommande()
{
	if (t == Action::DEPOT)
			return comm;
		else
			return (Commande*)0;
}
