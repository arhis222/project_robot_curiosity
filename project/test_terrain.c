#include "terrain.h"
#include <stdio.h>



int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;
  erreur_terrain test;
  

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  test=lire_terrain(f, &t, &x, &y);
  
  
  switch (test){
  case OK:
    afficher_terrain(&t);
    printf("Position initiale du robot : (%d, %d)\n", x, y);
    break;
  case ERREUR_FICHIER:
    printf("Veuillez entrer un nouveau nom de fichier : \n");
    char c[100];
    scanf("%s", c); //prend le nom du terrain en argument
    FILE *f1 = fopen(c, "r");
    while(f1==NULL){
      printf("Veuillez entrer un nouveau nom de fichier : \n");
      char c[100];
      scanf("%s", c); //prend le nom du terrain en argument
      f1 = fopen(c, "r");
    }
    
    test=lire_terrain(f1, &t, &x, &y); 
    
    switch(test){
      case OK:
        afficher_terrain(&t);
        printf("Position initiale du robot : (%d, %d)\n", x, y);
      case ERREUR_FICHIER:
        break;
      case ERREUR_CARACTERE_INCORRECT:
        printf("erreur:charactere lu dans le terrain inconnu (en dehors de ceux ci .,~,#,C)\n");
        break;
      case ERREUR_POSITION_ROBOT_MANQUANTE:
        printf("erreur:position du robot manques\n");
        break;
      case ERREUR_LECTURE_LARGEUR:
        printf("erreur:valeur du largeur manques\n");
        break;
      case ERREUR_LECTURE_HAUTEUR:
        printf("erreur:valeur du hauteur manques\n");
        break;
      case ERREUR_LARGEUR_INCORRECTE:
        printf("erreur:valeur du largeur incorrecte\n");
        break;
      case ERREUR_HAUTEUR_INCORRECTE:
        printf("erreur:valeur du hauteur incorrecte\n");
        break;
      case ERREUR_LIGNES_MANQUANTES:
        printf("erreur:il manque de(s) ligne(s) dans le fichier\n");
        break;
      case ERREUR_LIGNE_TROP_COURTE:
        printf("erreur:fichier contient de(s) ligne(s) plus court qu'on a declare(largeur)\n");
        break;
      case ERREUR_LIGNE_TROP_LONGUE:
        printf("erreur:fichier contient de(s) ligne(s) plus long qu'on a declare(largeur)\n");
        break;
    }
    fclose(f1);
    break;
      
  case ERREUR_CARACTERE_INCORRECT:
    printf("erreur:charactere lu dans le terrain inconnu (en dehors de ceux ci .,~,#,C)\n");
    break;
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf("erreur:position du robot manques\n");
    break;
  case ERREUR_LECTURE_LARGEUR:
    printf("erreur:valeur du largeur manques\n");
    break;
  case ERREUR_LECTURE_HAUTEUR:
    printf("erreur:valeur du hauteur manques\n");
    break;
  case ERREUR_LARGEUR_INCORRECTE:
    printf("erreur:valeur du largeur incorrecte\n");
    break;
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("erreur:valeur du hauteur incorrecte\n");
    break;
  case ERREUR_LIGNES_MANQUANTES:
    printf("erreur:il manque de(s) ligne(s) dans le fichier\n");
    break;
  case ERREUR_LIGNE_TROP_COURTE:
    printf("erreur:fichier contient de(s) ligne(s) plus court qu'on a declare(largeur)\n");
    break;
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("erreur:fichier contient de(s) ligne(s) plus long qu'on a declare(largeur)\n");
    break;
  }
  if(f!=NULL){
    fclose(f);
  }
}


//pour tester la fonction ecrire_terrain
/*
#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;
  FILE *fi;
  Terrain t;
  int x, y;

  if (argc < 3) {
    printf("Usage : %s <fichier_lecture> <fichier_ecriture>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier en lecture.\n");
    return 1;
  }

  fi = fopen(argv[2], "w");
  if (fi == NULL) {
    printf("Erreur lors de l'ouverture du fichier en écriture.\n");
    fclose(f);
    return 1;
  }

  lire_terrain(f, &t, &x, &y);
  fclose(f);

  afficher_terrain(&t);
  ecrire_terrain(fi, &t, x, y);

  fclose(fi);
  printf("Position initiale du robot : (%d, %d)\n", x, y);

  return 0;
}
*/