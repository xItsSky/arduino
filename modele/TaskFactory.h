#pragma once

#include <list>

#include "AbstractFactory.h"
#include "Task.h"

class TaskFactory :
	public AbstractFactory<Task>
{
private:
	TaskFactory();
	static TaskFactory* instance;
	std::list<Task*> tasks;
public:
	static TaskFactory* getInstance();
	Task* create(Task* group) override;
	bool remove(Task* group) override;
	Task* update(Task* group) override;
	Task* find(int index) override;
	std::list<Task*> findAll() override;
	int indexOf(Task* group);
};
