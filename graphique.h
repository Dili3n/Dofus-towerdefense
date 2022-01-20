#include "sub/divers.h"
#include <MLV/MLV_all.h>

#define x_marge 295
#define y_marge 225

// Prototype des fonctions utilisés dans graphique.h
void affiche_regle(Game * jeux);
void affiche_accueil(Game * jeux);
int affiche_game(Game * jeux);
void affiche_niveau(Game * jeux);
void retour_menu(Game * jeux);
void detection(Game * jeux);
void free_tab(Game * jeux);
void graphique();

// FONCTIONS 


/**
 * @brief 
 * Fonction qui permet de prévisualiser 
 * graphiquement la vague de monstre.
 *    
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void do_the_wave(Game * jeux){

    Enemy * current = jeux -> enemy;

    MLV_Image * jeu = MLV_load_image("assets/jeu2.png");

    MLV_Image * S = MLV_load_image("assets/mobs/1.png"); // Monstre : Craqueleur
    MLV_Image * A = MLV_load_image("assets/mobs/2.png"); // Monstre : Champ champ
    MLV_Image * B = MLV_load_image("assets/mobs/3.png"); // Monstre : Bouftou
    MLV_Image * C = MLV_load_image("assets/mobs/4.png"); // Monstre : Tofu
    MLV_Image * D = MLV_load_image("assets/mobs/5.png"); // Monstre : Piou

    MLV_draw_image(jeu, 0, 0);
    detection(jeux);

    while (current != NULL){

        if (current -> type == 'S')
            MLV_draw_image(S, x_marge + (current -> turn - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
        else if (current -> type == 'A')
            MLV_draw_image(A, x_marge + (current -> turn - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
        else if (current -> type == 'B')
            MLV_draw_image(B, x_marge + (current -> turn - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
        else if (current -> type == 'C')
            MLV_draw_image(C, x_marge + (current -> turn - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
        else if (current -> type == 'D')
            MLV_draw_image(D, x_marge + (current -> turn - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
        
        MLV_actualise_window();
        current = current -> next;
    }

    sleep(3);
    affiche_game(jeux);

}


/**
 * @brief 
 * Fonction sert à retourner au
 * menu principal lorsque l'on clic
 * sur la croix en haut à droite.
 *   
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void retour_menu(Game * jeux){
    int x,y;
    MLV_wait_mouse(&x, &y);
    if (1540 <= x && x <= 1590 && 5 <= y  && y <= 55){ // Croix en haut à droite
        do{
            MLV_free_window();
            MLV_free_audio();
            graphique();
        } while(1);
    }
}


/**
 * @brief 
 * Fonction qui va afficher graphiquement
 * l'interface de choix de niveau et
 * permettre de selectionner le niveau
 * souhaité en un clic.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void affiche_niveau(Game * jeux){

    int x,y;
    MLV_Image * jeu = MLV_load_image("assets/jeu.png"); // Image de l'interface du jeu
    MLV_Image * choix_niv = MLV_load_image("assets/choix_niv.png"); // Image de l'interface de choix de niveau

    FILE * fichier = NULL;
    char nom_fichier[128] = "";
    



    do{
            MLV_draw_image(choix_niv, 0, 0);
            MLV_actualise_window();
            MLV_wait_mouse(&x, &y);
            
            if (1540 <= x && x <= 1590 && 5 <= y  && y <= 55){ // // Croix orange en haut à droite
                MLV_free_window();
                MLV_free_audio();
                graphique();
            }

            if (582 <= x && x <= 1027 && 125 <= y  && y <= 155){ // Bouton Niveau 1
                    MLV_draw_image(jeu, 0, 0);
                    MLV_actualise_window();
                    snprintf(nom_fichier, sizeof nom_fichier, "levels/level_1.txt");
                    fichier = fopen(nom_fichier,"r");
                    init_enemy(fichier, jeux);
                    fclose(fichier);
                    affiche_game(jeux);
            }

            if (580 <= x && x <= 1027 && 282 <= y  && y <= 312){ // Bouton Niveau 50
                    MLV_draw_image(jeu, 0, 0);
                    MLV_actualise_window();   
                    snprintf(nom_fichier, sizeof nom_fichier, "levels/level_2.txt");
                    fichier = fopen(nom_fichier,"r");
                    init_enemy(fichier, jeux);
                    fclose(fichier);
                    affiche_game(jeux);
            }

            if (580 <= x && x <= 1027 && 428 <= y  && y <= 458){ // Bouton Niveau 100
                    MLV_draw_image(jeu, 0, 0);
                    MLV_actualise_window();     
                    snprintf(nom_fichier, sizeof nom_fichier, "levels/level_3.txt");
                    fichier = fopen(nom_fichier,"r");
                    init_enemy(fichier, jeux);
                    fclose(fichier);
                    affiche_game(jeux);
            }

            if (582 <= x && x <= 1027 && 580 <= y  && y <= 610){ // Bouton Niveau 150
                    MLV_draw_image(jeu, 0, 0);
                    MLV_actualise_window();  
                    snprintf(nom_fichier, sizeof nom_fichier, "levels/level_4.txt");
                    fichier = fopen(nom_fichier,"r");
                    init_enemy(fichier, jeux);
                    fclose(fichier);
                    affiche_game(jeux);
            }

            if (582 <= x && x <= 1027 && 727 <= y  && y <= 757){ // Bouton Niveau 200
                    MLV_draw_image(jeu, 0, 0);
                    MLV_actualise_window();
                    snprintf(nom_fichier, sizeof nom_fichier, "levels/level_5.txt");
                    fichier = fopen(nom_fichier,"r");
                    init_enemy(fichier, jeux);
                    fclose(fichier);
                    affiche_game(jeux);
            }else{
                affiche_niveau(jeux);
            }

        
    } while(1);
}


/**
 * @brief 
 * Fonction purement graphique qui
 * affiche le menu des règles et
 * permet à l'utilisateur de voir les règles
 * et les capacités de tourelles.
 *  
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void affiche_regle(Game * jeux){
    int x, y;
    MLV_Image * regle2 = MLV_load_image("assets/regle2.png"); // Image de la page deux des règles
    MLV_Image * regle = MLV_load_image("assets/regle.png"); // Image de la page une des règles
    MLV_Image * tourelle = MLV_load_image("assets/info_tourelles.png"); // Image des informations sur les tourelles

    do{

        MLV_draw_image(regle, 0, 0);  
        MLV_actualise_window(); 

        MLV_wait_mouse(&x, &y);
        if (1210 <= x && x <= 1260 && 50 <= y  && y <= 105){ // Flèche orange en haut à droite
            MLV_free_window();
            MLV_free_audio();
            graphique();
        }
        
        if (380 <= x && x <= 1230 && 690 <= y  && y <= 725){ // Continuer la discussion
            do{
                MLV_draw_image(regle2, 0, 0);
                MLV_actualise_window();

                MLV_wait_mouse(&x, &y);
                if ((380 <= x && x <= 1230 && 690 <= y  && y <= 725) || (1210 <= x && x <= 1260 && 50 <= y  && y <= 105)){ // Retourner au menu principal
                    MLV_free_window();
                    MLV_free_audio();
                    graphique();
                } else if (380 <= x && x <= 1230 && 730 <= y  && y <= 765){ // Image capacité des tourelles
                        MLV_draw_image(tourelle, 0, 0); 
                        MLV_actualise_window();
                        retour_menu(jeux);
                }

            } while(1);
        }

        if (380 <= x && x <= 1230 && 730 <= y  && y <= 765){ // Image capacité des tourelles
                MLV_draw_image(tourelle, 0, 0);  
                MLV_actualise_window();
                retour_menu(jeux);
        }
        
    } while(1);
    
}


/**
 * @brief 
 * Fonction qui va afficher graphiquement
 * l'interface du menu principal et jouer
 * la musique du jeu.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void affiche_accueil(Game * jeux){
    int x, y;
    MLV_Image * background = MLV_load_image("assets/bg.png"); // Menu principal
    MLV_init_audio();
    MLV_Music * background_sound = MLV_load_music("assets/musique/dofus.ogg"); // Musique de fond
    MLV_Image * credit = MLV_load_image("assets/credit.png"); // Image crédit
    
    MLV_draw_image(background, 0, 0);
    MLV_play_music(background_sound, 0.2, -1);
    MLV_actualise_window();

    do{
        MLV_wait_mouse(&x, &y);
        if (690 <= x && x <= 910 && 780 <= y  && y <= 845){ // Bouton JOUER
            affiche_niveau(jeux);

        }

        if (280 <= x && x <= 450 && 800 <= y  && y <= 850){ // Bouton REGLE
            affiche_regle(jeux);       
        }

        if (1170 <= x && x <= 1440 && 795 <= y  && y <= 845){ // Bouton CREDIT
                MLV_draw_image(credit, 0, 0);
                MLV_actualise_window();
                retour_menu(jeux);
        }
    } while(1);
}


/**
 * @brief 
 * Fonction qui va afficher graphiquement
 * les cercles où pourront avancés les monstres
 * et être pssés les tourelles.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void detection(Game * jeux){

    int i, j;

    for (i = 0; i < colonne ; i++){
        for (j= 0; j < ligne ; j++){
                MLV_draw_filled_circle(i *55 + x_marge, j*100 + y_marge, 5,  MLV_COLOR_ORANGE3);      
        }
    }
}


/**
 * @brief 
 * Fonction permettant de récupérer
 * la coordonnée y du premier cercle
 * ou pourront avancés les monstres et
 * être posés les tourelles.
 */
int recup_line(int y){

    int line = 0;
    line = ((y - y_marge + 30) / 100) + 1;
    return line;

}


/**
 * @brief 
 * Fonction permettant de récupérer 
 * la coordonnée x du premier cercle
 * où pourront avancés les monstres et
 * être posés les tourelles.
 */
int recup_column(int x){

    int column = 0;
    column = ((x - y_marge) / 55);
    return column;

}


/**
 * @brief 
 * Fonction permettant d'initialiser
 * graphiquement les tourelles.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void affiche_turret(Game * jeux){

    Kind * current = jeux -> kind;

    MLV_Image * S = MLV_load_image("assets/turrets/5.png"); // Tourelle : Ecaflip
    MLV_Image * A = MLV_load_image("assets/turrets/4.png"); // Tourelle : Eniripsa
    MLV_Image * B = MLV_load_image("assets/turrets/3.png"); // Tourelle : Bloqueuse
    MLV_Image * C = MLV_load_image("assets/turrets/2.png"); // Tourelle : Xélor
    MLV_Image * D = MLV_load_image("assets/turrets/1.png"); // Tourelle : Crâ

    while(current != NULL){

    if (current -> type == 'S')
        MLV_draw_image(S, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'A')
        MLV_draw_image(A, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'B')
        MLV_draw_image(B, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'C')
        MLV_draw_image(C, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'D')
        MLV_draw_image(D, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    current = current -> next;
    }
}


/**
 * @brief 
 * Fonction permettant d'initialiser
 * graphiquement les monstres.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void affiche_enemy(Game * jeux){

    Enemy * current = jeux -> enemy;

    MLV_Image * S = MLV_load_image("assets/mobs/1.png");
    MLV_Image * A = MLV_load_image("assets/mobs/2.png");
    MLV_Image * B = MLV_load_image("assets/mobs/3.png");
    MLV_Image * C = MLV_load_image("assets/mobs/4.png");
    MLV_Image * D = MLV_load_image("assets/mobs/5.png");

    while(current != NULL){

    if (current -> type == 'S')
        MLV_draw_image(S, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'A')
        MLV_draw_image(A, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'B')
        MLV_draw_image(B, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'C')
        MLV_draw_image(C, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
    if (current -> type == 'D')
        MLV_draw_image(D, x_marge + (current -> position - 1) * 55 - 30, y_marge + (current -> line - 1) * 100 - 30);
        
    current = current -> next;
    }
}


/**
 * @brief
 * Fonction qui permet de pouvoir graphiquement,
 * de poser les tourelles sur les cercles 
 * prévu à cet effet.
 * 
 * @param numero 
 * numéro de l'image de la tourelle séléctionnée.
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 * @param x 
 * Coordonnée x de l'endroit où l'on souhaite
 * placer la tourelle.
 * @param y 
 * Coordonnée y de l'endroit où l'on souhaite
 * placer la tourelle.
 */
void create_turret(int numero, Game * jeux, int x, int y){
    char infoTurret[4] = "";
    char * turret[6] = {"0","25","15","20","30","50"};

    if (numero >= 1 && numero <= 5 && jeux -> money >= atoi(turret[numero])){
        int line = recup_line(y);
        int column = recup_column(x);
        if (PossibleTurret(line, column, jeux) == 1){
            jeux -> money -= atoi(turret[numero]);
            jeux -> nb_turret ++;

            infoTurret[0] = SetType(numero);
            infoTurret[1] = SetPrice(numero);

            init_turret(infoTurret, column, line, jeux);

            affiche_turret(jeux);
        }
    }
}


/**
 * @brief 
 * Fonction qui affiche les écrans de
 * victoire et défaite en cas de victoire
 * ou défaite et permettant de rejouer.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */

void gagner(Game * jeux){

    if (loose_enemy(jeux) == 1){
        MLV_Image * victoire = MLV_load_image("assets/victoire.png"); // Image victoire
        int x, y;
        MLV_draw_image(victoire, 0, 0);
        MLV_actualise_window();
        MLV_wait_mouse(&x, &y);
        do {
            if (620 <= x && x <= 955 && 170 <= y  && y <= 260){
                MLV_free_window();
                MLV_free_audio();
                graphique();
            }

        
            if (1540 <= x && x <= 1590 && 5 <= y  && y <= 55){
                MLV_free_window();
                MLV_free_audio();
                graphique();
            }
        }while(1);

    }
    else if (loose_kind(jeux) == 1){

        MLV_Image * defaite = MLV_load_image("assets/defaite.png"); // Image défaite
        int x, y;
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_image(defaite, 0, 0);
        MLV_actualise_window();
        MLV_wait_mouse(&x, &y);
        do {
            if (620 <= x && x <= 955 && 170 <= y  && y <= 260){
                MLV_free_window();
                MLV_free_audio();
                graphique();
            }

        
            if (1540 <= x && x <= 1590 && 5 <= y  && y <= 55){
                MLV_free_window();
                MLV_free_audio();
                graphique();
            }
        
        }while(1);

    }
}


/**
 * @brief 
 * Fonction affichant la barre de vie
 * des ennemis, variant en fonction
 * du nombre de point de vie du monstre.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void barre_vie_enemy(Game * jeux){

    Enemy * current = jeux -> enemy;

    while (current != NULL){

        if (current -> position <= colonne){

            if (current -> life > 0){
                MLV_draw_line(x_marge - 70 + (55 * current -> position),
                              y_marge + (100 * (current -> line - 1)) - 30,
                              x_marge - 30 + (55 * current -> position),
                            y_marge + (100 * (current -> line - 1)) - 30, MLV_COLOR_RED);
                MLV_draw_line(x_marge - 70 + (55 * current -> position),
                              y_marge + (100 * (current -> line - 1)) - 30,
                              x_marge - 50 + (55 * current -> position) + 20 * ((current -> life) / life_enemy(current -> type)),
                            y_marge + (100 * (current -> line - 1)) - 30, MLV_COLOR_ORANGE3);
                
            }
        }

        current = current -> next;
    }

}


/**
 * @brief 
 * Fonction affichant la barre de vie
 * des tourelles, variant en fonction
 * du nombre de point de vie de la tourellles.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void barre_vie_allie(Game * jeux){

    Kind * current = jeux -> kind;

    while (current != NULL){

        if (current -> position <= colonne){

            if (current -> life > 0){
                MLV_draw_line(x_marge - 70 + (55 * current -> position),
                              y_marge + (100 * (current -> line - 1)) + 40,
                              x_marge - 30 + (55 * current -> position),
                            y_marge + (100 * (current -> line - 1)) + 40, MLV_COLOR_RED);
                MLV_draw_line(x_marge - 70 + (55 * current -> position),
                              y_marge + (100 * (current -> line - 1)) + 40,
                              x_marge - 50 + (55 * current -> position) + 20 * ((current -> life) / life_kind(current -> type)),
                            y_marge + (100 * (current -> line - 1)) + 40, MLV_COLOR_GREEN);
                
            }
        }

        current = current -> next;
    }

}


/**
 * @brief 
 * Fonction permettant de lancer le
 * jeu lorsque l'on appuie sur le bouton 
 * PLAY.
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 */
void start_game(Game * jeux){

    int jeu = 1;
    MLV_Image * bg_jeu = MLV_load_image("assets/jeu.png");

    char argent[4] = "";
    MLV_draw_image(bg_jeu, 0, 0);
    detection(jeux);
    snprintf(argent, sizeof argent, "%d", jeux -> money);

    MLV_draw_text(120, 155, argent, MLV_COLOR_WHITE);
    
    affiche_turret(jeux);
    affiche_enemy(jeux);
    barre_vie_enemy(jeux);
    barre_vie_allie(jeux);

    MLV_actualise_window();
    

    while(jeu == 1){

        walk_enemy(jeux);


        damage_enemy(jeux);
        damage_kind(jeux);
        MLV_draw_image(bg_jeu, 0, 0);
        detection(jeux);
        snprintf(argent, sizeof argent, "%d", jeux -> money);

        MLV_draw_text(120, 155, argent, MLV_COLOR_WHITE);
        
        affiche_turret(jeux);
        affiche_enemy(jeux);
        barre_vie_enemy(jeux);
        barre_vie_allie(jeux);
        MLV_actualise_window();
        sleep(1);

        if (jeux -> nb_turret > 0)
            death_turret(jeux);
        death_enemy(jeux);
        MLV_actualise_window();


        char argent[4] = "";
        MLV_draw_image(bg_jeu, 0, 0);
        detection(jeux);
        snprintf(argent, sizeof argent, "%d", jeux -> money);

        MLV_draw_text(120, 155, argent, MLV_COLOR_WHITE);
        
        affiche_turret(jeux);
        affiche_enemy(jeux);
        barre_vie_enemy(jeux);
        barre_vie_allie(jeux);
        MLV_actualise_window();


        if (loose_enemy(jeux) == 1 || loose_kind(jeux) == 1){
            jeu = 0;
            break;
        }
        
    sleep(1);
    }
    //free_tab(jeux);
    gagner(jeux);
}


/**
 * @brief 
 * Fonction permettant de séléctionner les tourelles,
 * faisant par al suite appel à create_turret pour 
 * les poser, et permettant de lancer par la suite le jeu
 * en faisant appele à start_game()
 * 
 * @param jeux 
 * La structure dans laquelle on stocke
 * l'information de l'argent.
 * @return int 
 * 0
 */
int affiche_game(Game * jeux){

    int x, y;
    int pose = 1;
    MLV_Image * background = MLV_load_image("assets/bg.png");
    MLV_Image * jeu = MLV_load_image("assets/jeu.png");
    

    do {
        MLV_clear_window(MLV_COLOR_BLACK);
        char argent[4] = "";
        MLV_draw_image(jeu, 0, 0);
        detection(jeux);
        affiche_turret(jeux);
        snprintf(argent, sizeof argent, "%d", jeux -> money);

        MLV_draw_text(120, 155, argent, MLV_COLOR_WHITE);
        MLV_actualise_window();
        pose = 1;
        MLV_wait_mouse(&x, &y);

        if (630 <= x && x <= 965 && 15 <= y  && y <= 115){
            start_game(jeux);
        }


        if (20 <= x && x <= 65 && 30 <= y  && y <= 75){ // Icone Crâ
                do{
                    MLV_wait_mouse(&x, &y);
                    int i, j;
                    for (i = 0; i < colonne ; i++){
                        for (j= 0; j < ligne ; j++){
                            if (x <= i*55 + 10 + x_marge && x >= i*55 - 10 + x_marge 
                                && y<= j*100 + 10 + y_marge && y>= j*100 -10 + y_marge){
                                pose = 0;
                                create_turret(1, jeux, x, y);
                                
                            }

                        }
                    }
                }while(pose);
        }

        if (70 <= x && x <= 115 && 30 <= y  && y <= 75){ // Icone Xélor
                do{
                    MLV_wait_mouse(&x, &y);
                    int i, j;
                    for (i = 0; i < colonne ; i++){
                        for (j= 0; j < ligne ; j++){
                            if (x <= i*55 + 10 + x_marge && x >= i*55 - 10 + x_marge 
                                && y<= j*100 + 10 + y_marge && y>= j*100 -10 + y_marge){
                                pose = 0;
                                create_turret(2, jeux, x, y);
                            }

                        }
                    }
                }while(pose);
        }

        if (120 <= x && x <= 165 && 30 <= y  && y <= 75){ // Icone Bloqueuse
                do{
                    MLV_wait_mouse(&x, &y);
                    int i, j;
                    for (i = 0; i < colonne ; i++){
                        for (j= 0; j < ligne ; j++){
                            if (x <= i*55 + 10 + x_marge && x >= i*55 - 10 + x_marge 
                                && y<= j*100 + 10 + y_marge && y>= j*100 -10 + y_marge){
                                pose = 0;
                                create_turret(3, jeux, x, y);
                            }

                        }
                    }
                }while(pose);
        }

        if (175 <= x && x <= 220 && 30 <= y  && y <= 75){ // Icone Eniripsa
                do{
                    MLV_wait_mouse(&x, &y);
                    int i, j;
                    for (i = 0; i < colonne ; i++){
                        for (j= 0; j < ligne ; j++){
                            if (x <= i*55 + 10 + x_marge && x >= i*55 - 10 + x_marge 
                                && y<= j*100 + 10 + y_marge && y>= j*100 -10 + y_marge){
                                pose = 0;
                                create_turret(4, jeux, x, y);
                            }

                        }
                    }
                }while(pose);
        }
        
        if (225 <= x && x <= 270 && 30 <= y  && y <= 75){ // Icone Ecaflip
                do{
                    MLV_wait_mouse(&x, &y);
                    int i, j;
                    for (i = 0; i < colonne ; i++){
                        for (j= 0; j < ligne ; j++){
                            if (x <= i*55 + 10 + x_marge && x >= i*55 - 10 + x_marge 
                                && y<= j*100 + 10 + y_marge && y>= j*100 -10 + y_marge){
                                pose = 0;
                                create_turret(5, jeux, x, y);
                            }

                        }
                    }
                }while(pose);
        }

        if (40 <= x && x <= 160 && 145 <= y  && y <= 180){ // Affichage de l'argent (kamas)
                MLV_draw_image(background, 0, 0);
                MLV_actualise_window();
        }

        if (1195 <= x && x <= 1455 && 15 <= y  && y <= 100){ // Bouton Voir la vague !
            do_the_wave(jeux);
        }

        if (1540 <= x && x <= 1590 && 5 <= y  && y <= 55){
            MLV_free_window();
            MLV_free_audio();
            graphique();
        }

    }while(1);
    return 0;
}