#include <iostream>
#include "GroupFactory.h"
#include "UserFactory.h"
#include "TaskFactory.h"

using namespace std;

int main() {
	GroupFactory* groups = GroupFactory::getInstance();
	UserFactory* users = UserFactory::getInstance();
	TaskFactory* tasks = TaskFactory::getInstance();

	Group* g1 = new Group(0, (char*)"Group 1", (char*)"#ff000000", 1);
	Group* g2 = new Group(1, (char*)"Group 2", (char*)"#ff000000", 2);
	Group* g3 = new Group(2, (char*)"Group 4", (char*)"#ff000000", 3);

	User* u1 = new User(0, (char*)"Quentin");

	Task* t1 = new Task(0, (char*)"Remplir la fiole");

	groups->create(g1);															// Creation G1
	groups->create(g2);															// Creation G2
	groups->create(g3);															// Creation G3
	groups->update(new Group(2, (char*)"Group 3", (char*)"#ff000000", 3));		// Groupe 4 -> Groupe 3 pour le groupe d'id 2
	groups->remove(g1);

	users->create(u1);

	tasks->create(t1);

	printf("On a %d groupes \n", (int)groups->findAll().size());
	printf("On a %d users \n", (int)users->findAll().size());
	printf("On a %d tasks \n", (int)tasks->findAll().size());

	printf("Index de g1: %d \n", (int)groups->indexOf(g2));

	for (int i = 0; i < (int)groups->findAll().size(); i++) {
		Group* group = groups->find(i);
		printf("On a le groupe: %s d'id %d \n", group->getName(), group->getId());
	}
}