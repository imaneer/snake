#ifndef __INTERFACE__
#define __INTERFACE__
#include "Monde.h"
#include <ncurses.h>
void interface_afficher_quadrillage(Monde mon);
void interface_afficher_pomme(Pomme pom);
void interface_afficher_poison(Pomme pom);
void interface_afficher_double(Pomme pom);
void interface_afficher_serpent (Serpent ser);
void interface_afficher_monde(Monde mon);
void interface_piloter(Monde *mon);
#endif