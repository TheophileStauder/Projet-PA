#include <SDL/SDL.h>
#include "fonctions_fichiers.c"
#include "jouer.h"



void jouer(){
	
	  char** tab = lire_fichier("ecrire") ;
    int continuer = 1;
    int compteur_droite = 0; 
    int a,b;
    SDL_Rect* tabPosTour = genereTourPos(tab);

	  SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL, *grass = NULL ,*tank_haut = NULL,*tank_bas = NULL ,*tank_gauche = NULL,*tank_droite = NULL, *tour = NULL;
    SDL_Surface *bullet = NULL;
    SDL_Rect posTank, tankSrc ,posMap,tourSrc,posBullet;
    SDL_Event event ;

    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)) ;

	  /*Chargement des sprites*/
    terre = SDL_LoadBMP("terreBon.bmp") ;
    mur = SDL_LoadBMP("murBon.bmp") ;
    tank_haut = SDL_LoadBMP("tank_haut.bmp") ;
    tank_bas = SDL_LoadBMP("tank_bas.bmp") ;
    tank_droite = SDL_LoadBMP("tank_droite.bmp") ;
    tank_gauche = SDL_LoadBMP("tank_gauche.bmp") ;
    grass = SDL_LoadBMP("grass.bmp") ;
    tour = SDL_LoadBMP("tourelle.bmp") ;
    bullet = SDL_LoadBMP("bullet.bmp");

    /*Gestion de la transparence des sprites*/
   
    SDL_SetColorKey(tank_droite, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_droite->format, 255,255,255));
    SDL_SetColorKey(tank_gauche, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_gauche->format, 255,255,255));
    SDL_SetColorKey(tank_bas, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_bas->format, 255,255,255));
    SDL_SetColorKey(tank_haut, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_haut->format, 255,255,255));
    SDL_SetColorKey(tour, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tour->format, 255,255,255));
    SDL_SetColorKey(bullet, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(bullet->format, 255,255,255));
    
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
    
    /*Afficher la carte*/
    afficherMap(tab,posMap,ecran,terre,mur);

    posTank.x = 64;
    posTank.y = 160;

    posMap.x = 0;
    posMap.y = 0;

    
  

    /* Boucle infini pour jouer tant qu'on a pas perdu ou arreter le programme*/
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
                        /*if(compteur_droite > 10){pokpok<3
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
        afficherTour(tabPosTour,ecran,tour);
        SDL_BlitSurface(tank, &tankSrc, ecran, &posTank) ; 
 
        

        SDL_Flip(ecran) ; 
    }
    


    //pause(); // Mise en pause du programme 

  
    
    
    /*Free de toutes les SDL_Surfaces*/

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
    SDL_FreeSurface(bullet);
}