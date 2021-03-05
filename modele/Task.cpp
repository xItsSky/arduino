#include "Task.h"

char * Task::getId() {
	return this.id;
}

TaskState Task::getState() {
	return this.state;
}