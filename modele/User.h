#pragma once
#include "Task.h"
#include <iterator>
#include <list>

/* User class by Quentin Emo */
class User {
private:
	char* id;
	std::list<Task*> tasks;
public:
	User(char* id);
	char* getId();
	void addTask(Task* task);
	Task* getTask(int _i);
};