#include <stdio.h>
#include <stdlib.h>
#include "elevator.h"

Elevator *create_elevator (int capacity, int currentFloor, PersonList *persons) {
// Creation de
 Elevator *elevator = (Elevator*)malloc(sizeof(Elevator));

 elevator ->capacity     = capacity;
 elevator ->currentFloor = currentFloor;
 elevator ->persons      = persons;
 
 return elevator;
}


Building *create_building (int nbFloor, Elevator *elevator, PersonList **waitingLists) {
// creation du batiment 
 Building *building = (Building*)malloc(sizeof(Building));

 building ->nbFloor      = nbFloor;
 building ->elevator     = elevator;
 building ->waitingLists = waitingLists;

 return building;
}


PersonList* exitElevator (Elevator *elevator) {
 PersonList *temp   = elevator ->persons; //la liste des personnes dans la cabine
 PersonList *copy   = elevator ->persons; //une copie de la meme liste
 PersonList *exit   = NULL;
 elevator ->persons = NULL;

 while (temp != NULL) {
	if (temp ->person ->dest != elevator ->targetFloor) {
		elevator ->persons = insert (temp ->person, elevator ->persons);
	}
	else {
		exit = insert (temp ->person, exit);
	}
	temp = temp ->next;
 }

 if (exit == NULL) {
	elevator ->persons = copy;
 }

 return exit;
}


PersonList* enterElevator (Elevator *elevator, PersonList *list) {
 int capacity   = elevator ->capacity;
 int occupation = 0, modif =0;

 PersonList *temp   = elevator ->persons; //la liste de personnes dans la cabine 
 PersonList *copy   = elevator ->persons;
 elevator ->persons = NULL;

 while (temp != NULL){
	elevator ->persons = insert(temp ->person, elevator ->persons);
	temp = temp ->next;
	occupation++;
 }
 
 modif = occupation;
 
 while (occupation < capacity && list != NULL) {
	elevator ->persons = insert (list ->person, elevator ->persons);
	list = list ->next;
	occupation++;
 }

 if (modif == occupation) {
	elevator -> persons = copy;
 }
 
 return list;
}

void stepElevator (Building *building) {
 int currentFloor = building ->elevator ->currentFloor;
 int targetFloor  = building ->elevator ->targetFloor;

 if (currentFloor > targetFloor) {
	building ->elevator ->currentFloor = currentFloor-1;
 }
 else if (currentFloor < targetFloor) {
	building ->elevator ->currentFloor = currentFloor+1;
 }
 else {
	building ->waitingLists[building ->elevator ->targetFloor] = enterElevator(building ->elevator, building ->waitingLists[building ->elevator ->targetFloor]);
	PersonList *exit = exitElevator (building ->elevator);
 }
}
