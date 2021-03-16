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
	int sound;

public:
	Group(int id);
	Group(int id, char* name);
	Group(int id, char* name, char* color, int sound);
	int getId();
	char* getColor();
	char* getName();
	int getSound();
	vector<User*> *getUser();
	void setColor(char* color);
	void setName(char* name);
	void setSound(int sound);
	void setUsers(vector<User*> *users);
};