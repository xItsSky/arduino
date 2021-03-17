#pragma once
#include "Task.h"
#include <iterator>
#include <list>

/* User class by Quentin Emo */
class User {
private:
	int id;
	char* name;
	std::list<Task*> tasks;
public:
	User(int id);
	User(int id, char* name);
	int getId();
	char* getName();
	void setName(char* name);
	void addTask(Task* task);
	Task* getTask(int _i);
	void setTasks(std::list<Task*> tasks);
	std::list<Task*> getTasks();
	bool operator==(const User& user) const;
};