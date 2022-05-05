#ifndef __CASE__
#define __CASE__
#include <stdlib.h>
#include<stdio.h>
typedef struct {
    int x;
    int y;
} Case;

typedef struct cellule {
    Case coordonnees;
    struct cellule *suivant;
} Cellule, *Liste;

Liste alloue_case(Case c);
int ajoute_en_tete (Liste *liste, Case c);
void supprime_derniere_case (Liste *liste);
void liberer_Liste(Liste* L);
#endif
