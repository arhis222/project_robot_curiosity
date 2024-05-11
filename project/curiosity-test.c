#include "terrain.h"
#include "robot.h"
#include "environnement.h"
#include "interprete.h"
#include "programme.h"

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

char orientation_char(Robot r) {
   Orientation o=r.o;
  switch (o) {
    case Nord:
        return'N';
    case Est:
        return'E';
    case Ouest:
        return 'O';
    case Sud:
        return 'S';
 }
}


//int verifier_max_pas(char t[DIM_MAX], int max) {
    //return max >= strlen(t);
//}



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
    printf(
        "Erreur lecture du terrain : position initiale du robot manquante\n");
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

int main(int argc, char **argv) {
    Environnement envt;
    Programme prog;
    Robot robot;
    erreur_terrain errt;
    erreur_programme errp;
    etat_inter etat;
    resultat_inter res;
    FILE *f;
    char nom_terrain[DIM_MAX];
    char nom_programme[DIM_MAX];
    int max,x,y;
    char e;
    int reponse_fscanf;
    int x_attendu,y_attendu;
    char orient_attendu;
    int pas=0;
    int n,ne;             // Nombre de valeurs lues

    if (argc < 2) {
    printf("Usage: %s <test_fichier>", argv[0]);
    return 1;
    }

    f=fopen(argv[1],"r");

    if(f==NULL){
        printf("Erreur du fichier\n");
        return 1; // en pire cas on return 1
    }

    n=fscanf(f,"%s",nom_terrain);
    if (n == 0) {
      printf("nom terrain manquee");
      return -1;
    }

    /* Initialisation de l'environnement : lecture du terrain,
        initialisation de la position du robot */
    errt = initialise_environnement(&envt, nom_terrain);
    gestion_erreur_terrain(errt);
    
    n=fscanf(f,"%s",nom_programme);
    if (n == 0) {
      printf("nom programme manquee");
      return -1;
    }
    //printf("%s",nom_programme);
    /* Lecture du programme */
    errp = lire_programme(&prog, nom_programme);

    gestion_erreur_programme(errp);


    reponse_fscanf=fscanf(f,"%d",&max);
    if(reponse_fscanf==0){
        printf("valeur max manquee\n");
        return -1;
      }
    if (max<0 || max>100000)
    {
      printf("valeur max incorrect\n");
      return -1;
    }
    
    fscanf(f, "\n");
    fscanf(f,"%c",&e);
    //printf("%c",e);
    if(e=='N' || e=='F'){
        ne=fscanf(f,"%d",&x_attendu);
        n=fscanf(f,"%d",&y_attendu);
        if(x_attendu < 0 || y_attendu<0 || x_attendu >DIM_MAX || y_attendu >DIM_MAX || ne==0 || n==0 ){
          printf("valeur de x ou y incorrect ou manque \n");
          return -1;
        }
        fscanf(f," ");
        fscanf(f,"%c",&orient_attendu);
        
        
        if(orient_attendu != 'O' && orient_attendu != 'E' && orient_attendu != 'N' && orient_attendu != 'S'){
          printf("orient incorrect ou manque \n");
          return -1;

        }


    }
    
    //printf("%d,%d,%c",x_attendu,y_attendu,orient_attendu);
    

    /* Initialisation de l'état */
    init_etat(&etat);
    do {
    
    res = exec_pas(&prog, &envt, &etat);
    // Affichage du terrain et du robot 
    afficher_envt(&envt);
    pas++;
    if(pas==max){//on a ajoute cette condition car a la fin du exec_pas fonction on n'atteint jamais  a ARRET_ROBOT
      res = OK_ROBOT;
    }
    } while (res == OK_ROBOT  &&  pas<max);
    
    

    robot = envt.r;
    position(&robot,&x,&y);
    //printf("%u\n",res);
    //printf("%d\n",x);
    //printf("%d\n",y);
    //printf("%d\n",pas);
    //printf("%d\n",robot.x);
    //printf("orientation: %c\n",orientation_char(robot));
    
    // Affichage du résultat 
    switch (res) {
    case OK_ROBOT:
        if(e=='N' && x==x_attendu && y==y_attendu && orient_attendu==orientation_char(robot)){
            printf("OK\n");
        }
        else{
            printf("no  les valeurs attendu ne sont pas correct \n");
            printf("e attendu : N \n");
            printf("e obtenu : %c\n",e);
            printf("x attendu : %d\n",x_attendu);
            printf("x obtenu : %d\n",x);
            printf("y attendu :  %d\n",y_attendu);
            printf("y obtenu : %d\n",y);
            printf("orientation attendu : %c\n",orient_attendu);
            printf("orientation obtenu : %c\n",orientation_char(robot));
        }
        break;
    case ARRET_ROBOT :
        if(e=='F' && x==x_attendu && y==y_attendu && orient_attendu==orientation_char(robot) ){
            printf("OK\n");
        }
        else{
            printf("no  les valeurs attendu ne sont pas correct\n");
            printf("e attendu : F \n");
            printf("e obtenu : %c\n",e);
            printf("x attendu : %d\n",x_attendu);
            printf("x obtenu : %d\n",x);
            printf("y attendu :  %d\n",y_attendu);
            printf("y obtenu : %d\n",y);
            printf("orientation attendu : %c\n",orient_attendu);
            printf("orientation obtenu : %c\n",orientation_char(robot));
        }
        break;

    case SORTIE_ROBOT:
        if(e=='S'){
            printf("OK\n");
        }
        else{
            printf("no  les valeurs attendu ne sont pas correct\n");
            printf("e attendu : S \n");
            printf("e obtenu : %c\n",e);
        }
        break;


    case CRASH_ROBOT:
        if(e=='O'){
            printf("OK\n");
        }
        else{
            printf("no  les valeurs attendu ne sont pas correct\n");
            printf("e attendu : O \n");
            printf("e obtenu : %c\n",e);
        }
        break;

    case  PLOUF_ROBOT:
        if(e=='P'){
            printf("OK\n");
        }
        else{
            printf("no  les valeurs attendu ne sont pas correct\n");
            printf("e attendu : P \n");
            printf("e obtenu : %c\n",e);
        }
        break;


    default:
        break;
        //printf("caractere inconnu\n");
    }

}
