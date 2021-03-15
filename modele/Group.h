#pragma once
#include <list>
#include <vector>


#include "User.h"

using namespace std;

/* Group class by Quentin Emo */
class Group {
private:
	
	int id;
	char* name;
	vector<User*> *users = new vector<User*>();
	char* color;

public:
	Group(int id);
	Group(int id, char* name);
	Group(int id, char* name, char* color);
	int getId();
	char* getColor();
	char* getName();
	vector<User*> *getUser();
	void setColor(char* color);
	void setName(char* name);
	void setUsers(vector<User*> *users);

	
	
};