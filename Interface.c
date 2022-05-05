#include "Interface.h"

/* affichage du quadrillage */
void interface_afficher_quadrillage(Monde mon) {
    int i, j;
    for (i = 0 ; i < mon.lignes ; i++) {
        move(i, 0);
        for (j = 0 ; j < mon.colonnes ; j++) {
            /* on alterne entre 2 couleurs */
            if ((i + j) % 2 == 0) {
                attron(COLOR_PAIR(1));
                printw(" ");
                attroff(COLOR_PAIR(1));
            }
            else {
                attron(COLOR_PAIR(5));
                printw(" ");
                attroff(COLOR_PAIR(5));
            }
        }
    }
}

/* affichage d'une pomme */ 
void interface_afficher_pomme(Pomme pom) {
    attron(COLOR_PAIR(2));
    mvprintw(pom.pomme.y, pom.pomme.x, " ");
    attroff(COLOR_PAIR(2));
    refresh();
    refresh();
}

/* affichage d'une pomme empoisonnee en une couleur differente */
void interface_afficher_poison(Pomme pom) {
    attron(COLOR_PAIR(6));
    mvprintw(pom.pomme.y, pom.pomme.x, " ");
    attroff(COLOR_PAIR(6));
    refresh();
    refresh();
}

/*afficher une pomme avec le numero 2 au centre pour
 * identifier les pommes qui rajoutent 2 points au score */
void interface_afficher_double(Pomme pom) {
    attron(COLOR_PAIR(2));
    mvprintw(pom.pomme.y, pom.pomme.x, "2");
    attroff(COLOR_PAIR(2));
    refresh();
    refresh();
}

/* affichage du serpent */
void interface_afficher_serpent (Serpent ser) {
    Liste tmp;
    /* on affiche la tete de la liste qui represente la tete du serpent */
    attron(COLOR_PAIR(3));
    mvprintw(ser.tete->coordonnees.y, ser.tete->coordonnees.x, " ");
    attroff(COLOR_PAIR(3));
    refresh();
    /* on parcourt la liste */
    tmp = ser.tete->suivant;
    while (tmp) {
        /* et on affiche chaque cellule du corps */
        attron(COLOR_PAIR(4));
        mvprintw(tmp->coordonnees.y, tmp->coordonnees.x, " ");
        refresh();
        attroff(COLOR_PAIR(4));
        tmp = tmp->suivant;
    }
    refresh();
}

/* affichage du monde en faisant appel aux fonctions d'affichage de chaque element */
void interface_afficher_monde(Monde mon) {
    L_pomme tmp;
    /* Affichage du quadrillage */
    interface_afficher_quadrillage(mon);
    /* Affichage du serpent */
    interface_afficher_serpent(mon.serpent);
    /* Affichage des pommes */
    tmp = mon.position_pomme;
    while (tmp != NULL) {
        interface_afficher_pomme(tmp->debut);
        tmp = tmp->suivant;
    }
    /* Affichage des pommes empoisonnées */
    tmp = mon.position_poison;
    while (tmp != NULL) {
        interface_afficher_poison(tmp->debut);
        tmp = tmp->suivant;
    }
    /* Affichage des pommes qui valent 2 points */
    tmp = mon.position_double;
    while (tmp != NULL) {
        interface_afficher_double(tmp->debut);
        tmp = tmp->suivant;
    }
    /* Affichage du score */
    mvprintw(mon.lignes / 2, mon.colonnes + 2, "Nombre de pommes mangées : %d", mon.nb_pomme_mange);
    refresh();
}
/* changer les directions et mettre le jeu en pause */
void interface_piloter(Monde *mon) {
    int touche;
    /* on prend une touche */
    touche = getch();
    switch (touche) {
    /* vers le haut */ 
    case 'z':
        mon->serpent.direction = NORD;
        break;
    /* vers le bas */
    case 's':
        mon->serpent.direction = SUD;
        break;
    /* vers la droite */ 
    case 'd':
        mon->serpent.direction = EST;
        break;
    /* vers la gauche */
    case 'q':
        mon->serpent.direction = OUEST;
        break;
    /* mettre le jeu en pause / reprendre */
    case 'p':
        mon->etat = (mon->etat + 1) % 2;
        break;
    
    default:
        break;
    }
}