#include <SDL/SDL.h>
#include "fonctions_fichiers.h"
#include "fonctions_fichiers.c"
#include "define.h"
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>  
#include <math.h>



int main(int argc, char *argv[])   

{
   
    
 
    /*Declaration des variables surfaces*/ 
    SDL_Surface *ecran = NULL, *menu = NULL;   
    SDL_Rect posMenu;


    SDL_Event event1 ; 
    int menuBoolean = 1;  
    posMenu.x = 0; 
    posMenu.y = 0;   
     
    /*Initialisation de le SDL*/  
    SDL_Init(SDL_INIT_VIDEO);        
      
    /*Initialisation de l'écran*/
    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)) ;
     
    /*Charegement srpite menu et blitt*/
    menu = SDL_LoadBMP("menu_test.bmp") ;
    SDL_BlitSurface(menu,NULL,ecran,&posMenu);  
    
    /*Nom fenetre */
    SDL_WM_SetCaption("Jeu programmation avancée", NULL);     
    
    /*Permission des événements à répétitions*/ 
    SDL_EnableKeyRepeat(10, 10) ;        
 
    while(menuBoolean){
        SDL_WaitEvent(&event1); 
        switch(event1.type){    
            case SDL_MOUSEBUTTONDOWN :                 
              jouer(); 
              break;
            case SDL_QUIT:
              menuBoolean = 0;     
              break;
        }      
         SDL_BlitSurface(menu,NULL,ecran,&posMenu);   
         SDL_Flip(ecran) ; 
    }

  
   

    SDL_FreeSurface(menu);
    SDL_Quit(); // Arrêt de la SDL


 

    return EXIT_SUCCESS; // Fermeture du programme

}

 





