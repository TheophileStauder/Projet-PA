#include <SDL.h>
#include "fonctions_fichiers.h"
#include <time.h>
#include <math.h>
#define SIZE 32 
#define WIDTH 640 
#define HEIGHT 320 

char** allouer_tab_2D(int n, int m){
	int i;
	char ** tab = malloc(n*sizeof(char*));
	
	
	for(i = 0 ; i < n ; i++){
		tab[i] = malloc(m*sizeof(char*));
	}
	return tab;
}



void desallouer_tab_2D(char** tab, int n){

	int j;
	for(j = 0; j < n ; j++){
		free(tab[j]);
	}
	free(tab);
}

void afficher_tab_2D(char** tab, int n, int m){
	 int i , j;
	 
	 for (i = 0 ; i < n ; i++){
		for( j = 0 ; j < m ; j ++){
			printf("%d",tab[i][m] );
		  
		}
	 }
}


char** lire_fichier(const char* nomFichier){
	
	int c , n = 0;
	char** tab = allouer_tab_2D(13,6);
	int i = 0;
	int j = 0;
	
	FILE* ptrFichier = fopen(nomFichier, "r");
	
	if (ptrFichier==NULL)  
		perror("Erroropeningfile");  
	else{

		do{
		    c = fgetc(ptrFichier);
		    if(c=='\n'){
		      printf("\n");

		      i++; 
		      j = 0 ;
		    }
		   
		    if(c!=10 && c!=-1){
			tab[i][j] = c;
			n++ ;
		    }
		     if(c!='\n'){
		      j++ ;
                    }
		}while(c != EOF);

	}
	fclose(ptrFichier);  
	//printf("File contains %d caracteres\n",n);  
	
	return tab;
  
}


void pause();


int main(int argc, char *argv[])

{
  int i, j ;
  char** tab = lire_fichier("ecrire") ;

    int continuer, colorkey ;
    int level = 1 ;
        
    SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL, *grass = NULL ;
    SDL_Rect pos, tankSrc ;//, posGrass ;
    SDL_Event event ;
    
    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    
   

    continuer = 1 ;

    ecran =SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    SDL_WM_SetCaption("Jeu programmation avancée", NULL);
    
    terre = SDL_LoadBMP("terreBon.bmp") ;
    mur = SDL_LoadBMP("murBon.bmp") ;
    tank = SDL_LoadBMP("tank.bmp") ;
    grass = SDL_LoadBMP("grass.bmp") ;
    
    colorkey = SDL_MapRGB(ecran->format, 0, 0, 0);
    SDL_SetColorKey(tank, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
    tankSrc.x = 0;
    tankSrc.y = 0;
    tankSrc.w = SIZE;
    tankSrc.h = SIZE;  
    /*
    posGrass.x = 0 ;
    posGrass.y = 0 ;
*/
   
    //position mur et terre
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
            pos.x = pos.x + SIZE ;
        }
        pos.y = pos.y + SIZE ;
        pos.x = 0 ;
    }
    pos.x = 0 ;
    pos.y = 0 ;
    
    SDL_BlitSurface(tank, &tankSrc, ecran, &pos) ;
    
    srand(time(NULL));
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

/*
    SDL_EnableKeyRepeat(10, 10) ;
    while(continuer){
        
        SDL_WaitEvent(&event) ;
        switch(event.type){
            case SDL_QUIT :
                continuer = 0 ;
                break ;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym){
                    case SDLK_UP :
                      //  if(tankSrc.y>=32){
                        tankSrc.y -= SIZE ;
                     //   }
                        break ;
                    case SDLK_DOWN :
                       // if (tankSrc.y <=288){
                        tankSrc.y += SIZE ;
                     //   }
                        break ;
                    case SDLK_RIGHT :
                        if (tankSrc.w >=160){
                            tankSrc.w = SIZE ;
                        }
                      //  if (tankSrc.x <= 6){
                        tankSrc.x += SIZE ;
                      //  }
                        break ;
                    case SDLK_LEFT :
                        if (tankSrc.x >=32){
                        tankSrc.x -= SIZE ;
                        }
                        break ;
                    default :
                        break ;
                }
                break ;
                    default :
                        break ;
        }
        
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)) ;
        SDL_BlitSurface(tank, &tankSrc, ecran, &tankSrc) ;
        SDL_Flip(ecran) ;
    }
    */

    

    pause(); // Mise en pause du programme

    
    SDL_FreeSurface(grass) ;
    SDL_FreeSurface(tank) ;
    SDL_FreeSurface(mur) ;
    SDL_FreeSurface(terre) ;
    SDL_Quit(); // Arrêt de la SDL

 

    return EXIT_SUCCESS; // Fermeture du programme

}

 

void pause()

{

    int continuer = 1;

    SDL_Event event;

 

    while (continuer)

    {

        SDL_WaitEvent(&event);

        switch(event.type)

        {

            case SDL_QUIT:

                continuer = 0;

        }

    }

}



