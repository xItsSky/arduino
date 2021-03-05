#include <iostream>
#include "User.cpp"

using namespace std;

/* Exemple main with modele usage */
int main() {
	User* user = new User("Quentin");
	cout << "On est " + user->getId() << endl;

	Task *task = new Task("mytask");
	task->nextState();
	user->addTask(task);
	cout << "On a la tache " + user->getTask(0)->getId() + " qui est " + user->getTask(0)->getState() << endl;
}