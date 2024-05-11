#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generation_terrains.h"

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

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv) {
  int N,i,l,h;
  float dObst;
  FILE *resFile;
  Terrain T;

  if (argc < 6) {
    printf(
        "Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[1], NULL, 10);
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);

  // test de l et h
  if (l > DIM_MAX || l % 2 == 0) {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h > DIM_MAX || h % 2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[5], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  // A compléter
  srand(time(NULL));
  // A compléter
  // Génération aléatoire des terrains
  // Écriture des terrains générés dans le fichier resFile
  // Écriture/Affichage des statistiques
  i=0;
  int nb_total_generees=0; // le nombre de terrain total qui est generees
  // int counter=0;//pour controller si on afficher N terrains ou pas dans la boucle
  float total_dObst = 0;//pour trouver la densite d'obstacle moyen on a besoin la somme des densites des obstacle 
  float dObst_obtenu;
  while(i<N ){
    T.hauteur=h;
    T.largeur=l;
    generation_aleatoire(&T,l,h,dObst);
    if(!existe_chemin_vers_sortie(&T)){
      
    }
    else{
      ecrire_terrain(resFile,&T,l/2,h/2);//on ecrire le terrain dans le fichier et initialise la position du robot
      fprintf(resFile,"\n"); //Pour être plus lisible
      T.tab[l/2][h/2] =LIBRE;//pour que nb_cases_occupees marche correctement on doit Il faut compter la position de départ 'C' comme LIBRE
      dObst_obtenu =(float)nb_cases_occupees(&T)/(float)(h*l);
      fprintf(resFile,"la densité d'obstacle obtenue  : %.2f\n",dObst_obtenu);
      fprintf(resFile,"la densité d'obstacle attendue  : %.2f\n",dObst);
      if(dObst<dObst_obtenu){
        fprintf(resFile,"la densité d'obstacle obtenue est plus grande que densite obstacle attendue avec une difference de %.2f\n",dObst_obtenu-dObst);
      }
      else{
        fprintf(resFile,"la densité d'obstacle obtenue est plus petite que densite obstacle attendue avec une difference de %.2f\n",dObst-dObst_obtenu);
      }
      fprintf(resFile,"\n"); //Pour être plus lisible
      
      i++;
      total_dObst+=dObst_obtenu;
    }
    nb_total_generees++;
  }
  
  fprintf(resFile,"les statistiques generelas:\n");
  fprintf(resFile,"\n"); //Pour être plus lisible
  fprintf(resFile,"la densité d'obstacle moyenne sur les terrains : %.2f\n",(total_dObst/(float)N));
  fprintf(resFile,"nombre du terrain valide: %d\n",N);
  fprintf(resFile,"nombre du terrrain totale: %d\n",nb_total_generees);
  fprintf(resFile,"Le pourcentage de terrain valides par rapport au nombre total généré : %.2f\n",((float)N/(float)nb_total_generees)*100);//j'affiche seulemet les 4 chiffres du pourcentage pour être plus lisible

    
    
    
  
  // fermeture des fichiers
  fclose(resFile);
  return 0;

}