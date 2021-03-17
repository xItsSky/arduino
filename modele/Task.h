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
		void setName(char* name);
		char* getName();
		void setState(TaskState state);
		TaskState getState();
		bool nextState();
		bool operator==(const Task& task) const;
};