#pragma once
#include "Task.h"
#include <iterator>
#include <list>

#ifndef User_h
#define User_h

/* User class by Quentin Emo */
class User {
private:
	string id;
	list<Task*> tasks;
public:
	User(string id);
	string getId();
	void addTask(Task* task);
	Task* getTask(int _i);
};

#endif