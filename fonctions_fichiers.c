#include "fonctions_fichiers.h"
#include <SDL/SDL.h>
#define SIZE_SPRITE 32 

char** allouer_tab_2D(int n, int m){
	int i;
	char ** tab = malloc(n*sizeof(char*));
	
	
	for(i = 0 ; i < n ; i++){
		tab[i] = malloc(m*sizeof(char*));
	}
	return tab;
}



/*void desallouer_tab_2D(char** tab, int n){

	int j;
	for(j = 0; j < n ; j++){
		free(tab[j]);
	}
	free(tab);
}*/

void desallouer_tab_2D(char** tab, int dimension1, int dimension2){
    int i,j;
    
    
    for (i = 0 ;i < dimension1 ; i++){
      for (j=0 ; j < dimension2 ; j++){
		free(tab[i]);
      }

    }
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

void deplacerJoueurDroite(int** map, SDL_Rect position){

}

void afficherMap(char** map, SDL_Rect pos,SDL_Surface *ecran,SDL_Surface *terre,SDL_Surface *mur){
	int i,j;
	for(i = 0 ; i < 10 ; i++){
        for (j = 0 ; j < 20 ; j++){
            if(map[i][j] == '1'){
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
}


int peutDeplacerTankHaut(char** tab, SDL_Rect posTank){
	int i,j,i2,j2,res;
	
	i = ((posTank.y + 30 ) /32);
	j = (posTank.x /32) ;
	i2 = ((posTank.y + 30 ) /32);
	j2 = ((posTank.x +30) /32) ;

	res = 1;

	printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position au dessus du tank)= %c \n", tab[i-1][j] );
	if(tab[i-1][j]=='1' || tab[i2-1][j2] == '1'){
		res = 0;
	}
	printf("posTank.y : %d" ,posTank.y );
	

	return res;
}

int peutDeplacerTankDroite(char** tab, SDL_Rect posTank){
	int i,j,i2,j2,res;

	
	i = ((posTank.y + 2)  / 32)  ;
	j = (posTank.x /32) ;
	res = 1;
	i2 = ((posTank.y + 30)  / 32)  ;
	j2 = (posTank.x  /32) ;


	printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position au dessus du tank)= %c \n", tab[i-1][j] );

	if(tab[i][j+1] == '1' || tab[i2][j2+1] == '1'){
		res = 0;
	}
	printf("posTank.y : %d \n" ,posTank.y );
	printf("posTank.x : %d \n" ,posTank.x );

	return res;
}

int peutDeplacerTankBas(char** tab, SDL_Rect posTank){
	int i,j,i2,j2,res;
	
	i = (posTank.y + 2) / 32 ;
	j = (posTank.x / 32) ;

	i2 = (posTank.y + 2) / 32 ;
	j2 = (posTank.x + 30) / 32;

	res = 1;

	printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position en dessous du tank)= %c \n", tab[i-1][j] );

	if(tab[i+1][j]=='1'|| tab[i2+1][j2] == '1'){
		res = 0;
	}
	printf("posTank.y : %d" ,posTank.y );
	

	return res;
}

int peutDeplacerTankGauche(char** tab, SDL_Rect posTank){
	int i,j,i2,j2,res;
	
	i = (posTank.y + 2 )/ 32;
	j = (posTank.x + 30) / 32;
	i2 = (posTank.y + 30 )/ 32;
	j2 = (posTank.x + 30) / 32; 

	res = 1;

	//printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	//printf("Position au dessus du tank)= %c \n",i, j, tab[i-1][j] );


	if(tab[i][j-1] == '1' || tab[i2][j2-1] == '1'){
		res = 0;
	}
	printf("posTank.y : %d \n" ,posTank.y);
	printf("posTank.x : %d \n" ,posTank.x);

	return res;
}


