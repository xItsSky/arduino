#include "Group.h"

Group::Group(int id)
{
	this->id = id;
	
}

Group::Group(int id, string name)
{

	this->id = id;
	this->name = name;
}

Group::Group(int id, string name, string color)
{
	this->id = id;
	this->name = name;
	this->color = color;
}

int Group::getId()
{
	return this->id;
}

string Group::getColor()
{
	return this->color;
}

string Group::getName()
{
	return this->name;
}

vector<User*> Group::getUser()
{
	return this->users;
}

void Group::setColor(string color)
{
	this->color = color;
}

void Group::setName(string name)
{
	this->name = name;
}

void Group::setUsers(vector<User*> users)
{
	this->users = users;
}
