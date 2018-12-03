#include <SDL/SDL.h>

char** allouer_tab_2D(int n, int m);
SDL_Rect* allouer_tab_1D(int n);
/*void desallouer_tab_2D(char** tab, int n);*/
void desallouer_tab_2D(char** tab, int dimension1, int dimension2);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
void afficherMap(char** map, SDL_Rect pos,SDL_Surface *ecran,SDL_Surface *terre,SDL_Surface *mur);
SDL_Rect* genereTourPos(char** map);
void afficherTour(SDL_Rect* tabPosTour,SDL_Surface *ecran,SDL_Surface *tour);
float calculCoeffDirBullet(SDL_Rect posTour , SDL_Rect posTank);
float calculOrdOriBullet(SDL_Rect posTour, float coeffDir);
SDL_Rect genereFlagPos(char** map);
int hasReached(SDL_Rect tank,SDL_Rect posFlag);
void jouer();


/*Fonctions booléennes pour les collisions*/
int peutDeplacerTankHaut(char** tab, SDL_Rect posTank);
int peutDeplacerTankDroite(char** tab, SDL_Rect posTank);
int peutDeplacerTankBas(char** tab, SDL_Rect posTank);
int peutDeplacerTankGauche(char** tab, SDL_Rect posTank);

