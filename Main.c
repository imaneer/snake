#include "Monde.h"
#include "Interface.h"
#include <unistd.h>
#include <string.h>


int main() {


    Monde monde;
    char chaine[50];
    int valeur;
    int lignes;
    int colonnes;
    int nb_pommes;
    int taille_serpent;
    int duree_tour;
    FILE* fichier;

    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_GREEN);  /* plateau */
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); /* pomme */
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA); /* tete du snake */
    init_pair(4, COLOR_BLACK, COLOR_BLUE); /* corps du snake */
    init_pair(6, COLOR_WHITE, COLOR_RED); /* rouge pour les pommes empoisonnees */

    lignes = 0;
    colonnes = 0;
    nb_pommes = 0;
    taille_serpent = 0;
    duree_tour = 0;
    /* on ouvre le fichier Serpent.ini qui contient les donnees du jeu (taille, nb_pomme...) */
    fichier = fopen("Serpent.ini", "r");
    /* verification du fichier */
    if (fichier == NULL) {
        printf("Ouverture fichier impossible\n");
        exit(EXIT_FAILURE);
    }
    /* on recupere les donnees et on les affectes a des variables */
    while(fscanf(fichier, "%s = %d", chaine, &valeur) == 2) {
        if (strcmp(chaine, "largeur") == 0)
            colonnes = valeur;
        if (strcmp(chaine, "hauteur") == 0)
            lignes = valeur;
        if (strcmp(chaine, "nombre_pommes") == 0)
            nb_pommes = valeur;
        if (strcmp(chaine, "taille_serpent") == 0)
            taille_serpent = valeur;
        if (strcmp(chaine, "duree_tour") == 0)
            duree_tour = valeur;
        
    }
    /* initialisation du monde par les valeurs du fichiers */
    monde = monde_initialiser(colonnes, lignes, taille_serpent, nb_pommes);
    /* on initialise l'etat a 0 pour qu'on ne commence pas directement apres l'execution du programme */
    monde.etat = 0;
    /* tant que le snake est vivant */
    while (monde_est_mort_serpent(monde) == 0) {
        clear ();
        /* on affiche le monde */
        interface_afficher_monde(monde);
        refresh();
        /* on le bouge seulement si etat est differnt de 0 
         * car si etat = 0 alors l'utilisateur a mis le jeu en pause */
        if (monde.etat != 0){
            monde_evoluer_serpent(&monde);
            beep(); /* quand il bouge on mets un son */
        }
        clear ();
        /* mettre a jour l'affichage */
        interface_afficher_monde(monde);
        refresh();
        /* changer les directions ou mettre le jeu en pause 
         *en utilisant les touches du clavier */
        interface_piloter(&monde);
        /* attendre quelques instants */
        usleep(duree_tour);
    }
    clear();
    
    /* si la taille du serpent = la taille du quadrillage l'utilisateur a gagné */
    if (monde_est_mort_serpent(monde) == 2) {
        mvprintw((LINES - 1) / 2, (COLS - 1) / 2 - strlen("Vous avez gagné"), "Vous avez gagné");
        mvprintw((LINES - 1) / 2 + 1, (COLS - 1) / 2 - strlen("Score final :  ") / 2, "Score final : %d", monde.nb_pomme_mange);
        refresh();
    }

    /* dans tous les autres cas il a perdu */
    else {
        mvprintw((LINES - 1) / 2, (COLS - 1) / 2 - strlen("Vous avez perdu") / 2, "Vous avez perdu");
        mvprintw((LINES - 1) / 2 + 1, (COLS - 1) / 2 - strlen("Score final :  ") / 2, "Score final : %d", monde.nb_pomme_mange);
        refresh();
    }
    /* on libère les listes chainnees */ 
    liberer_Liste_pomme(&monde.position_pomme);
    liberer_Liste_pomme(&monde.position_poison);
    liberer_Liste_pomme(&monde.position_double);
    liberer_Liste(&monde.serpent.tete);

    sleep(2);
    refresh();
    sleep(2);
    endwin();
    return 0;
}
