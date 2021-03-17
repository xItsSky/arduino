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

Group::Group(int id, char* name, char* color, int sound)
{
	this->id = id;
	this->name = name;
	this->color = color;
	this->sound = sound;
}

int Group::getId()
{
	return this->id;
}

char* Group::getColor()
{
	return this->color;
}

int Group::getSound()
{
	return this->sound;
}

char* Group::getName()
{
	return this->name;
}

std::list<User*> Group::getUser()
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

void Group::setSound(int sound)
{
	this->sound = sound;
}

void Group::setUsers(std::list<User*> users)
{
	this->users = users;
}

void Group::addUser(User* user)
{
	this->users.push_back(user);
}

bool Group::operator==(const Group& group) const {
	return this->id == group.id;
}
