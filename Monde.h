#ifndef __MONDE__
#define __MONDE__

#include <ncurses.h>
#include <stdio.h>
#include "Serpent.h"
#include "Pomme.h"

typedef struct {
    int lignes;
    int colonnes;
    Serpent serpent;
    L_pomme position_pomme;
    L_pomme position_poison;
    L_pomme position_double;
    int nb_pomme_mange;
    int etat;
} Monde;

void monde_ajouter_pomme(Monde *mon);
void monde_ajouter_poison(Monde *mon);
void monde_ajouter_double(Monde *mon);
int case_dans_serpent(Serpent serpent, Case c);
int case_dans_pomme(L_pomme liste_pomme, Case c);
Monde monde_initialiser(int nb_lignes, int nb_colonnes, int taille_serpent, int nb_pommes);
int monde_est_mort_serpent(Monde mon);
void monde_evoluer_serpent(Monde *mon);

#endif