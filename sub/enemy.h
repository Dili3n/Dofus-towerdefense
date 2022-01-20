#include "struct.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


// FONCTIONS 

/**
 * @brief 
 * Fonction utilisé pour faire des sauts
 * de ligne, et éviter de faire des
 * \n à tout va.
 * 
 * @param n 
 * Nombre de ligne à sauter.
 */
void end(int n){

    int i;

    for (i = 0; i < n; i++)
        printf("\n");
}


/**
 * @brief 
 * Fonction qui initialise l'argent que le 
 * joueur aura au début de son aventure.
 * Cette somme sera initialisé dans la 
 * structure Game ("jeux").
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 * @param argent 
 * la chaine de caractère argent 
 * qu'on modifiera ensuite en int.
 */
void init_argent(Game * jeux ,char argent[4]){

    int thune = atoi(argent);
    jeux -> money = thune;

}

/**
 * @brief 
 * Création de la spped des ennemies
 * par rapport à son type
 * 
 * @return int 
 * retourne la speed de l'ennemie
 */
int speed_enemy(char type){

    if (type == 'S')
        return 1;
    if (type == 'C')
        return 3;
    return 2;
}

/**
 * @brief 
 * Création de la vie des ennemies
 * par rapport à son type
 * 
 * @return int 
 * retourne les points de vie de l'ennemie
 */
int life_enemy(int type){

    if (type == 'D' || type == 'B')
        return 3;
    else if (type == 'S')
        return 15;
    else if (type == 'C' || type == 'A')
        return 4;
    return 0;
}

/**
 * @brief
 * On "set" toutes les variables ennemies
 * transformation char en int,
 * on crée la vie et le speed de l'ennemie
 * par rapport à son type.
 * 
 * @param jeux 
 * Pour mettre les variables en jeu.
 * @param enemy 
 * Contient la variable tour, ligne et type.
 */ 
Enemy * set_enemy(Game * jeux, char enemy[4]){

    Enemy * lstEnemy = (Enemy *)malloc(sizeof(Enemy));
    memset(lstEnemy, 0, sizeof(Enemy));
    char type = enemy[2];

    lstEnemy -> turn = (atoi(&enemy[0])/10);
    lstEnemy -> position = lstEnemy -> turn + colonne;
    lstEnemy -> line = atoi(&enemy[1]);
    lstEnemy -> type = enemy[2];
    lstEnemy -> life = life_enemy(type);
    lstEnemy -> speed = speed_enemy(type);

    return lstEnemy;
}

/**
 * @brief 
 * Creation de la double liste chainée
 * qui ne nous sert pas plus que ça.
 * Mais qui a été faite
 * suite aux consignes données
 * 
 * @param jeux 
 */
void create_db(Game * jeux){

    Enemy * current = jeux -> enemy;

    while (current -> next != NULL){

        if (current -> line == current -> next -> line){

            current -> next_line = current -> next;
            current -> next -> prev_line = current;
        }
        current = current -> next;
    }

}

/**
 * @brief 
 * Fonction qui trie et définie les ennemis au
 * sein de la structure GAME.
 * @param jeux 
 * @param enemy 
 * Chaine de caractère dans laquelle on trouve
 * les infos d'un ennemi
 */
void alloue_enemy(Game * jeux, char enemy[4]){

    Enemy * add = set_enemy(jeux, enemy);

    if (add == NULL)
        return;

    Enemy * current = jeux -> enemy;

    if(jeux -> enemy == NULL){
        jeux -> enemy = add;
        return;
    }else{
        if (add -> line < current -> line){
            add -> next = jeux -> enemy;
            jeux -> enemy= add;
            return;
        }
        if (add -> line == current -> line){
            if (add -> turn < current -> turn){
                add -> next = jeux -> enemy;
                jeux -> enemy = add;
                return;

            }else if (add -> turn == current -> turn){
                if (add -> life < current -> life){  
                    add -> next = jeux -> enemy;
                    jeux -> enemy = add;
                    return;
                }
            }
        }
        while (current -> next != NULL){
            if (add -> line < current -> next -> line){
                add -> next = current -> next;
                current -> next = add;
                return;
            } else if (add -> line == current -> next -> line){
                if (add -> turn < current -> turn){
                add -> next = jeux -> enemy;
                jeux -> enemy = add;
                return;
                }else if (add -> turn == current -> turn){
                    if (add -> life < current -> life){
                        add -> next = jeux -> enemy;
                        jeux -> enemy = add;
                        return;
                    }
                }
            }
            current = current -> next;
        }
        current -> next = add;
        return;
    }
}


/**
 * @brief
 * Initalisation des coordonées de départ
 * ennemies. Pour cela nous allons parcourir
 * l'intégralité du fichier texte du niveau
 * correspondant.
 * 
 * @param fichier 
 * Le ficher texte qui contient les coordonnées.
 * @param jeux 
 * Pour remplir les coordonnées dans la structure
 * enemy.
 */
void init_enemy(FILE * fichier, Game * jeux){

    char carac_actuel = ' '; // Le caractère extrait du fichier.
    char argent[4] = ""; // Chaine de caractère qui définit l'argent du joueur.
    int indice_argent = 0; // Permet de compter l'argent.
    int indice_enemy = 0;
    int nb_enemy = 0; // Compte le nombre d'ennemis
    char enemy[4] = "";
    do{
        carac_actuel = fgetc(fichier);
        if (carac_actuel == EOF)
            break; //Pour ne pas refaire une dernière fois le (do)
        if (indice_argent <= 3){
            argent[indice_argent] = carac_actuel;
            indice_argent ++;
        }else{
            if(carac_actuel == '\n'){
                if (indice_enemy != 0){
                    alloue_enemy(jeux, enemy);
                }
                indice_enemy = 0;
                nb_enemy ++;
            }else{
                indice_enemy ++;
                // On décompose les différentes informations.
                if (indice_enemy == 1){
                    enemy[0] = carac_actuel;
                }else if(indice_enemy == 3){
                    enemy[1] = carac_actuel;
                }else if(indice_enemy == 5){
                    enemy[2] = carac_actuel;
                    enemy[3] = '\0';
                }
            }
        }
    }while(carac_actuel != EOF);
    // Argent disponible.
    argent[3] = '\0';
    init_argent(jeux, argent);
    //Nombre d'ennemis.
    jeux -> nb_enemy = nb_enemy;
}

/**
 * @brief 
 * Fonction qui permet de lire le niveau
 * sur lequel le joueur veut jouer.
 * Grace au "scanf".
 * Qui ouvre ensuite le fichier et vérifie
 * si ce niveau existe ou non.
 * @param jeux 
 * Utile pour les prochains appels de fonction.
 */
void choixlvl(Game * jeux){
    
        
    int level = 0;
    FILE * fichier = NULL;

    printf("Quel niveau voulez-vous faire ?\n\n");
    printf("1 - level_1\t2 - level_2\n3 - level_3\t4 - level_4\n5 - level_5\n\n");
    scanf("%d", &level);
    
    while (level > 5 || level < 1){
        printf("Quel niveau voulez-vous faire ?\n\n");
        printf("1 - level_1\t2 - level_2\n3 - level_3\t4 - level_4\n5 - level_5\n\n");
        scanf("%d", &level);
    }

    char nom_fichier[128] = "";
    snprintf(nom_fichier, sizeof nom_fichier, "levels/level_%d.txt", level);
    fichier = fopen(nom_fichier,"r");

    if (fichier == NULL){

        printf("Ce niveau n'existe pas. \n");
        choixlvl(jeux);
    
    }else{

        printf("Niveau trouvé !\n");
        
        init_enemy(fichier, jeux);
        fclose(fichier);
    }
}

/**
 * @brief 
 * Fonction qui vérifie si un ennemi est mort
 * et qui supprime l'ennemi de la structure
 * tout en faisant un dump.
 * 
 * @param jeux 
 */
void death_enemy(Game * jeux){

    Enemy * prec = NULL;
    Enemy * enem = jeux -> enemy;
    Enemy * temp = NULL;

    while (jeux -> enemy != NULL && jeux -> enemy -> life <= 0){
        temp = jeux -> enemy;
        jeux -> nb_enemy -= 1;
        jeux -> enemy = jeux -> enemy -> next; 
        enem = jeux -> enemy;
        free(temp);
    }

    while (enem != NULL){
        if (enem -> life <= 0){
            jeux -> nb_enemy -= 1;
            temp = enem;
            prec -> next = enem -> next;
            enem = prec->next;
            free(temp);
        } else {
            prec = enem;
            enem = enem -> next;
        }
    }
}

/**
 * @brief 
 * Fonction qui calcul les dégats pour
 * chacun des ennemis
 * 
 * @param type 
 * Le type de l'enemie
 * @return int 
 * Combien il fait de dégat.
 */
int calculate_damage_enemy(char type){

    srand(time(NULL));
    int dmg_craq = rand()%2 + 1;

    if (type == 'S'){
        if (dmg_craq == 1)
            return 5;
        else
            return 10; 
    }
    if (type == 'A')
        return 0;
    if (type == 'B')
        return 2;
    if (type == 'C')
        return 1;
    if (type == 'D')
        return 1;
    return 0;

}

/**
 * @brief 
 * Le sort de l'ennemi champchamp
 * qui heal les ennemis en sacrifiant
 * ses points de vie
 * 
 * @param enem 
 * @param jeux 
 */
void heal_champ(Enemy * enem, Game * jeux){

    Enemy * current = jeux -> enemy;

    while (current != NULL){

        if (current -> type != 'A'){
            if (current -> life < life_enemy(current -> type)){
                current -> life ++;
                enem -> life --;
            }
        }
        current = current -> next;
    }
}

/**
 * @brief 
 * Fonction qui modifie les points de vie
 * des tourelles, grace aux fonctions au dessus.
 * 
 * @param jeux 
 */
void damage_enemy(Game * jeux){

    Kind * turret = jeux -> kind;
    while(turret != NULL){
        Enemy * current = jeux -> enemy;
        while (current != NULL){
            if (current -> type == 'A'){
            heal_champ(current, jeux);
            }
            if (current -> line == turret -> line){
                if (current -> position -1 == turret -> position){
                    turret -> life -= calculate_damage_enemy(current -> type);
                }
            }
            current = current -> next;
        }
        turret = turret -> next;
    }
}

/**
 * @brief 
 * Fonction qui fait marcher les 
 * ennemis, selon leur vitesse
 * et si un autre ennemi ou une tourelle
 * bloque le passage.
 * @param jeux 
 */
void walk_enemy(Game * jeux){

    Enemy * current = jeux -> enemy;
    Enemy * previous = NULL;

    while (current != NULL){
        if (previous == NULL || previous -> line != current -> line){

            Kind * gentil = jeux -> kind;
            Kind * previousg = jeux -> kind;
            Kind * best_gentil = NULL;

            while (gentil != NULL){

                if (current -> line == gentil -> line){

                    if (best_gentil == NULL){
                        best_gentil = gentil;
                    }

                    if (previousg != NULL && current -> position - gentil -> position > 0 &&
                        current -> position - previousg -> position > 0 &&
                        current -> position - gentil -> position < current -> position - previousg -> position){
                            if (best_gentil -> position < current -> position &&
                                best_gentil -> position < gentil -> position)
                                   best_gentil = gentil;
                    } else if (previousg != NULL && current -> position - gentil -> position > 0 &&
                        current -> position - previousg -> position > 0 &&
                        current -> position - gentil -> position > current -> position - previousg -> position){
                            if (best_gentil -> position < current -> position &&
                                best_gentil -> position < previousg -> position)
                                   best_gentil = previousg;

                    }
                }
                previousg = gentil;
                gentil = gentil -> next;
            }
            if (best_gentil != NULL){
                int speed = 0;
                while (speed != current -> speed){
                    speed ++;
                    int nb_temp = 0;
                    Kind * temp = jeux -> kind;
                    while (temp != NULL){

                        if (current -> position -1 == temp -> position &&
                            current -> line == temp -> line){
                                nb_temp ++;
                        }

                        temp = temp -> next;
                    }
                    if (current -> position -1 != best_gentil -> position && nb_temp == 0){
                        current -> position --;
                    }
                }
            }else{
                current -> position -= current -> speed;
            }
            

        }
        else if (previous != NULL && previous -> line == current -> line){

            int speed = 0;
            while (speed != current -> speed){
                speed ++;
                Enemy * temp = jeux -> enemy;
                int nb_temp = 0;
                while(temp != NULL){
                    if (current -> position -1 == temp -> position &&
                        current -> line == temp -> line)
                        nb_temp ++;
                    temp = temp -> next; 
                }
                if (current -> position -1 != previous -> position && nb_temp == 0){
                        current -> position --;
                }
            }
        }
         
        previous = current;
        current = current -> next;
    }

}