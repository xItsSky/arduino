#include "User.h"

/* User constructor */
User::User(std::string id) {
	this->id = id;
}

/* Return user id as string */
std::string User::getId() {
	return this->id;
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