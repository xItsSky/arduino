#include "Group.h"

Group::Group(int id)
{
	this->id = id;
	
}

Group::Group(int id, char* name)
{
	this->id = id;
	this->name = name;
}

Group::Group(int id, char* name, char* color)
{
	this->id = id;
	this->name = name;
	this->color = color;
}

int Group::getId()
{
	return this->id;
}

char* Group::getColor()
{
	return this->color;
}

char* Group::getName()
{
	return this->name;
}

vector<User*> * Group::getUser()
{
	return this->users;
}

void Group::setColor(char* color)
{
	this->color = color;
}

void Group::setName(char* name)
{
	this->name = name;
}

void Group::setUsers(vector<User*> *users)
{
	this->users = users;
}
