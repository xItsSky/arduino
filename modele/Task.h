#pragma once
#include "TaskState.h"

/* Task class by Quentin Emo */
class Task {
	private:
		int id;
		char* name;
		TaskState state;
	public:
		Task(int id);
		Task(int id, char* name);
		int getId();
		char* getName();
		const char* getState();
		bool nextState();
};