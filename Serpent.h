#ifndef __SERPENT__
#define __SERPENT__
#include "Case.h"
#include <stdlib.h>

typedef enum {
    NORD,
    SUD,
    EST,
    OUEST
} Direction;

typedef struct {
    Direction direction;
    Liste tete;
    int taille;
} Serpent;

Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille);
Case serpent_case_visee(Serpent serp);
#endif
