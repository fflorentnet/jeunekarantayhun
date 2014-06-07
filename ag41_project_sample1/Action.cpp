/*
 * Action.cpp
 *
 *  Created on: May 18, 2014
 *      Author: florent
 */

#include "Action.h"

namespace Donnees
{
Action::~Action() {

}

Action::Action(Client* s, Client* e): start(s), end(e), t(DEPLACEMENT), comm((Commande*)0){

}
Action::Action(Client* cli, Commande* co) : start(cli), comm(co), end((Client*)0), t(DEPOT) {
}
TypeAction Action::getType()
{
	return t;
}
Client* Action::getStart()
{
	return start;
}
Client* Action::getEnd()
{
	if (t == DEPLACEMENT)
		return end;
	else
		return (Client*)0;
}
Commande* Action::getCommande()
{
	if (t == DEPOT)
		return comm;
	else
		return (Commande*)0;
}
void Action::setEnd(Client* c)
{
	end = c;
}
bool Action::operator==(Action & a)
{
	bool b=true;
	if (getType() == a.getType())
	{
		if (getType() == DEPLACEMENT)
		{
			if (getStart() == a.getStart())
			{
				if (getEnd() == a.getEnd())
				{
					b = true;
				}
			}
		}
		else if (getType() == DEPOT)
		{
			if (getCommande() == a.getCommande())
			{
				if (getStart() == a.getStart())

				{if (getEnd() == a.getEnd())

				{b = true;}
				}
			}
		}
	}
	return b;
}
}
