# towerdefense

C’est un jeu à un seul joueur qui joue contre la machine (ou l’environnement). Durant chaque niveau, une somme de
crédits est donnée au joueur qui devra acheter et mettre en place des tourelles qui devront arrêter une vague de vilains
gros méchants souhaitant infester l’ordinateur central.

Comment jouer au jeu ?

1) En ASCII

Dans un premier temps il faut compiler le programme, pour cela il vous suffit de taper la
commande : “clang -std=c17 main.c -Wall -o main.c -lMLV”
Pour lancer le jeu en ASCII vous devez exécuter la commande : “./main -a”

Une fois lancé, le menu apparaîtra, il vous sera demandé de choisir votre niveau, vous
devrez donc entrez un chiffre de 1 à 5.

Vous aurez une prévisualisation de la vague de monstres puis il vous sera demandé de
choisir les tourelles que vous voulez placer. Encore une fois vous devrez entrer un chiffre de
1 à 7 (7 étant pour lancer le jeu).

Une fois votre tourelle choisie, il vous sera demandé de choisir la position de cette tourelle,
vous devrez donc entrer la ligne, entre 1 et 7, puis la colonne, entre 1 et 24.

Une fois placée votre tourelle vous pouvez en placer d’autre en fonction de votre argent
disponible (dans le jeu les “kamas”) ou alors entrez 7 pour débuter le jeu.

2) En MLV (affichage graphique)
3) 
Vous devez compiler de la même manière que pour l’ASCII cependant pour lancer le jeu
vous devrez entrer la commande : “./main -g

Une fois lancé le menu principal apparaîtra, de ce menu vous pourrez au choix, cliquer sur
le bouton RÈGLE pour aller dans le menu des règles et voir les capacité des tourelles,
ou alors vous pouvez cliquer sur CREDIT pour voir le menu des crédits.

La troisième possibilité, la plus importante, vous pouvez cliquer sur le bouton JOUER.
Après avoir cliquer sur le bouton JOUER vous serez redirigés vers le menu de choix des
niveaux, vous pourrez donc choisir un des 5 niveaux proposés.

Une fois un niveau sélectionné vous serez redirigé vers l’interface de jeu.

Sur cette interface vous pouvez cliquer sur le bouton “Voir la vague !” pour voir la vague de
monstres qui vous attend.
Pour placer des tourelles il vous suffit de cliquer sur les icônes des tourelles en haut à droite
puis de les placer sur les cercles en cliquant dessus.
Une fois toutes vos tourelles placées vous devez cliquer sur le bouton PLAY ce qui lancera
le jeu.
