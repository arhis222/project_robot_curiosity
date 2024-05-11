#ifndef _GENERATION_TERRAINS_H_
#define _GENERATION_TERRAINS_H_

#include "terrain.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tirage(int a,int b);//generer une nombre aleatoire entre a et b
/* Génère aléatoirement un terrain T, de largeur l, de hauteur h,
   avec une densité d'obstacle dObst : 0 <= dObst <= 1.
   Précondition : T est un pointeur vers un terrain existant.
   Résultat : T est modifié et contient le terrain généré.
              La case centrale de T ne contient pas d'obstacle.
 */
void generation_aleatoire(Terrain *T, int l, int h, float dObst);

/* determine s'il existe un chemin du centre au bord du terrain T
   version avec tableau annexe
*/
int existe_chemin_vers_sortie(Terrain *T);

#endif
