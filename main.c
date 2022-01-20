#include "graphique.h"

/**
 * @brief 
 * Fonction qui free
 * toute la structure 
 * jeux à la fin de la partie
 * @param jeux 
 */
void free_tab(Game * jeux){

    Enemy * mechant = jeux -> enemy;
    Enemy * temp_E = NULL;
    Kind * gentil = jeux -> kind; 
    Kind * temp_G = NULL;
    int nb_t = 1;

    while (mechant != NULL){
        temp_E = mechant;
        mechant = mechant -> next;
        free(temp_E);
    }
    while (gentil != NULL){
        nb_t ++;
        temp_G = gentil;
        gentil = gentil -> next;
        free(temp_G);
    }
    temp_E = mechant;
    temp_G = gentil;
    if (temp_E != NULL)
        free(temp_E);
    if (temp_G != NULL)
        free(temp_G);

}

// MAIN

/**
 * @brief 
 * Fonction qui fait
 * la fonction ASCII
 * 
 */
void ASCII(void){

    Game jeux; // Initialisation de la partie.

    jeux.kind = NULL;
    jeux.enemy = NULL;
    jeux.money = 0;
    jeux.turn = 0;
    jeux.nb_enemy = 0;
    jeux.nb_turret = 0;

    int jeu = 1;

    choixlvl(&jeux);

    printf("\nL'argent disponible pour ce niveau est de : %d Kamas\n", jeux.money);
    printf("%d ennemis sont en approches.\n", jeux.nb_enemy);

    create_db(&jeux);

    end(5);

    visualise_enemy(&jeux);

    sleep(1);

    printf("\e[1;1H\e[2J");

    while(lire_turret(&jeux) != 6);

    while (jeu == 1){

        jeux.turn ++;

            affiche_ascii(&jeux);
            end(2);

            walk_enemy(&jeux);

            damage_enemy(&jeux);
            damage_kind(&jeux);

            if (jeux.nb_turret > 0)
                death_turret(&jeux);
            death_enemy(&jeux);

            if (loose_enemy(&jeux) == 1 || loose_kind(&jeux) == 1)
                jeu = 0;
        sleep(1);
    }
    affiche_ascii(&jeux);
    loose_enemy(&jeux);
    loose_kind(&jeux);
    free_tab(&jeux);
}

/**
 * @brief 
 * Fonction qui fait 
 * la partie graphique
 * 
 */
void graphique(void){

    Game jeux; // Initialisation de la partie.

    jeux.kind = NULL;
    jeux.enemy = NULL;
    jeux.money = 0;
    jeux.turn = 0;
    jeux.nb_enemy = 0;
    jeux.nb_turret = 0;
    

    MLV_create_window("Dofus Tower Defense", "DTD", 1600, 900);
    affiche_accueil(&jeux);
    affiche_game(&jeux);

    MLV_free_window();
    free_tab(&jeux);

}

int main(int argc, char * argv[]){

    int i = 1;

    if (argc > 1){
        if (argv[1][0] == '-'){
            while (argv[1][i] != '\0'){
                if (argv[1][i] == 'g'){
                    graphique();
                    break;
                }else{
                    ASCII();
                    break;
                }
            }
        }else
            printf("Format -a (mode ASCII) / -g (mode graphique)\n");
    }else
        printf("Format -a (mode ASCII) / -g (mode graphique)\n");

    return 0;
}