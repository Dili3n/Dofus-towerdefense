#define ligne 7
#define colonne 24

typedef struct kind{

    char type;
    int life;
    int line;
    int position;
    int price;
    struct kind* next;

}Kind;

typedef struct enemy{

    int type;
    int life;
    int line;
    int position;
    int speed;
    int turn;
    struct enemy* next;
    struct enemy* next_line;
    struct enemy* prev_line;

}Enemy;

typedef struct{

    Enemy* enemy;
    Kind* kind;
    int nb_enemy;
    int nb_turret;
    int turn;
    int money;

}Game;