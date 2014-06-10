/*
 * Action.h
 *
 *  Created on: May 18, 2014
 *      Author: florent
 */

#ifndef ACTION_H_
#define ACTION_H_
#include "Client.h"

namespace Donnees
{
	enum TypeAction { DEPLACEMENT, DEPOT };
	class Action {
	private:
		TypeAction t;
		Client* start;
		Client* end;
		Commande* comm;
	public:
		Action(Client* s, Client* e);
		Action(Client* cli, Commande* co);
		TypeAction getType();
		Client* getStart();
		Client* getEnd();
		void setEnd(Client* c);
		Commande* getCommande();
		virtual ~Action();
		bool operator==(Action & a);
		string toString();
	};
}
#endif /* ACTION_H_ */
