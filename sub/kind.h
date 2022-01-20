#include "enemy.h"

/**
 * @brief 
 * Une fonction qui regarde si il
 * est possible de poser une tourelle 
 * à telles coordonées
 * 
 * @param line 
 * La ligne
 * @param column 
 * La colonne
 * @param jeux 
 * @return int 
 * Oui ou Non
 */
int PossibleTurret(int line, int column, Game * jeux){

    Kind * current = jeux -> kind;
    Enemy * current_2 = jeux -> enemy;
    int nb_e = 0;
    int nb_t = 0;

    if (1 <= line &&  line <= ligne){
        if (1 <= column && column <= colonne){

            // On vérifie qu'une tourelle ne soit pas posé sur une autre.
            while (jeux->nb_turret != nb_t){
                nb_t ++;
                if (current != NULL && current -> line == line){
                    if (current != NULL && current -> position == column){
                        return 0;
                    }
                }
                current = current -> next;
            }

            // On vérifie qu'une tourelle ne soit pas posé sur un ennemie.
            while (jeux->nb_enemy != nb_e){
                nb_e ++;
                if (current_2 -> line == line){
                        if (current_2 -> position == column){
                            return 0;
                    }
                }
                current_2 = current_2 -> next;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }
    return 1;
}

/**
 * @brief
 * Fonction
 * qui set le type des tourelles
 * selon le level des tourelles
 * choisi par l'utilisateur
 * 
 * @param level 
 * le niveau choisi par l'user
 * @return char 
 */
char SetType(int level){

    if (level == 1)
        return 'D';
    if (level == 2)
        return 'C';
    if (level == 3)
        return 'B';
    if (level == 4)
        return 'A';
    if (level == 5)
        return 'S';
    return 'Z';
}

/**
 * @brief
 * Fonction
 * qui set le prix des tourelles
 * selon le level des tourelles
 * choisi par l'utilisateur
 * 
 * @param level 
 * le niveau choisi par l'user
 * @return int 
 * le prix
 */
int SetPrice(int level){

    if (level == 1)
        return 50;
    if (level == 2)
        return 100;
    if (level == 3)
        return 100;
    if (level == 4)
        return 150;
    if (level == 5)
        return 250;
    return 0 ;
}

/**
 * @brief
 * Fonction qui set les dégats des tourelles
 * selon le type des tourelles
 * @param type
 * le niveau choisi par l'user
 * @return int
 * les dégats
 */
int SetDamage(char type){

    srand(time(NULL));
    int dmg_cra = rand()%2 + 1;
    int dmg_eca = rand()%5;

    if (type == 'D')
        return dmg_cra;
    if (type == 'C')
        return 1;
    if (type == 'B')
        return 0;
    if (type == 'A')
        return 0;
    if (type == 'S')
        return dmg_eca;
    return 0;
}

/**
 * @brief 
 * Fonction qui 
 * retourne la vie d'une tourelle 
 * selon son type
 * 
 * @param type 
 * type
 * @return int 
 * vie
 */
int life_kind(char type){

    if (type == 'D')
        return 3;
    if (type == 'C')
        return 3;
    if (type == 'B')
        return 10;
    if (type == 'A')
        return 1;
    if (type == 'S')
        return 4;
    return 0;
}   

/**
 * @brief 
 * Fonction qui alloue une tourelle
 * avec les informations neccessaires
 * pour ensuite retourner une tourelle.
 * @param jeux 
 * @param column 
 * Colonne
 * @param line 
 * Ligne
 * @param infoTurret 
 * @return Kind* 
 * Return qui est set dans le Game -> kind ensuite
 */
Kind * alloue_turret(Game * jeux, int column, int line, char infoTurret[3]){

    Kind * lstKind = (Kind *)malloc(sizeof(Kind));
    memset(lstKind, 0, sizeof(Kind));
    lstKind -> line = line;
    lstKind -> position = column;
    lstKind -> type = infoTurret[0];
    lstKind -> price = infoTurret[1];
    lstKind -> life = life_kind(infoTurret[0]);
    
    return lstKind;
}

/**
 * @brief 
 * Fonction qui initialise une tourelle
 * qui la trie par rapport à la ligne et
 * colonne pour ensuite la set dans la
 * structure jeux.
 * 
 * @param infoTurret 
 * @param column 
 * @param line 
 * @param jeux 
 */
void init_turret(char infoTurret[3], int column, int line, Game * jeux){

    Kind * add = alloue_turret(jeux, column, line, infoTurret);
    int nb_t = 0;

    if (add == NULL)
        return;

    Kind * current = jeux -> kind;

    if(jeux -> kind == NULL){
        jeux -> kind = add;
        return;
    } else {

        if (add -> line < current -> line){
            add -> next = jeux -> kind;
            jeux -> kind = add;
            return;
        }

        if (add -> line == current -> line){
            if (add -> position < current -> position){
                add -> next = jeux -> kind;
                jeux -> kind = add;
                return;

            }else if (add -> position == current -> position){
                if (add -> life < current -> life){
                    add -> next = jeux -> kind;
                    jeux -> kind = add;
                    return;
                }
            }
        }
        while (current -> next != NULL){
            nb_t ++;
            if (add -> line < current -> next -> line){
                add -> next = current -> next;
                current -> next = add;
                return;
            } else if (add -> line == current -> next -> line){
                if (add -> position < current -> position){
                add -> next = jeux -> kind;
                jeux -> kind = add;
                return;

                }else if (add -> position == current -> position){
                    if (add -> life < current -> life){
                        add -> next = jeux -> kind;
                        jeux -> kind = add;
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
 * Sysytème pour lire la saisie ASCII d'un joueur
 * Si il veut acheter une tourelle ou non...
 * 
 * @param jeux 
 * @return int 
 * Pour savoir quan arrêter la saisie controlé.
 */
int lire_turret(Game * jeux){

    int level = 0;
    int line = 0;
    int column = 0;
    char infoTurret[4] = "";
    char * turret[6] = {"0","25","15","20","30","50"};

    if (jeux -> money < 15){
        printf("Vous n'avez pas assez d'argent pour acheter une tourelle (min 15 Kamas / %d Kamas)\n", jeux -> money);
        return 6;
    }

    do{

        if (level <= 6 && level >= 1 && jeux -> money >= atoi(turret[level]))
            break;

        printf("Veuillez choisir une tourelle :\n\t(Vous avez %d Kamas) \n\n", jeux -> money);
        printf("1 |-| Le Cra : 25 Kamas\n2 |-| Le Xelor : 15 Kamas\n3 |-| La Bloqueuse : 20 Kamas\n");
        printf("4 |-| Eniripsa : 30 Kamas\n5 |-| Ecaflip : 50 Kamas\n\n");
        printf("6 |-| Pour passer son tour :  0 Kama\n\n");
        scanf("%d", &level);

        if (level == 6){
            return 6;
        }

    }while (1);

    do{

        if (PossibleTurret(line, column, jeux) == 1){
            break;
        }

        printf("Position de la tourelle : ligne colonne\n");
        scanf("%d %d", &line, &column);
    }while (PossibleTurret(line, column, jeux) == 0);

    printf("\nAchat de la tourelle effectuée !\n\n");

    jeux -> money -= atoi(turret[level]);

    jeux -> nb_turret ++;

    infoTurret[0] = SetType(level);
    infoTurret[1] = SetPrice(level);

    init_turret(infoTurret, column, line, jeux);
    
    return level;
}

/**
 * @brief 
 * Fonction qui supprime les 
 * tourelles et les frees ensuite
 * 
 * @param jeux 
 */
void death_turret(Game * jeux){

    Kind * prec = NULL;
    Kind * gentil = jeux -> kind;
    Kind * temp = NULL;

    while (jeux -> kind != NULL && jeux -> kind -> life <= 0){
        temp = jeux -> kind;
        jeux -> nb_turret-= 1;
        jeux -> kind = jeux -> kind -> next; 
        gentil = jeux -> kind;
        free(temp);
    }

    while (gentil != NULL){
        if (gentil -> life <= 0){
            jeux -> nb_turret -= 1;
            temp = gentil;
            prec -> next = gentil -> next;
            gentil = prec -> next;
            free(temp);
        } else {
            prec = gentil;
            gentil = gentil -> next;
        }
    }
}

/**
 * @brief 
 * Fonction si un ennemi est devant en premier.
 * 
 * @param jeux 
 * @param enem 
 * @return int 
 */
int enemy_devant(Game * jeux, Enemy * enem){

    Enemy * current = jeux -> enemy;

    while(current != NULL){
        if (current -> line == enem -> line){
            if (current -> position < enem -> position){
                return 0;
            }
        }
        current = current -> next;
    }
    return 1;
}

/**
 * @brief 
 * Fonction pour faire reculer un ennemi,
 * utilisé pour le xelor.
 * @param enem 
 * @param curr_k 
 */
void recule_case(Enemy * enem, Kind * curr_k){

    Enemy * current = enem;
    Enemy * temp = enem;
    int i;

    if (enem -> line == curr_k -> line){

        for (i = 1; i < 4; i++){
            if(curr_k -> position + i == current -> position &&
            enem -> line == curr_k -> line){

                if (current -> next == NULL){
                    current -> position ++;
                    enem -> life -= 1;
                }

                if (current -> next != NULL){
                    if (current -> next -> position - 1 == temp -> position){
                        enem -> life -= 2;
                    } else {
                        current -> position ++;
                        enem -> life -= 1;
                    }
                }
            }
        }
    }
}

/**
 * @brief 
 * FOnction pour le heal de l'eniripsa
 * Elle heal tout le monde avec une chance sur 2.
 * 
 * @param jeux 
 */
void heal_team(Game * jeux){

    Kind * current = jeux -> kind;
    srand(time(NULL));

    while (current != NULL){

        int heal = rand()%2 + 1;

        if (current -> type != 'A'){
            if (heal == 1){
                if (current -> life < life_kind(current -> type)){
                    current -> life ++;
                }
            }
        }
        current = current -> next;
    }
}

/**
 * @brief 
 * Fonction pour l'écaflip
 * qui tape en ligne de 4 de portée
 * sur deux lignes
 * 
 * @param enem 
 * @param curr_k 
 * @param jeux 
 */
void pile_face(Enemy * enem, Kind * curr_k, Game * jeux){

    int i;
    Enemy * current = enem;
    Enemy * mechant = jeux -> enemy;

    for (i = 1; i < 5; i++){
        if(curr_k -> position + i == current -> position){
            current -> life -= SetDamage(curr_k -> type);
            while (mechant != NULL){
                if (current -> position == mechant -> position){
                    if (current -> line - 1 == mechant -> line)
                        mechant -> life -= SetDamage(curr_k -> type);
                    if (current -> line + 1 == mechant -> line)
                        mechant -> life -= SetDamage(curr_k -> type);
                }
                mechant = mechant -> next;
            }
        }
    }
}

/**
 * @brief 
 * Fonction qui met des dégats aux tourelles
 * grace aux fonction ci-dessus.
 * 
 * @param jeux 
 */
void damage_kind(Game * jeux){

    Kind * current = jeux -> kind;

    int nb_t = 0;
    while (nb_t < jeux -> nb_turret){
        nb_t ++;
        Enemy * enem = jeux -> enemy;
            while (enem != NULL){
                if (current -> line == enem -> line){
                    if (enem -> position <= colonne){
                        if(enemy_devant(jeux, enem)){
                            if (current -> position < enem -> position){
                                if (current -> type == 'D')
                                    enem -> life -= SetDamage(current -> type);
                                if (current -> type == 'C')
                                    recule_case(enem, current);
                                if (current -> type == 'A')
                                    heal_team(jeux);
                                if (current -> type == 'S')
                                    pile_face(enem, current, jeux);
                            }
                        }
                    }
                }
                enem = enem -> next;
            }
        current = current -> next;
    }
}