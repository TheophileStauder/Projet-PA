#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


char** allouer_tab_2D(int n, int m);
/*void desallouer_tab_2D(char** tab, int n);*/
void desallouer_tab_2D(char** tab, int dimension1, int dimension2);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
void pause();