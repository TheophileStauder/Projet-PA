#include <SDL/SDL.h>
#include "structure.h"

/*Fonctions allocations mémoires*/
char** allouer_tab_2D(int n, int m);
SDL_Rect* allouer_tab_1D_Rect(int n);
void desallouer_tab_2D(char** tab, int n);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
Tir* allouer_tab_1D_Tir(int n);
Tir* genereTabTir(int n);

/*Fonctions d'affichages */
void afficherMap(char** map, SDL_Rect pos,SDL_Surface *ecran,SDL_Surface *terre,SDL_Surface *mur);
SDL_Rect* genereTourPos(char** map);
void afficherTour(SDL_Rect* tabPosTour,SDL_Surface *ecran,SDL_Surface *tour);

/*Fonction calcul la position des balles de tirs*/
void initialise_Tir(SDL_Rect* tabPosTour,SDL_Rect posTank,Tir* tabTir);
void calcul_Tir(Tir* tabTir);
void affiche_Tir(Tir* tabTir,SDL_Surface *bullet,SDL_Surface *ecran);
void fire_Down(Tir* tabTir);
int est_Touche(Tir* tabTir,SDL_Rect posTank);
void affiche_Explosion(SDL_Surface* explosion,SDL_Surface *ecran,SDL_Rect posTank,SDL_Rect exploSrc);

/*Fonction pour le flag*/
SDL_Rect genereFlagPos(char** map,SDL_Rect posTank);
int hasReached(SDL_Rect tank,SDL_Rect posFlag);

/*Fonctions booléennes pour les collisions*/
int peutDeplacerTankHaut(char** tab, SDL_Rect *posTank);
int peutDeplacerTankDroite(char** tab, SDL_Rect *posTank);
int peutDeplacerTankBas(char** tab, SDL_Rect *posTank);
int peutDeplacerTankGauche(char** tab, SDL_Rect *posTank);

/*Fonction JOUER*/
void jouer();


/*Fonction calcul angle*/
float calcul_Angle(SDL_Rect posTour , SDL_Rect posTank);



