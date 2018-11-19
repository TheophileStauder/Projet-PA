#include <SDL/SDL.h>
#include "fonctions_fichiers.h"
#include "fonctions_fichiers.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define SIZE_SPRITE 32 
#define WIDTH 640 
#define HEIGHT 320 






int main(int argc, char *argv[])

{
    int i, j ;
    char** tab = lire_fichier("ecrire") ;

    int colorkey ;
    int level = 1 ;
    int continuer = 1 ;
        

    /*Declaration des variables surfaces*/
    SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL, *grass = NULL ,*tank_haut ,*tank_bas ,*tank_gauche ,*tank_droite;
    SDL_Rect pos, tankSrc ;//, posGrass ;
    SDL_Event event ;
    
    /*Initialisation de le SDL*/
    SDL_Init(SDL_INIT_VIDEO); 
    
    /*Initialisation de l'écran*/
    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)) ;
    
    /*Nom fenetre */
    SDL_WM_SetCaption("Jeu programmation avancée", NULL);
    
    /*Permission des événements à répétitions*/
    SDL_EnableKeyRepeat(10, 10) ;

    /*Chargement des sprites*/
    terre = SDL_LoadBMP("terreBon.bmp") ;
    mur = SDL_LoadBMP("murBon.bmp") ;
    tank_haut = SDL_LoadBMP("tank_haut.bmp") ;
    tank_bas = SDL_LoadBMP("tank_bas.bmp") ;
    tank_droite = SDL_LoadBMP("tank_droite.bmp") ;
    tank_gauche = SDL_LoadBMP("tank_gauche.bmp") ;
    grass = SDL_LoadBMP("grass.bmp") ;
    
    tank = tank_bas;

    /*Gestion de la transparence des sprites*/
    colorkey = SDL_MapRGB(ecran->format, 0,0,0);
    SDL_SetColorKey(tank_droite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(tank_gauche, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    SDL_SetColorKey(tank_bas, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
    
    /*Initialisation fiche sprite tank*/
    tankSrc.x = 0;
    tankSrc.y = 0;
    tankSrc.w = SIZE_SPRITE;
    tankSrc.h = SIZE_SPRITE;  
   
    
   
    /*
    posGrass.x = 0 ;
    posGrass.y = 0 ;
    */
   
    /*Chargement de la map, positionement des sprites mur et terre*/
    pos.x = 0 ;
    pos.y = 0 ;
    
    for(i = 0 ; i < 10 ; i++){
        for (j = 0 ; j < 20 ; j++){
            if(tab[i][j] == '1'){
                SDL_BlitSurface(mur, NULL, ecran, &pos) ;

            }
            else{
                SDL_BlitSurface(terre, NULL, ecran, &pos) ;

            }
            pos.x = pos.x + SIZE_SPRITE ;
        }
        pos.y = pos.y + SIZE_SPRITE ;
        pos.x = 0 ;
    }
    
    /*Blitte du tank*/
    //(Inutile car pos pas dans fenetre pour le moment)
    SDL_BlitSurface(tank, &tankSrc, ecran, &pos) ;
    

    //srand(time(NULL));
    if (level){
      /*pos.x = (rand()%WIDTH/SIZE + 1) ;
      pos.y = (rand()%HEIGHT/SIZE + 1) ;  */
      pos.x = 64 ;
      pos.y = 160 ;
   
     // printf("position aleatoire = (%d, %d)  tab[i][j] = %c\n\n",i,j, tab[i][j]) ;
      SDL_BlitSurface(grass, NULL, ecran, &pos) ;
    /*  while (tab[i][j]=='1'){
	pos.x = (rand()%WIDTH/SIZE + 1)*SIZE;
        pos.y = (rand()%HEIGHT/SIZE + 1) *SIZE;  
	i = pos.x ;
        j = pos.y ;
      }
      SDL_BlitSurface(grass, NULL, ecran, &pos) ;
*/
    level++ ;
    }
      
    if (level==2){
      pos.x = 192 ;
      pos.y = 32 ; 
      SDL_BlitSurface(grass, NULL, ecran, &pos) ;
      level++ ;
    }
    
     if (level==3){
      pos.x = 320 ;
      pos.y = 224 ; 
      SDL_BlitSurface(grass, NULL, ecran, &pos) ;
      level++ ;
    }
    
     if (level==4){
      pos.x = 256 ;
      pos.y = 32 ; 
      SDL_BlitSurface(grass, NULL, ecran, &pos) ;
      level++ ;
    }


    
    while(continuer){
        
        SDL_WaitEvent(&event) ;
        switch(event.type){
            case SDL_QUIT :
                continuer = 0 ;
                break ;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym){
                    case SDLK_UP :
                     
		      tank = tank_haut;
		      tankSrc.y = 0;
		      if (tankSrc.x >191){
			tankSrc.x = 0 ;
                       }
                       tankSrc.x += SIZE_SPRITE;
		       pos.y -= 2;
                        break ;
                    case SDLK_DOWN :
		      
			  tank = tank_bas;
			  tankSrc.y = 0;
			  if (tankSrc.x >191){
			  tankSrc.x = 0 ;
			}
			tankSrc.x += SIZE_SPRITE;
			if (pos.y <= 290){
			  pos.y += 2;
			}
                        break ;
		    case SDLK_RIGHT :
			tank = tank_droite;
			tankSrc.x = 0; 
                       if (tankSrc.y >191){
			tankSrc.y = 0 ;
                       }
                       tankSrc.y += SIZE_SPRITE;
		       if (pos.x <= 610){
			 pos.x += 2;
		       }
		       
                        break ;
                    
		    case SDLK_LEFT :
		      
			tank = tank_gauche;
			tankSrc.x = 0;
                        if (tankSrc.y >191){
			tankSrc.y = 0 ;
                       }
                       tankSrc.y += SIZE_SPRITE;
		       pos.x -= 2;
                        break ;
                    default :
                        break ;
                }
                break ;
                    default :
                        break ;
        }
        
        SDL_BlitSurface(tank, &tankSrc, ecran, &pos) ;
        SDL_Flip(ecran) ;
    }
    


    pause(); // Mise en pause du programme

  
    
    
    
    //desallouer_tab_2D(tab, 20,10);
    SDL_FreeSurface(tank_droite) ;
    SDL_FreeSurface(tank_gauche) ;
    SDL_FreeSurface(tank_haut) ;
    SDL_FreeSurface(tank_bas) ;
    SDL_FreeSurface(grass) ;
    //SDL_FreeSurface(tank) ;
    SDL_FreeSurface(mur) ;
    SDL_FreeSurface(terre) ;
    SDL_Quit(); // Arrêt de la SDL

 

    return EXIT_SUCCESS; // Fermeture du programme

}

 





