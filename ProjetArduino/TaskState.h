#pragma once
#include <string>

using namespace std;

// Constante ToDo string
static const char* ToDo_str = "ToDo";

// Constante InProgress string
static const char* InProgress_str = "InProgress";

// Constante Done string
static const char* Done_str = "Done";

// All strings value
static const char* enum_str[] =
{ ToDo_str, InProgress_str, Done_str };

/* Task state enum by Quentin Emo */
enum class TaskState : int {
	Todo = 0, 
	InProgress = 1, 
	Done = 2
};