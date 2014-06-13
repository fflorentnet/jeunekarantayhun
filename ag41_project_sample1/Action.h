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
		bool passeParFournisseur;
		TypeAction t;
		Client* start;
		Client* end;
		Commande* comm;
		vector<Client*> path;
	public:
		Action(Client* s, Client* e, vector<Client*> p);
		Action(Client* cli, Commande* co);
		Action(Action* a);
		TypeAction getType();
		Client* getStart();
		Client* getEnd();
		void setEnd(Client* c);
		Commande* getCommande();
		virtual ~Action();
		bool operator==(Action& a);
		bool operator==(Action* a);
		string toString();
		vector<Client*>& getPath();
		bool contientFournisseur();
};
}
#endif /* ACTION_H_ */
