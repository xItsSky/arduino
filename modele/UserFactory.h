#pragma once

#include <list>

#include "AbstractFactory.h"
#include "User.h"

class UserFactory :
	public AbstractFactory<User>
{
private:
	UserFactory();
	static UserFactory* instance;
	std::list<User*> users;
public:
	static UserFactory* getInstance();
	User* create(User* group) override;
	bool remove(User* group) override;
	User* update(User* group) override;
	User* find(int index) override;
	std::list<User*> findAll() override;
	int indexOf(User* group);
};

