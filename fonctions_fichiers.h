#include <SDL/SDL.h>
#include "jouer.h"

typedef struct s_tank { 
    SDL_Surface *tank; 
    int level;
    int monde ;
    int pv ;
  } s_tank_t, *tank_t ;

char** allouer_tab_2D(int n, int m);
SDL_Rect* allouer_tab_1D(int n);
/*void desallouer_tab_2D(char** tab, int n);*/
void desallouer_tab_2D(char** tab, int dimension1, int dimension2);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
void ecrire_fichier(const char* nomFichier, char* chaine) ;
void afficherMap(char** map, SDL_Rect pos,SDL_Surface *ecran,SDL_Surface *terre,SDL_Surface *mur);
SDL_Rect* genereTourPos(char** map);
void afficherTour(SDL_Rect* tabPosTour,SDL_Surface *ecran,SDL_Surface *tour);
int calculA(SDL_Rect posTour , SDL_Rect posTank);
int calculB(SDL_Rect posTour, SDL_Rect posTank);
int calculC(SDL_Rect posTour, SDL_Rect posTank);
SDL_Rect genereFlagPos(char** map);
 void print(tank_t t) ;
int hasReached(tank_t tank, SDL_Rect postank,SDL_Rect posFlag);
void jouer();
 void next_level(tank_t t) ;
 int est_mort(tank_t t) ;
 int get_pv(tank_t t) ;
int get_level(tank_t t) ;
int get_monde(tank_t t) ;

/*Fonctions booléennes pour les collisions*/
int peutDeplacerTankHaut(char** tab, SDL_Rect posTank);
int peutDeplacerTankDroite(char** tab, SDL_Rect posTank);
int peutDeplacerTankBas(char** tab, SDL_Rect posTank);
int peutDeplacerTankGauche(char** tab, SDL_Rect posTank);

