#pragma once
#include <array>
#include <list>
#include <string>
#include <vector>


#include "User.h"

using namespace std;

/* Group class by Quentin Emo */
class Group {
private:
	
	int id;
	string name;
	vector<User*> *users = new vector<User*>();
	string color;

public:
	Group(int id);
	Group(int id, string name);
	Group(int id, string name, string color);
	int getId();
	string getColor();
	string getName();
	vector<User*> *getUser();
	void setColor(string color);
	void setName(string name);
	void setUsers(vector<User*> *users);

	
	
};