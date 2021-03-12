#pragma once
#include "Task.h"
#include <iterator>
#include <list>

/* User class by Quentin Emo */
class User {
private:
	std::string id;
	std::list<Task*> tasks;
public:
	User(std::string id);
	std::string getId();
	void addTask(Task* task);
	Task* getTask(int _i);
};