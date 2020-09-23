#include <stdio.h>
#include <stdlib.h>
#include "person.h"

Person* createPerson (int src, int dest) {
  Person* person =(Person*)malloc(sizeof(Person));

  person ->dest = dest;
  person ->src  = src;
  return person;
}

PersonList* insert (Person *p, PersonList *list) {
  PersonList *liste = (PersonList*)malloc(sizeof(PersonList));
  
  liste ->next   = list;
  liste ->person = p;
  return liste;
}
