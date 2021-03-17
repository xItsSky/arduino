#pragma once
#include <list>


#include "User.h"

using namespace std;

/* Group class by Quentin Emo */
class Group {
private:
	
	int id;
	char* name;
	std::list<User*> users;
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
	std::list<User*> getUser();
	void setColor(char* color);
	void setName(char* name);
	void setSound(int sound);
	void addUser(User* user);
	void setUsers(std::list<User*> users);
	bool operator==(const Group& group) const;
};