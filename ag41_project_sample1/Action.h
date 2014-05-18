/*
 * Action.h
 *
 *  Created on: May 18, 2014
 *      Author: florent
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "Client.h"
#include "Commande.h"

class Action {
private:
	enum TypeAction { DEPLACEMENT, DEPOT };
	TypeAction t;
	Client* start;
	Client* end;
	Commande* comm;
public:
	Action(Client* s, Client* e);
	Action(Client* cli, Commande* co);
	TypeAction getType();

	virtual ~Action();
};

#endif /* ACTION_H_ */
