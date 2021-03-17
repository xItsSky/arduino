#include "TaskFactory.h"

TaskFactory* TaskFactory::instance = new TaskFactory();

TaskFactory::TaskFactory() {
	this->tasks = {};
}

TaskFactory* TaskFactory::getInstance() {
	return TaskFactory::instance;
}

Task* TaskFactory::create(Task* task) {
	this->tasks.push_back(task);
	return task;
}

bool TaskFactory::remove(Task* task) {
	this->tasks.remove(task);
	return(indexOf(task) == -1);
}

Task* TaskFactory::update(Task* task) {
	std::list<Task*>::iterator it = this->tasks.begin();
	for (int i = 0; i < (int)this->tasks.size(); i++) {
		if (*(*it) == *(task)) {
			(*it)->setName(task->getName());
			(*it)->setState(task->getState());
			return (*it);
		}
		++it;
	}
	return NULL;
}

Task* TaskFactory::find(int index) {
	std::list<Task*>::iterator it = this->tasks.begin();
	for (int i = 0; i < index; i++) {
		++it;
	}
	return *it;
}

std::list<Task*> TaskFactory::findAll() {
	return this->tasks;
}

int TaskFactory::indexOf(Task* task) {
	int index = -1;
	std::list<Task*>::iterator it = this->tasks.begin();
	for (int i = 0; i < (int)this->tasks.size(); i++) {
		if (*(*it) == *(task))
			index = i;
		++it;
	}
	return index;
}