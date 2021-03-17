#include "User.h"

/* User constructor */
User::User(int id) {
	this->id = id;
}

User::User(int id, char* name) {
	this->id = id;
	this->name = name;
}


/* Return user id  */
int User::getId() {
	return this->id;
}

char* User::getName() {
	return this->name;
}

void User::setName(char* name)
{
	this->name = name;
}

/* Add a task to the user */
void User::addTask(Task* task) {
	this->tasks.push_back(task);
}

/* Return a task of a user based on the index _i */
Task* User::getTask(int _i) {
    std::list<Task*>::iterator it = this->tasks.begin();
    for (int i = 0; i < _i; i++) {
        ++it;
    }
    return *it;
}

void User::setTasks(std::list<Task*> tasks)
{
	this->tasks = tasks;
}

std::list<Task*> User::getTasks()
{
	return this->tasks;
}

bool User::operator==(const User& user) const
{
	return this->id == user.id;
}
