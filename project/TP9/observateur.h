/*
Arhan et Ege
#######################################################
###############       README         ##################
#######################################################

NOTE:Pour l'exo 5 du TP9 on a pense une nouvel propriete dont la description est la suivante:

Si notre robot effectue une rotation complète de 360 degrés autour de lui-même dans une meme case, 
c'est-à-dire s'il tourne quatre fois au total vers la gauche ou vers la droite dans le meme case, 
nous voulons qu'il signale une erreur. Pour ce faire, nous avons ajouté de 
nouveaux états à notre fonction de transition et faire des nouvels transitions, 
ces états sont les suivants :

init :(0 degree) Lorsque le robot avance dans cet état, il reste dans cet état. 
Cependant, s'il tourne à droite, il passe à l'état une_d après avoir effectué 
une rotation totale de droite une fois. De même, s'il tourne à gauche, il passe à 
l'état une_g après avoir effectué une rotation totale de gauche une fois.

une_d :-Lorsque le robot avance dans cet état, il revient à l'état init_etat car 
il se déplace vers un nouveau bloc donc on reset son rotation total à 0 degree. 
-S'il tourne à droite, il passe à l'état deux_d car il a effectué une rotation totale de droite deux fois. 
-S'il tourne à gauche, il revient à l'état init_etat car on a 90 degree a droite + 90 degree gauche donc ca fait 0 degree.

une_g : -Lorsque le robot avance dans cet état, il revient à l'état init_etat car
il se déplace vers un nouveau bloc donc on reset son rotation total à 0 degree.
-S'il tourne à gauche, il passe à l'état deux_g car il a effectué une rotation totale de gauche deux fois. 
-S'il tourne à droite, il revient à l'état init_etat car on a 90 degree a droite + 
90 degree gauche donc ca fait 0 degree.

deux_d : -Lorsque le robot avance dans cet état, il revient à l'état init_etat car 
il se déplace vers un nouveau bloc donc on reset son rotation total à 0 degree.
-S'il tourne à droite, il passe à l'état trois_d car il a effectué une rotation totale de droite trois fois.
-S'il tourne à gauche, il revient à l'état une_d car il a effectué une rotation totale de gauche une fois
(car on a 180 degree a droite + 90 degree gauche donc ca fait 90 degree droite).

deux_g : -Lorsque le robot avance dans cet état, il revient à l'état init_etat car 
il se déplace vers un nouveau bloc donc on reset son rotation total à 0 degree.
-S'il tourne à gauche, il passe à l'état trois_g car il a effectué une rotation totale de gauche trois fois. 
-S'il tourne à droite, il revient à l'état une_g car il a  effectué une rotation totale de droite une fois.
( car on a 180 degree a gauche + 90 degree droite donc ca fait 90 degree gauche).

trois_d : -Lorsque le robot avance dans cet état, il revient à l'état init_etat 
car il se déplace vers un nouveau bloc donc on reset son rotation total à 0 degree. 
-S'il tourne à droite, il passe à l'état erreur car il a effectué une rotation totale de droite quatre fois (soit 360 degrés). 
-S'il tourne à gauche, il revient à l'état deux_d car il a effectué une rotation totale de gauche deux fois.
(car on a 270 degree a gauche + 90 degree droite donc ca fait 180 degree droite).

trois_g : Lorsque le robot avance dans cet état, il revient à l'état init_etat 
car il se déplace vers un nouveau bloc donc on reset son rotation total à 0 degree.  
-S'il tourne à gauche, il passe à l'état erreur car il a effectué une rotation totale de gauche quatre fois (soit 360 degrés). 
-S'il tourne à droite, il revient à l'état deux_g car il a effectué une rotation totale de droite deux fois.
( car on a 270 degree a gauche + 90 degree droite donc ca fait 180 degree gauche).

Err : Cet état est atteint lorsqu'il a déjà effectué une rotation complète de 360 degrés. 
En raison d'une erreur déjà signalée, le robot reste dans cet état pour toutes les actions ultérieures.

Note:Pour tous les autres commandes ( M , ? , ! , ... ) il reste dans la meme etat.

*/


#ifndef _OBSERVATEUR_H_
#define _OBSERVATEUR_H_

#include<stdlib.h>
#include<stdio.h>

typedef enum {A,D,G,M} Alphabet;
typedef enum {Init,Mes,Err,Une_g,Deux_g,Trois_g,Une_d,Deux_d,Trois_d} Etat;

/*Renvoie l'etat intiial de l'automate*/
Etat initial();

/*fonction de transition de l'automate 1*/
Etat transition(Etat e,Alphabet c);

/*fonction de transition de l'automate 2*/
Etat transition_2(Etat e,Alphabet c);

/*Renvoi vrai ddi e est un etat final de l'automate*/
int est_final(Etat e);

/*Renvoi vrai ddi e est un etat final de l'automate*/
int est_final_2(Etat e);

#endif


