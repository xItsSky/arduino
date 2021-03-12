#pragma once
#include "TaskState.h"
#include <string>

#ifndef Task_h
#define Task_h

/* Task class by Quentin Emo */
class Task {
	private:
		string id;
		TaskState state;
	public:
		Task(string id);
		string getId();
		string getState();
		bool nextState();
};

#endif