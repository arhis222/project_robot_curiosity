#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "generation_terrains.h"

#include <stdio.h>
#include <stdlib.h>


void gestion_erreur_terrain(erreur_terrain e) {
  switch (e) {
  case OK:
    break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf("Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
  switch (e.type_err) {
  case OK_PROGRAMME:
    break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}

int nb_cases_occupees(Terrain *T) {
  int occupee = 0;
  int x, y;
  for (x = 0; x < largeur(T); x++) {
    for (y = 0; y < hauteur(T); y++) {
      if (T->tab[x][y] != LIBRE)
        occupee++;
    }
  }
  return occupee;
}

int tirage(int a,int b){//generer une nombre aleatoire entre a et b
    return a + rand()% (b-a+1);
}

int main(int argc, char **argv) {
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;
  int N,i,l,h,nb_step_max,graine,counter;
  float d;
  FILE *resFile;
  FILE *fichier_programme;
  FILE *terrain;
  Terrain T;
  int obstacle=0;//pour les statistiques generals a la fin
  int bloque = 0;//pour les statistiques generals a la fin
  int sortie = 0;//pour les statistiques generals a la fin
  int total_pas =0;
  if (argc < 9) {
  printf("Usage: %s <fichier_programme> <N> <largeur> <hauteur> <densite_obstacle> <graine> <max> <fichier_res> \n",argv[0]);
  return 1;
  }
  fichier_programme  = fopen(argv[1], "r");
  N = strtol(argv[2], NULL, 10);
  l = strtol(argv[3], NULL, 10);
  h = strtol(argv[4], NULL, 10);
  d = strtof(argv[5], NULL);
  graine = strtol(argv[6], NULL,10);
  nb_step_max  = strtol(argv[7], NULL, 10);


  // test de l et h
  if (l > DIM_MAX || l % 2 == 0) {
  printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
  return 1;
  }
  if (h > DIM_MAX || h % 2 == 0) {
  printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
  return 1;
  }
  if ((d> 1) || (d < 0)) {
  printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
  return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[8], "w");
  
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  // A compléter
  srand(graine);

  
  int nb_total_generees=0; // le nombre de terrain total qui est generees
  // int counter=0;//pour controller si on afficher N terrains ou pas dans la boucle
  float total_dObst = 0;//pour trouver la densite d'obstacle moyen on a besoin la somme des densites des obstacle 
  float dObst_obtenu ;

  for(int k=0;k<N;k++){
    terrain = fopen("terrain.txt", "w");
      /* Initialisation de l'environnement : lecture du terrain,
      initialisation de la position du robot */
    i=0;
    while(i<1){ // on veut seulement une terrain
        T.hauteur=h;
        T.largeur=l;
        generation_aleatoire(&T,l,h,d);
        if(existe_chemin_vers_sortie(&T)){
            ecrire_terrain(terrain,&T,l/2,h/2);//on ecrire le terrain dans le fichier et initialise la position du robot
            fprintf(terrain,"\n"); //Pour être plus lisible
            //fprintf(resFile,"\n"); //Pour être plus lisible
            dObst_obtenu =(float)nb_cases_occupees(&T)/(float)(h*l);
            i++;
            total_dObst+=dObst_obtenu;
            
        }
        nb_total_generees++;
        
    } 
    fclose(terrain); 
    //init_robot(l/2,h/2,E);
    errt = initialise_environnement(&envt, "terrain.txt");
    gestion_erreur_terrain(errt);

    /* Lecture du programme */
    errp = lire_programme(&prog, argv[1]);
    gestion_erreur_programme(errp);

    /* Initialisation de l'état */
    init_etat(&etat);
    afficher_envt(&envt);
    counter=0;
    do {
        res = exec_pas(&prog, &envt, &etat);
        counter++;
        /* Affichage du terrain et du robot */
        //afficher_envt(&envt);
    } while (counter!=nb_step_max && res==OK_ROBOT);

    /* Affichage du résultat */
    switch (res) {
    case SORTIE_ROBOT:
        fprintf(resFile,"%d\n",counter);
        //printf("robot sorti\n");
        total_pas +=counter;
        sortie++;
        break;
    case OK_ROBOT:
    case ARRET_ROBOT:
        fprintf(resFile,"-1\n");
        bloque++;
        break;
    case PLOUF_ROBOT:
        fprintf(resFile,"-2\n");
        obstacle++;
        break;
    case CRASH_ROBOT:
        fprintf(resFile,"-3\n");;
        obstacle++;
        break;
    default:
        fprintf(resFile,"erreur\n");
    }

  }

  // fermeture des fichiers
  fclose(resFile);
  printf("les statistiques generelas:\n");
  printf("\n"); //Pour être plus lisible
  printf("nombre et pourcentage de terrains d'où le robot est sorti : %d donc %.2f\n",sortie,((float)sortie/(float)N)*100);
  printf("nombre et pourcentage de terrains d'ou il est resté bloqué: %d donc %.2f\n",bloque,((float)bloque/(float)N)*100);
  printf("nombre et pourcentage de terrains d'où il est rentré dans un obstacle: %d donc %.2f\n",obstacle,((float)obstacle/(float)N)*100);
  /*si le robot ne sortie jamais il affiche -nan */
  printf("nombre moyen de pas effectués pour les sorties : %.2f\n",((float)total_pas/(float)sortie));//j'affiche seulemet les 4 chiffres du pourcentage pour être plus lisible
  return 0;
}

