#include <iostream>


#include "Group.h"
#include "Task.h"
#include "User.h"

using namespace std;

/* Exemple main with modele usage */
int main() {

	Group* group = new Group(1);
	group->setName("Groupe de test");
	group->setColor("#FF0000");
	
	User* user = new User("Quentin");
	cout << "On est " + user->getId() << endl;


	vector<User*> vec;
	vec.push_back(user);
	vec.push_back(user);
	vec.push_back(user);

	group->getUser()->push_back(user);
	group->getUser()->push_back(user);
	group->getUser()->push_back(user);
	cout << group->getUser()->at(0)->getId() << endl;
	

	Task* task = new Task("mytask");
	task->nextState();
	user->addTask(task);
	cout << "On a la tache " + user->getTask(0)->getId() + " qui est " + user->getTask(0)->getState() << endl;

	
}