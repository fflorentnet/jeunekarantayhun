/*
 * Action.cpp
 *
 *  Created on: May 18, 2014
 *      Author: florent
 */

#include "Action.h"
#include <sstream>

namespace Donnees
{
Action::~Action() {

}

Action::Action(Client* s, Client* e): start(s), end(e), t(DEPLACEMENT), comm((Commande*)0){

}
Action::Action(Client* cli, Commande* co) : start(cli), comm(co), end((Client*)0), t(DEPOT) {
}
Action::Action(Action* a)
{
	t = a->t;
	start = a->start;
	end = a->end;
	if (a->comm != NULL)
		comm = new Commande(a->comm);
	else
		comm = NULL;
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
string Action::toString()
{
	string s = "";
	if (getType() == DEPLACEMENT)
	{
		if (getStart() != NULL)
			s = " DEPLACEMENT de " + getStart()->getNom();
		else
			s = " DEPLACEMENT depuis le Fournisseur";
		if (getEnd() != NULL)
			s += " vers " + getEnd()->getNom();
		else
			s += " vers le Fournisseur";
	}
	else if (getType() == DEPOT)
	{
		std::stringstream ss;
		ss << getCommande()->getDate();
		s = " DEPOT de " + getCommande()->getProduit()->getNom() + " chez " + getStart()->getNom() + " (avant " + ss.str() + ")";
	}
	return s;
}
bool Action::operator==(Action * a)
																						{
	Client* start = a->getStart();
	Client* end = a->getEnd();
	Commande* comm = a->getCommande();

	bool b=true;
	if (getType() == a->getType())
	{
		if (getType() == DEPLACEMENT)
		{
			bool a = false;
			bool c = false;
			if (getStart() == start)
			{
				a = true;
			}
			else
			{
				if ((*getStart()) == start)
				{
					a = true;
				}
			}

			if (getEnd() == end)
			{
				c = true;
			}
			else
			{
				if ((*getEnd()) == end)
				{
					c = true;
				}
			}
			if (a && c)
				b = true;
		}
	}
	else if (getType() == DEPOT)
	{
		if ((*getCommande()) == (*comm))
		{
			if ((*getStart()) == (*start))
			{
				if ((*getEnd()) == (*end))
				{
					b = true;}
			}
		}

	}
	return b;

}
bool Action::operator==(Action & a)
{
	bool b=true;
	if (getType() == a.getType())
	{
		if (getType() == DEPLACEMENT)
			if (getStart() == a.getStart())
				if (getEnd() == a.getEnd())
					b = true;
				else if (getType() == DEPOT)
					if (getCommande() == a.getCommande())
						if (getStart() == a.getStart())
							if (getEnd() == a.getEnd())
								b = true;
	}
	return b;
	}
}
