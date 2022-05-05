#include "Monde.h"

/* ajouter une pomme a la liste */
void monde_ajouter_pomme(Monde *mon) {
    L_pomme courant;
    L_pomme tmp;
    Case c;
    /* on prend une case aleatoirement */
    c.x = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.x;
    c.y = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.y;

    /* si la liste des pommes est vide on rajoute la pomme */
    if (mon->position_pomme == NULL) {
        tmp = alloue_pomme(c.x, c.y);
        mon->position_pomme = tmp;
    }
    else {
        /* on verifie que la pomme ne va pas se poser sur le serpent ou sur une autre pomme */ 
        while ((case_dans_serpent(mon->serpent, c) == 1) || (case_dans_pomme(mon->position_pomme, c) == 1) || (case_dans_pomme(mon->position_poison, c) == 1)
                    || (case_dans_pomme(mon->position_double, c) == 1)) {
            c.x = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.x;
            c.y = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.y;
        }
        /* on rajoute la pomme a la fin de la liste */
        tmp = alloue_pomme(c.x, c.y);
        courant = mon->position_pomme;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }  
        courant->suivant = tmp;
    }
}

/*ajouter une pomme empoisonnee */
void monde_ajouter_poison(Monde *mon) {
    L_pomme courant;
    L_pomme tmp;
    Case c;
    /* on prend une case aleatoirement */
    c.x = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.x;
    c.y = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.y;
    /* si la liste des pommes est vide on rajoute la pomme */
    if (mon->position_poison == NULL) {
        tmp = alloue_pomme(c.x, c.y);
        mon->position_poison = tmp;
    }
    else {
        /* on verifie que la pomme ne va pas se poser sur le serpent ou sur une autre pomme */ 
        while ((case_dans_serpent(mon->serpent, c) == 1) || (case_dans_pomme(mon->position_pomme, c) == 1) || (case_dans_pomme(mon->position_poison, c) == 1)
                    || (case_dans_pomme(mon->position_double, c) == 1)) {
            c.x = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.x;
            c.y = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.y;
        }
        /* on rajoute la pomme a la fin de la liste */
        tmp = alloue_pomme(c.x, c.y);
        courant = mon->position_poison;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }  
        courant->suivant = tmp;
    }
}
/* ajouter une pomme qui rajoute 2 points au score */
void monde_ajouter_double(Monde *mon) {
    L_pomme courant;
    L_pomme tmp;
    Case c;
    /* on prend une case aleatoirement */
    c.x = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.x;
    c.y = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.y;
    /* si la liste des pommes est vide on rajoute la pomme */
    if (mon->position_double == NULL) {
        tmp = alloue_pomme(c.x, c.y);
        mon->position_double = tmp;
    }
    else {
        /* on verifie que la pomme ne va pas se poser sur le serpent ou sur une autre pomme */ 
        while ((case_dans_serpent(mon->serpent, c) == 1) || (case_dans_pomme(mon->position_pomme, c) == 1) || (case_dans_pomme(mon->position_poison, c) == 1)
                    || (case_dans_pomme(mon->position_double, c) == 1)) {
            c.x = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.x;
            c.y = pomme_aleatoire(mon->lignes, mon->colonnes).pomme.y;
        }
        /* on rajoute la pomme a la fin de la liste */
        tmp = alloue_pomme(c.x, c.y);
        courant = mon->position_double;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }  
        courant->suivant = tmp;
    }
}

/* tester si la case c existe deja dans la liste du serpent */
int case_dans_serpent(Serpent serpent, Case c) {
    Liste tmp;
    tmp = serpent.tete;
    while (tmp != NULL) {
        if (tmp->coordonnees.x == c.x && tmp->coordonnees.y == c.y)
            return 1;
        tmp = tmp->suivant;
    }
    return 0;
}
/* tester si la case c existe deja dans la liste des pommes */
int case_dans_pomme(L_pomme liste_pomme, Case c) {
    L_pomme tmp;
    tmp = liste_pomme;
    while (tmp != NULL) {
        if (tmp->debut.pomme.x == c.x && tmp->debut.pomme.y == c.y)
            return 1;
        tmp = tmp->suivant;
    }
    return 0;
}
/* fonction qui initialise les champs du Monde et le renvoie */
Monde monde_initialiser(int nb_lignes, int nb_colonnes, int taille_serpent, int nb_pommes) {
    Monde tmp;
    int i;
    tmp.lignes = nb_lignes;
    tmp.colonnes = nb_colonnes;
    tmp.nb_pomme_mange = 0;
    tmp.etat = 0;
    tmp.position_pomme = NULL;
    tmp.position_poison = NULL;
    tmp.position_double = NULL;
    tmp.serpent = serpent_initialiser(nb_lignes, nb_colonnes, taille_serpent);
    for (i = 0 ; i < nb_pommes ; i++)
        monde_ajouter_pomme(&tmp);
    monde_ajouter_poison(&tmp);
    return tmp;
}
/* verifie si le serpent est mort  renvoie 1 si oui, 2 si l'utilisateur a gagne et 0 sinon */
int monde_est_mort_serpent(Monde mon) {
    Case prochaine_case;
    prochaine_case = serpent_case_visee(mon.serpent);
    /* Si la prochaine position de la tete du serpent est une case de son corps */
    if (case_dans_serpent(mon.serpent, prochaine_case) == 1) {
        beep();
        return 1;
    }
    /* Si la prochaine position de la tete du serpent est en dehors du quadrillage */
    if (prochaine_case.x < 0 || prochaine_case.y < 0 ){
        beep();
        return 1;
    }
    if (prochaine_case.x > mon.colonnes - 1 || prochaine_case.y > mon.lignes - 1) {
        beep();
        return 1;
    }
    /* Si le serpent a mangé une pomme empoisonnée */
    if (case_dans_pomme(mon.position_poison, prochaine_case) == 1){
        beep();
        return 1;
    }
    /* Si le serpent fait la taille du quadrillage */
    if (mon.serpent.taille == (mon.lignes * mon.colonnes))
        return 2;
    return 0;
}

/* fonction qui change la position du serpent et mange les pommes*/
void monde_evoluer_serpent(Monde *mon) {
    Case prochaine_case;
    prochaine_case = serpent_case_visee(mon->serpent);
    /* Si le serpent va manger une pomme normale */
    if (supprime_pomme(&mon->position_pomme, prochaine_case.x, prochaine_case.y) == 1) {
        /* S'il n'y a pas de nouvel emplacement libre pour créer une nouvelle pomme, on supprime des pommes empoisonnées */
        while ((taille_poison(mon->position_poison) + mon->nb_pomme_mange) >= (mon->lignes * mon->colonnes))
            supprime_poison(&mon->position_poison);
        /* Affichage du serpent après son déplacement */
        ajoute_en_tete(&(mon->serpent.tete), prochaine_case);
        /* Actualisation du nombre de pommes mangées et de la taille du serpent */
        (mon->nb_pomme_mange)++;
        beep();
        printf("\a");
        mon->serpent.taille++;
        /* Ajout d'une nouvelle pomme normale ou qui vaut 2 points */
        if ((mon->nb_pomme_mange % 7) == 3)
            monde_ajouter_double(mon);
        else
            monde_ajouter_pomme(mon);
        /* Toutes les 10 pommes mangées, on rajoute une pomme empoisonnée */
        if ((mon->nb_pomme_mange % 10) == 0)
            monde_ajouter_poison(mon);
        return;
    }
    /* Si le serpent va manger une pomme qui vaut 2 points */
    if (supprime_pomme(&mon->position_double, prochaine_case.x, prochaine_case.y) == 1) {
        /* S'il n'y a pas de nouvel emplacement libre pour créer une nouvelle pomme, on supprime des pommes empoisonnées */
        while ((taille_poison(mon->position_poison) + mon->nb_pomme_mange) >= (mon->lignes * mon->colonnes))
            supprime_poison(&mon->position_poison);
        /* Affichage du serpent après son déplacement */
        ajoute_en_tete(&(mon->serpent.tete), prochaine_case);
        /* Actualisation du nombre de pommes mangées et de la taille du serpent */
        (mon->nb_pomme_mange) += 2;
        beep();
        mon->serpent.taille++;
        /* Ajout d'une nouvelle pomme normale ou qui vaut 2 points */
        if ((mon->nb_pomme_mange % 7) == 3)
            monde_ajouter_double(mon);
        else
            monde_ajouter_pomme(mon);
        /* Toutes les 10 pommes mangées, on rajoute une pomme empoisonnée */
        if ((mon->nb_pomme_mange % 10) == 0)
            monde_ajouter_poison(mon);
        return;
    }
    /* Actualisation du serpent après son déplacement */
    supprime_derniere_case(&(mon->serpent.tete));
    ajoute_en_tete(&(mon->serpent.tete), prochaine_case);
}

