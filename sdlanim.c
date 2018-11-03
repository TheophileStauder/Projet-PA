#include <SDL.h>
#include "fonctions_fichiers.h"

#include <math.h>
#define SIZE 32 ;

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
		    else{
		      j++ ;
		    }
		    if(c!=10 && c!=-1){
			tab[i][j] = c;
			n++ ;
		    }
		}while(c != EOF);

	}
	fclose(ptrFichier);  
	//printf("File contains %d caracteres\n",n);  
	
	return tab;
  
}

void pause();


SDL_Rect pos, tankSrc ;
int gameover, x, y ;
char** tab ;
void HandleEvent(SDL_Event event)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    gameover = 1;
    break;
			
    /* handle the keyboard */
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      gameover = 1;
      break;
    
    case SDLK_LEFT:
        x = tankSrc.x ;
        y = tankSrc.y ;
        if(tab[x][y]=='0'){
            tankSrc.x -= SIZE ;
        }
      
      break;
    case SDLK_RIGHT:
         x = tankSrc.x ;
        y = tankSrc.y ;
        if(tab[x][y]=='0'){
            tankSrc.x += SIZE ;
        }
      
      break;
    
    case SDLK_UP:
         x = tankSrc.x ;
        y = tankSrc.y ;
        if(tab[x][y]=='0'){
            tankSrc.y -= SIZE ;
        }
      break;
      case SDLK_DOWN:
           x = tankSrc.x ;
        y = tankSrc.y ;
        if(tab[x][y]=='0'){
            tankSrc.y += SIZE ;
        }
          
      break;
      default :
          break ;
  }
    break;
    
    /*  default :
          break ;*/
  }
}


 

int main(int argc, char *argv[])

{
 // lire fichier *********************************   
    int c , n = 0;
	tab = allouer_tab_2D(13,6);
	int i = 0;
	int j = 0;
	
	FILE* ptrFichier = fopen("ecrire", "r");
	
	if (ptrFichier==NULL)  
		perror("Erroropeningfile");  
	else{

		do{
		    c = fgetc(ptrFichier);
		    if(c=='\n'){
		     // printf("\n");

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


        
        //fin lire fichier

        
        
    SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL ;
   // SDL_Rect pos, tankSrc ;
    
    tankSrc.x = 0;
    tankSrc.y = 0;
    tankSrc.w = SIZE;
    tankSrc.h = SIZE;  
    
    
    
    //position mur et terre
    pos.x = 0 ;
    pos.y = 0 ;
    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    gameover = 0 ;

    ecran =SDL_SetVideoMode(640, 320, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    
    
    SDL_WM_SetCaption("Jeu programmation avancée", NULL);
    terre = SDL_LoadBMP("terreBon.bmp") ;
    mur = SDL_LoadBMP("murBon.bmp") ;
    tank = SDL_LoadBMP("tank.bmp") ;
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
    tank = SDL_LoadBMP("tank.bmp") ;
    SDL_BlitSurface(tank, &tankSrc, ecran, &pos) ;

     /* while (!gameover)
    {
      SDL_Event event;*/
		
      /* look for an event */
     /* if (SDL_PollEvent(&event)) {
	HandleEvent(event);
      }
        SDL_BlitSurface(tank, &tankSrc, ecran, &pos) ;
    }*/

    pause(); // Mise en pause du programme

 

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



