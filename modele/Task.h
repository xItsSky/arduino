#include "TaskState.h"
#include <string>

/* Task class by Quentin Emo */
class Task {
	private:
		std::string id;
		TaskState state;
	public:
		Task(std::string id);
		std::string getId();
		std::string getState();
		bool nextState();
};