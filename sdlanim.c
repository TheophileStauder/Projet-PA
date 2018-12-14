#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
/*#include "fonctions_fichiers.h"
#include "fonctions_fichiers.c"*/
#include "jouer.c"
#include "jouer.h"

#include "define.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>   
#include <math.h>
#include <string.h>



int main(int argc, char *argv[])   

{
    // Recupere le score de la derniere partie   
    char** tab = lire_fichier("ecriture_fichier") ;

    // texte qui sera ecrit dans option
    char chaine1[30] = "Nombre de drapeaux : " ; 
    char chaine2[30] = "Monde atteint : " ;

    // dernier score repuperé

    const char* tab0 = tab[0][0];
    const char* tab1 = tab[0][1];
   
    // concatenation du texte avec le score associé
    strcat(chaine1, &tab0);
    strcat(chaine2, &tab1);
   
    /*Declaration des variables surfaces*/ 
    SDL_Surface *ecran = NULL, *menu = NULL, *barre_jouer = NULL, *barre_options = NULL, *barre_quitter = NULL, *texte = NULL, *retour = NULL, *monde = NULL ;     
    SDL_Rect posMenu, pos_jouer, pos_options, pos_quitter, posTexte, pos_retour;


    SDL_Event event1 ; 
    int menuBoolean = 1;  //pour savoir quand quitter
    int afficher = 1 ; //pour ne pas afficher le menu a l'interrieur d'option

    //position du fond
    posMenu.x = 0; 
    posMenu.y = 0;   

    // position du bouton jouer
    pos_jouer.x = 213 ;
    pos_jouer.y = 32 ;

    // position du bouton option
    pos_options.x = 213 ;
    pos_options.y = 132 ;

    // position du bouton quitter
    pos_quitter.x = 213 ;
    pos_quitter.y = 232 ;

    // position du bouton retour (dans option)
    pos_retour.x = 520 ;
    pos_retour.y = 270 ;
     
    /*Initialisation de le SDL*/  
    SDL_Init(SDL_INIT_VIDEO);    

    /*Initialisation de ttf*/
    TTF_Init();

    // intialisation de la police
    TTF_Font *police = NULL;

    void affiche_texte(){
        police = TTF_OpenFont("Alioli-Regular.ttf", 50) ;
        SDL_Color couleurNoire = {0, 0, 0};
        texte = TTF_RenderText_Blended(police,chaine1, couleurNoire);
        // position pour afficher la premiere ligne de texte
        posTexte.x = 32 ;
        posTexte.y = 32 ;
        // affichage de la premiere ligne
        SDL_BlitSurface(texte, NULL, ecran, &posTexte); /* Blit du texte */

        monde = TTF_RenderText_Blended(police, chaine2, couleurNoire);
        // position pour afficher la deuxieme ligne de texte
        posTexte.y = 150 ;
        // affichage de la seconde ligne
        SDL_BlitSurface(monde, NULL, ecran, &posTexte); /* Blit du texte */

    }

    void affiche_menu(SDL_Surface *menu, SDL_Surface *barre_jouer, SDL_Surface *barre_quitter, SDL_Surface *barre_options){

        // transparence
        SDL_SetColorKey(barre_options, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(barre_options->format, 153,217,234));
        SDL_SetColorKey(barre_jouer, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(barre_jouer->format, 153,217,234));
        SDL_SetColorKey(barre_quitter, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(barre_quitter->format, 153,217,234));
        
        SDL_BlitSurface(menu,NULL,ecran,&posMenu);
        SDL_BlitSurface(barre_jouer,NULL,ecran,&pos_jouer);  
        SDL_BlitSurface(barre_quitter,NULL,ecran,&pos_quitter);  
        SDL_BlitSurface(barre_options,NULL,ecran,&pos_options) ;
    }

    /*Initialisation de l'écran*/
    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)) ;
     
    /*Chargement des sprites*/
    menu = SDL_LoadBMP("fond.bmp") ;
    barre_options = SDL_LoadBMP("barre_options.bmp") ;
    barre_quitter = SDL_LoadBMP("barre_quitter.bmp") ;
    barre_jouer = SDL_LoadBMP("barre_jouer.bmp") ;
    retour = SDL_LoadBMP("retour_final.bmp") ;

    // transparence du bouton de retour
    SDL_SetColorKey(retour, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(barre_options->format, 153,217,234));

    // affiche le menu (fond + boutons)
    affiche_menu(menu, barre_jouer, barre_quitter, barre_options) ;
    
    /*Nom fenetre */
    SDL_WM_SetCaption("Jeu programmation avancée", NULL);     
    
    /*Permission des événements à répétitions*/ 
    SDL_EnableKeyRepeat(10, 10) ;      

    int x, y ; // coordonnées de la souris
  
    int dans_option = 0 ;  // booleen 

    while(menuBoolean){
        SDL_WaitEvent(&event1); 
        switch(event1.type){    
            case SDL_MOUSEBUTTONDOWN : 
              // recupere les coordonnees de la souris 
              SDL_GetMouseState(&x, &y);   
              // si clique sur le bouton jouer
              if(y>=32 && y <= 72 && x>=213 && x<=454 && !dans_option) {     
                jouer(); 
                dans_option = 0 ;
                afficher = 1 ;
              }
              // si clique sur le bouton option
              if(y>=132 && y<=172 && x>=213 && x<=454){
                SDL_BlitSurface(menu,NULL,ecran,&posMenu);
                SDL_BlitSurface(retour,NULL,ecran,&pos_retour);  
                // empeche d'afficher le menu par dessus notre texte
                afficher = 0 ;
                // affiche le dernier score
                affiche_texte() ;
                dans_option = 1 ;
              }
              // si est dans option et clique sur le bouton retour
              if(y>=270 && y<=310 && x>=520 && x<=637 && dans_option){
                dans_option = 0 ;
                // renvoie au menu
                affiche_menu(menu, barre_jouer, barre_quitter, barre_options) ;
              }
              // si clique sur quitter
              if(y>=232 && y<= 272 && x>=213 && x<=454 && !dans_option){
                printf("Aurevoir\n");
                menuBoolean = 0 ;
                dans_option = 0 ;
              }
              break;
            case SDL_QUIT:
              menuBoolean = 0;     
              break;
        }      
        // si booleen afficher == 1
        if(afficher){
            affiche_menu(menu, barre_jouer, barre_quitter, barre_options) ;

        }
        SDL_Flip(ecran) ; 
    }

  
          
    // libere les surfaces
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(barre_jouer);
    SDL_FreeSurface(barre_options);
    SDL_FreeSurface(barre_quitter);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(retour);
    SDL_FreeSurface(monde);



    SDL_Quit(); // Arrêt de la SDL
    TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
    TTF_Quit(); // Arret de ttf

 

    return EXIT_SUCCESS; // Fermeture du programme

}

      





