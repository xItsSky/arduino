#pragma once
#include "TaskState.h"

/* Task class by Quentin Emo */
class Task {
	private:
		char* id;
		TaskState state;
	public:
		Task(char* id);
		char* getId();
		const char* getState();
		bool nextState();
};