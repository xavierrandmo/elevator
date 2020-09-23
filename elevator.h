#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "person.h"

typedef struct _Elevator {
	int capacity; //capacité maximale de la cabine
	int currentFloor; //étage courant
	int targetFloor; // destination
	PersonList *persons; // personnes dans la cabine
} Elevator;

typedef struct _Building {
	int nbFloor; // nombre d'étage des l'immeuble
	Elevator *elevator; // la cabine d'ascenseur
	PersonList **waitingLists; // array of waiting list
} Building;

Elevator *create_elevator (int capacity, int currentFloor, PersonList *persons);
Building *create_building (int nbFloor, Elevator *elevator, PersonList **waitingLists);

PersonList* exitElevator (Elevator *elevator);
PersonList* enterElevator (Elevator *elevator, PersonList *list);
void stepElevator (Building *building);

#endif
