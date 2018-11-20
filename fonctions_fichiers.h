#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>


char** allouer_tab_2D(int n, int m);
/*void desallouer_tab_2D(char** tab, int n);*/
void desallouer_tab_2D(char** tab, int dimension1, int dimension2);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
void pause();
void afficherMap(char** map, SDL_Rect pos,SDL_Surface *ecran,SDL_Surface *terre,SDL_Surface *mur);

/*Fonctions booléennes pour les collisions*/
int peutDeplacerTankHaut(char** tab, SDL_Rect posTank);
int peutDeplacerTankDroite(char** tab, SDL_Rect posTank);
int peutDeplacerTankBas(char** tab, SDL_Rect posTank);
int peutDeplacerTankGauche(char** tab, SDL_Rect posTank);