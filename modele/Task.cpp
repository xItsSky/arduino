#include "Task.h"

/* Task constructor */
Task::Task(std::string id) {
	this->id = id;
	this->state = TaskState::Todo;
}

/* Return the task id as string */
std::string Task::getId() {
	return this->id;
}

/* Return the current task state as string */
std::string Task::getState() {
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
		case TaskState::Done:
			return false;
	}
}