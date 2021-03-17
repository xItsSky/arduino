#pragma once

#include <list>

#include "Group.h"
#include "AbstractFactory.h"

class GroupFactory :
    public AbstractFactory<Group>
{
private:
	GroupFactory();
	static GroupFactory *instance;
	std::list<Group*> groups;
public:
	static GroupFactory *getInstance();
	Group* create(Group* group) override;
	bool remove(Group* group) override;
	Group* update(Group* group) override;
	Group* find(int index) override;
	std::list<Group*> findAll() override;
	int indexOf(Group* group);
};

