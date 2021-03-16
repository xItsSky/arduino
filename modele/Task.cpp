#include "Task.h"

/* Task constructor */
Task::Task(int id) {
	this->id = id;
	this->state = TaskState::Todo;
}

Task::Task(int id, char* name) {
	this->id = id;
	this->name = name;
	this->state = TaskState::Todo;
}

/* Return the task id  */
int Task::getId() {
	return this->id;
}

char* Task::getName() {
	return this->name;
}

/* Return the current task state as string */
const char* Task::getState() {
	return enum_str[(int) this->state];
}

/* Set up the task on the next state */
bool Task::nextState() {
	switch (this->state) {
		case TaskState::Todo:
			this->state = TaskState::InProgress;
			return true;
		case TaskState::InProgress:
			this->state = TaskState::Done;
			return true;
		default:
			return false;
	}
}