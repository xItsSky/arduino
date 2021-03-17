#include "UserFactory.h"

UserFactory* UserFactory::instance = new UserFactory();

UserFactory::UserFactory() {
	this->users = {};
}

UserFactory* UserFactory::getInstance() {
	return UserFactory::instance;
}

User* UserFactory::create(User* user) {
	this->users.push_back(user);
	return user;
}

bool UserFactory::remove(User* user) {
	this->users.remove(user);
	return(indexOf(user) == -1);
}

User* UserFactory::update(User* user) {
	std::list<User*>::iterator it = this->users.begin();
	for (int i = 0; i < (int)this->users.size(); i++) {
		if (*(*it) == *(user)) {
			(*it)->setName(user->getName());
			(*it)->setTasks(user->getTasks());
			return (*it);
		}
		++it;
	}
	return NULL;
}

User* UserFactory::find(int index) {
	std::list<User*>::iterator it = this->users.begin();
	for (int i = 0; i < index; i++) {
		++it;
	}
	return *it;
}

std::list<User*> UserFactory::findAll() {
	return this->users;
}

int UserFactory::indexOf(User* user) {
	int index = -1;
	std::list<User*>::iterator it = this->users.begin();
	for (int i = 0; i < (int)this->users.size(); i++) {
		if (*(*it) == *(user))
			index = i;
		++it;
	}
	return index;
}