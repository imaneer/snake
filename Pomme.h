#ifndef __POMME__
#define __POMME__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Case.h"

typedef struct {
    Case pomme;
} Pomme;

typedef struct cellule_pomme {
    Pomme debut;
    struct cellule_pomme *suivant;
} C_pomme, *L_pomme;

Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes);
L_pomme alloue_pomme(int x, int y);
int supprime_pomme(L_pomme *liste, int x, int y);
int taille_poison(L_pomme poison);
void supprime_poison(L_pomme *liste);
void liberer_Liste_pomme(L_pomme* L);
#endif