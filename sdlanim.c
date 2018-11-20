#include <SDL/SDL.h>
#include <SDL_image.h>
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

enum{MUR,TERRE,TANK};





int main(int argc, char *argv[]) 

{
   
    char** tab = lire_fichier("ecrire") ;

    int level = 1 ;
    int continuer = 1 ;
    int compteur_droite = 0;

    /*Declaration des variables surfaces*/
    SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL, *grass = NULL ,*tank_haut = NULL,*tank_bas = NULL ,*tank_gauche = NULL,*tank_droite = NULL, *tour = NULL;
    SDL_Rect posTank, tankSrc ,posMap, posTour,tourSrc;
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
    tour = SDL_LoadBMP("tourelle.bmp") ;

    /*Gestion de la transparence des sprites*/
   
    SDL_SetColorKey(tank_droite, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_droite->format, 255,255,255));
    SDL_SetColorKey(tank_gauche, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_gauche->format, 255,255,255));
    SDL_SetColorKey(tank_bas, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_bas->format, 255,255,255));
    SDL_SetColorKey(tank_haut, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_haut->format, 255,255,255));
    SDL_SetColorKey(tour, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tour->format, 255,255,255));
    
    /*Initialisation fiche sprite tank*/
    tank = tank_bas; 
    tankSrc.x = 0;
    tankSrc.y = 0;
    tankSrc.w = SIZE_SPRITE;
    tankSrc.h = SIZE_SPRITE;  

    tourSrc.x = 0;
    tourSrc.y = 0;
    tourSrc.w = SIZE_SPRITE;
    tourSrc.h = SIZE_SPRITE;  
  
    
    /*Chargement de la map, positionement des sprites mur et terre*/
    posTank.x = 0 ;
    posTank.y = 0 ;

    posMap.x = 0;
    posMap.y = 0;

    posTour.x = 4*32;
    posTour.y = 4*32;
    
    /*Afficher la carte*/
    afficherMap(tab,posMap,ecran,terre,mur);

    

    //srand(time(NULL)); 
    if (level){
      /*pos.x = (rand()%WIDTH/SIZE + 1) ; 
      pos.y = (rand()%HEIGHT/SIZE + 1) ;  */
      posTank.x = 64 ;
      posTank.y = 160 ;
   
     // printf("position aleatoire = (%d, %d)  tab[i][j] = %c\n\n",i,j, tab[i][j]) ;
      SDL_BlitSurface(grass, NULL, ecran, &posMap) ;
    }
    /*  while (tab[i][j]=='1'){
	pos.x = (rand()%WIDTH/SIZE + 1)*SIZE;
        pos.y = (rand()%HEIGHT/SIZE + 1) *SIZE;  
	i = pos.x ;
        j = pos.y ;
      }
      SDL_BlitSurface(grass, NULL, ecran, &pos) ;
*/
      /*    
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
  */

    
    while(continuer){
        
        SDL_WaitEvent(&event) ;
        switch(event.type){
            case SDL_QUIT :
                continuer = 0 ;
                break ;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym){
                    case SDLK_UP : 

                    if(peutDeplacerTankHaut(tab,posTank)){ 
                      tank = tank_haut;
                      tankSrc.y = 0;
                      if (tankSrc.x >191){
                         tankSrc.x = 0 ;
                      }
                      tankSrc.x += SIZE_SPRITE;   
                      posTank.y -= 2;
                    }

                    break ;
                    

                    case SDLK_DOWN :
		                 
                    if(peutDeplacerTankBas(tab,posTank)){
                        tank = tank_bas;
                        tankSrc.y = 0;
                        if (tankSrc.x >191){  
                            tankSrc.x = 0 ;
                        } 
                        /*if(compteur_droite > 10){
                          tankSrc.x += SIZE_SPRITE; 
                          compteur_droite = 0;
                        }*/ 
                        tankSrc.x += SIZE_SPRITE; 
                        posTank.y += 2;    
                        compteur_droite ++;
                         
                    }


                        break ;
              		    case SDLK_RIGHT :  
                      

                      if(peutDeplacerTankDroite(tab, posTank)){ 
                          tank = tank_droite;
                          tankSrc.x = 0;  
                          

                          if (tankSrc.y >191){
                           tankSrc.y = 0 ;
                          }
                          tankSrc.y += SIZE_SPRITE; 
                          if (posTank.x <= WIDTH - SIZE_SPRITE){ 
                            posTank.x += 2;
                          }
                    }
		                    
                      break ;
                    
		                  case SDLK_LEFT :   
		               
                          if(peutDeplacerTankGauche(tab, posTank)){       
                              tank = tank_gauche;
                              tankSrc.x = 0;
                              if (tankSrc.y >191){  
                                tankSrc.y = 0 ;
                              }
                              tankSrc.y += SIZE_SPRITE;  
                              posTank.x -= 2; 
                          }

                      break ;
                      default :
                        break ;
                }
                break ;
                    default :
                        break ;
        }
        afficherMap(tab,posMap,ecran,terre,mur); 
        SDL_BlitSurface(tour, &tourSrc,ecran, &posTour);
        
        SDL_BlitSurface(tank, &tankSrc, ecran, &posTank) ;

        

        SDL_Flip(ecran) ;
    }
    


    pause(); // Mise en pause du programme

  
    
    
    
    //desallouer_tab_2D(tab, 20,10);  
    SDL_FreeSurface(tank_droite) ; 
    SDL_FreeSurface(tank_gauche) ;
    SDL_FreeSurface(tank_haut) ;
    SDL_FreeSurface(tank_bas) ;
    SDL_FreeSurface(grass) ;
    SDL_FreeSurface(tour);
    //SDL_FreeSurface(tank) ;
    SDL_FreeSurface(mur) ;
    SDL_FreeSurface(terre) ;
    SDL_Quit(); // Arrêt de la SDL

 

    return EXIT_SUCCESS; // Fermeture du programme

}

 





