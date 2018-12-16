#include <SDL/SDL.h>
#include "jouer.h"
#include "structure.h"




char** allouer_tab_2D(int n, int m);
SDL_Rect* allouer_tab_1D_Rect(int n);
Tir* allouer_tab_1D_Tir(int n) ;
void desallouer_tab_2D(char** tab, int n);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier, int* continuer);
void ecrire_fichier(const char* nomFichier, char* chaine) ;
void afficherMap(char** map, SDL_Rect pos,SDL_Surface *ecran,SDL_Surface *terre,SDL_Surface *mur);
/*Fonctions booléennes pour les collisions*/
int peutDeplacerTankHaut(char** tab, SDL_Rect *posTank);
int peutDeplacerTankDroite(char** tab, SDL_Rect *posTank);
int peutDeplacerTankBas(char** tab, SDL_Rect *posTank);
int peutDeplacerTankGauche(char** tab, SDL_Rect *posTank);

float calcul_Angle(SDL_Rect posTour , SDL_Rect posTank) ;
SDL_Rect* genereTourPos(char** map);
Tir* genereTabTir(int n) ;
void afficherTour(SDL_Rect* tabPosTour,SDL_Surface *ecran,SDL_Surface *tour);
SDL_Rect genereFlagPos(char** map,SDL_Rect posTank) ;
int hasReached(tank_t tank, SDL_Rect postank,SDL_Rect posFlag);
void fire_Down(Tir* tabTir) ;
void initialise_Tir(SDL_Rect* tabPosTour,SDL_Rect posTank,Tir* tabTir,float vitesse) ;
void calcul_Tir(Tir* tabTir) ;
void afficher_Tir(Tir* tabTir,SDL_Surface *bullet,SDL_Surface *ecran) ;
int est_Touche(Tir* tabTir,SDL_Rect posTank) ;
void affiche_Explosion(SDL_Surface* explosion,SDL_Surface *ecran,SDL_Rect posTank,SDL_Rect exploSrc) ;
 
void print(tank_t t) ;
void jouer();
void next_level(tank_t t) ;
void est_mort(tank_t t) ;
int get_level(tank_t t) ;
int get_monde(tank_t t) ;
void update_monde(tank_t t) ;
tank_t cons() ;
