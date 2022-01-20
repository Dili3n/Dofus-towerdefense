#include "kind.h"

/**
 * @brief 
 * Fonction qui sert à détecter si 
 * les gentils ont perdu ou non.
 * @param jeux 
 * Structure jeu...
 * @return int 
 * 1 : PERDU
 * 0 : pas encore perdu
 */
int loose_kind(Game * jeux){

    Enemy * current = jeux -> enemy;

    while (current != NULL){

        if(current -> position <= 1){
            printf("Vous avez été vaincu par la vague d'ennemie !\n");
            return 1;
        }
        current = current -> next;
    }
    return 0;
}

/**
 * @brief 
 * Fonction qui sert à détecter si 
 * les gentils ont gagné ou non.
 * @param jeux 
 * Structure jeu...
 * @return int 
 * 1 : GAGNE
 * 0 : pas encore gagné
 */
int loose_enemy(Game * jeux){

    if (jeux -> nb_enemy <= 0){
        printf("Vous avez réussi à vaincre la vague d'ennemie !\n");
        return 1;
    }
    return 0;
}

/**
 * @brief 
 * Fonction d'affichage du jeu en
 * mode ascii, en parcourant toute
 * la structure jeu.
 * @param jeux 
 * structure utilisée pour parcourir
 * les coordonnées des pièces.
 */
void affiche_ascii(Game * jeux){
    int i, j, nb_t = 0;
    Kind * curr_t = jeux -> kind;
    Enemy * curr_e = jeux -> enemy;
    printf("\e[1;1H\e[2J");
    printf("Turn N° %d\n\n", jeux -> turn);
    while (curr_e != NULL && curr_e -> position > colonne){
        curr_e = curr_e -> next;
    }
    for (i = 1; i <= ligne; i++){
        printf("%d |", i);
        for(j = 1; j <= colonne; j++){
            if (nb_t < jeux -> nb_turret && curr_t -> line == i && curr_t -> position == j){
                printf(" %d%c", curr_t -> life, curr_t -> type);
                nb_t ++;
                curr_t = curr_t -> next;
            } else if (curr_e != NULL){
                if (curr_e -> position <= colonne){
                    if (curr_e -> line == i && curr_e -> position == j){
                        printf(" %d%c", curr_e -> life, curr_e->type);
                        curr_e = curr_e -> next;
                        while (curr_e != NULL && curr_e -> position > colonne){
                            curr_e = curr_e -> next;
                        }
                    } else
                        printf("   ");
                } else
                    printf("   ");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }        
}

/**
 * @brief 
 * Fonction qui permet de
 * prévisualiser la vague d'ennemi 
 * en ASCII.
 * @param jeux 
 * Structure qui permet de lire
 * les coordonnées
 */
void visualise_enemy(Game * jeux){

    Enemy * current = jeux -> enemy;
    int i = 1, j = 1;
    printf("\e[1;1H\e[2J");
    printf("Prévisualisation\n");

    for (i = 1; i <= ligne; i++){
        printf("\n%d| ", i);
        for (j = 1; j <= 9; j++){
            if (current != NULL && current -> line == i && current -> turn == j){
                printf(" %d%c", current -> life, current -> type);
                current = current -> next;
            } else
                printf("   ");
        }
    }  
}