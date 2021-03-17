#include "GroupFactory.h"

GroupFactory* GroupFactory::instance = new GroupFactory();

GroupFactory::GroupFactory() {
	this->groups = {};
}

GroupFactory *GroupFactory::getInstance() {
	return GroupFactory::instance;
}

Group* GroupFactory::create(Group* group) {
	this->groups.push_back(group);
	return group;
}

bool GroupFactory::remove(Group* group) {
	this->groups.remove(group);
	return(indexOf(group) == -1);
}

Group* GroupFactory::update(Group* group) {
	std::list<Group*>::iterator it = this->groups.begin();
	for (int i = 0; i < (int)this->groups.size(); i++) {
		if (*(*it) == *(group)) {
			(*it)->setName(group->getName());
			(*it)->setColor(group->getColor());
			(*it)->setSound(group->getSound());
			(*it)->setUsers(group->getUser());
			return (*it);
		}
		++it;
	}
	return NULL;
}

Group* GroupFactory::find(int index) {
	std::list<Group*>::iterator it = this->groups.begin();
	for (int i = 0; i < index; i++) {
		++it;
	}
	return *it;
}

std::list<Group*> GroupFactory::findAll() {
	return this->groups;
}

int GroupFactory::indexOf(Group* group) {
	int index = -1;
	std::list<Group*>::iterator it = this->groups.begin();
	for (int i = 0; i < (int)this->groups.size(); i++) {
		if (*(*it) == *(group))
			index = i;
		++it;
	}
	return index;
}