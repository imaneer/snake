#include "Pomme.h"
#include <ncurses.h>

/* genere une pomme avec des coordonees aleatoires */ 
Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes) {
    int x, y;
    Pomme tmp;
    x = rand() % (nb_colonnes - 1);
    y = rand() % (nb_lignes - 1);
    tmp.pomme.x = x;
    tmp.pomme.y = y;
    return tmp;
}

/*allocation d'une pomme */
L_pomme alloue_pomme(int x, int y) {
    L_pomme tmp;
    tmp = (L_pomme)malloc(sizeof(C_pomme));
    if (tmp == NULL)
        return NULL;
    tmp->debut.pomme.x = x;
    tmp->debut.pomme.y = y;
    tmp->suivant = NULL;
    return tmp;
}
/* suppression d'une pomme renvoie 1 si la suppression est faite et 0 sinon */
int supprime_pomme(L_pomme *liste, int x, int y) {
    L_pomme tmp, index;
    tmp = NULL;
    index = *liste;
    /* si la liste est vide on ne fait rien */
    if (index == NULL)
        return 0;
    /* si la pomme qu'on veut supprimer est la tete de la liste */
    if (((*liste)->debut.pomme.x == x) && ((*liste)->debut.pomme.y == y)) {
        tmp = *liste;
        /* on la supprime */
        *liste = (*liste)->suivant;
        tmp->suivant = NULL;
        free(tmp);
        return 1;
    }
    else {
        /* on parcourt la liste */
        while (index->suivant != NULL) {
            /* on cherche la pomme a supprimer */
            if (index->suivant->debut.pomme.x == x && index->suivant->debut.pomme.y == y) {
                /* si on la trouve on la supprime */
                tmp = index->suivant;
                index->suivant = tmp->suivant;
                tmp->suivant = NULL;
                free(tmp);
                return 1;
            }
            /* sinon on continue a chercher */
            index = index->suivant;
        }
    }
    return 0;
}

/* renvoie la taille de la liste des pommes */
int taille_poison(L_pomme poison) {
    int taille;
    taille = 0;
    while (poison != NULL) {
        taille++;
        poison = poison->suivant;
    }
    return taille;
}
/* supprime une pomme de liste */
void supprime_poison(L_pomme *liste) {
    L_pomme tmp;
    tmp = *liste;
    *liste = (*liste)->suivant;
    free(tmp);
}

/* libere de la memoire allouee */
void liberer_Liste_pomme(L_pomme* L){
    L_pomme next, courant;
    courant = *L;
    while(courant){
        next = courant->suivant;
        free(courant);
        courant = next;
    }
}
