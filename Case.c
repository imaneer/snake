#include "Case.h"
/* alloue une Cellule qui contient c et renvoie un pointeur sur cette cellule*/
Liste alloue_case(Case c){
    Liste tmp;
    tmp = (Liste)malloc(sizeof(Cellule));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->coordonnees.x = c.x;
    tmp->coordonnees.y = c.y;
    tmp->suivant = NULL;
    return tmp;
}
/* ajoute une case c a la liste liste  renvoie 0 si l'allocation s'est mal passe et 1 sinon */
int ajoute_en_tete (Liste *liste, Case c) {
    Liste tete;
    tete = alloue_case(c);
    if (tete == NULL) {
        return 0;
    }
    tete->suivant = *liste;
    *liste = tete;
    return 1;
}
/* supprime la derniere cellule de la liste liste */ 
void supprime_derniere_case(Liste *liste) {
    Liste tmp;
    tmp = *liste;
    /* si la liste est vide on ne fait rien */
    if (tmp == NULL)
        return;
    /* si la liste ne contient qu'un seul element on le supprime */ 
    if (tmp->suivant == NULL) {
        free(tmp);
        tmp = NULL;
        return;
    }
    /* sinon on parcours la liste */
    while (tmp->suivant->suivant != NULL)
        tmp = tmp->suivant;
    /* et on supprime le dernier element */ 
    free(tmp->suivant);
    tmp->suivant = NULL;
}

/* fonction pour liberer la memoire allouee */
void liberer_Liste(Liste* L){
    Liste next, courant;
    courant = *L;
    while(courant){
        next = courant->suivant;
        free(courant);
        courant = next;
    }
}







