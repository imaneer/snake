#include "Serpent.h"

/* initialise un serpent et le renvoie */
Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille) {
    Serpent tmp;
    Liste prec;
    Liste courant;
    Case c;
    int i;
    c.x = nb_colonnes / 2;
    c.y = nb_lignes / 2;
    tmp.direction = EST;
    for (i = 0 ; i < taille ; i++) {
        c.x -=  i;
        courant = alloue_case(c);
        if (i == 0) {
            prec = courant;
            tmp.tete = prec;
        }
        else {
            prec->suivant = courant;
            prec = prec->suivant;
        }
    }
    return tmp;
}
/* renvoie les coordennes de la case visee par le serpent */
Case serpent_case_visee(Serpent serp) {
    Case c;
    switch (serp.direction) {
        case NORD :
            c.x = serp.tete->coordonnees.x;
            c.y = serp.tete->coordonnees.y - 1;
            break;
        case SUD :
            c.x = serp.tete->coordonnees.x;
            c.y = serp.tete->coordonnees.y + 1;
            break;
        case OUEST :
            c.x = serp.tete->coordonnees.x - 1;
            c.y = serp.tete->coordonnees.y;
            break;
        case EST :
            c.x = serp.tete->coordonnees.x + 1;
            c.y = serp.tete->coordonnees.y;
            break;
    }
    return c;
}




