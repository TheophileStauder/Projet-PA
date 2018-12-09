#include <SDL/SDL.h>
#include <time.h>
#include "define.h"
#include "fonctions_fichiers.h"
#include "jouer.h"



char** allouer_tab_2D(int n, int m){
	int i;
	char ** tab = malloc(n*sizeof(char*));
	
	
	for(i = 0 ; i < n ; i++){
		tab[i] = malloc(m*sizeof(char*));
	}
	return tab;
}

SDL_Rect* allouer_tab_1D(int n){
  SDL_Rect* tab = malloc(n*sizeof(SDL_Rect));
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

void ecrire_fichier(const char* nomFichier, char* chaine){
  FILE* ptrFichier = fopen(nomFichier, "w");
  if (ptrFichier==NULL){ 
      perror("Erroropeningfile");  
  }
  else{
    fputs(chaine, ptrFichier) ;
    if (ferror(ptrFichier)){
      printf("Error writting to nomFichier.txt\n");
    }
    fclose(ptrFichier) ;
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
	j = ((posTank.x +2) /32) ;
	i2 = ((posTank.y + 30 ) /32);
	j2 = ((posTank.x +30) /32) ;

	res = 1;

	/*printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position au dessus du tank)= %c \n", tab[i-1][j] );*/
	
	if(tab[i-1][j]=='1' || tab[i2-1][j2] == '1'){
		res = 0;
	}
	//printf("posTank.y : %d" ,posTank.y );
	

	return res;
}

int peutDeplacerTankDroite(char** tab, SDL_Rect posTank){
	int i,j,i2,j2,res;

	
	i = ((posTank.y + 2)  / 32)  ;
	j = (posTank.x /32) ;
	res = 1;
	i2 = ((posTank.y + 30)  / 32)  ;
	j2 = (posTank.x  /32) ;


	/*printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position au dessus du tank)= %c \n", tab[i-1][j] );*/

	if(tab[i][j+1] == '1' || tab[i2][j2+1] == '1'){
		res = 0;
	}
/*	printf("posTank.y : %d \n" ,posTank.y );
	printf("posTank.x : %d \n" ,posTank.x );*/

	return res;
}

int peutDeplacerTankBas(char** tab, SDL_Rect posTank){
	int i,j,i2,j2,res;
	
	i = (posTank.y + 2) / 32 ;
	j = ((posTank.x + 2)/ 32) ;

	i2 = (posTank.y + 2) / 32 ;
	j2 = (posTank.x + 30) / 32;

	res = 1;

	/*printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position en dessous du tank)= %c \n", tab[i-1][j] );*/

	if(tab[i+1][j]=='1'|| tab[i2+1][j2] == '1'){
		res = 0;
	}
	//printf("posTank.y : %d" ,posTank.y );
	

	return res;
}

int peutDeplacerTankGauche(char** tab, SDL_Rect posTank){
	int i,j,i2,j2,res;
	
	i = (posTank.y + 2 )/ 32;
	j = (posTank.x + 30) / 32;
	i2 = (posTank.y + 30 )/ 32;
	j2 = (posTank.x + 30) / 32; 

	res = 1;

	/*printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position au dessus du tank)= %c \n", tab[i-1][j] );*/


	if(tab[i][j-1] == '1' || tab[i2][j2-1] == '1'){
		res = 0;
	}
	/*printf("posTank.y : %d \n" ,posTank.y);
	printf("posTank.x : %d \n" ,posTank.x);*/

	return res;
}


int calculA(SDL_Rect posTour , SDL_Rect posTank){
  int copiePosTourX = posTour.x;
  int copiePosTourY =  posTour.y;
  int copiePosTankX = posTank.x;
  int copiePosTankY = posTank.y;

  return copiePosTankY-copiePosTourY;
}

int calculB(SDL_Rect posTour, SDL_Rect posTank){
  int copiePosTourX = posTour.x;
  int copiePosTourY =  posTour.y;
  int copiePosTankX = posTank.x;
  int copiePosTankY = posTank.y;


  return copiePosTankX - copiePosTankY;
}

int calculC(SDL_Rect posTour, SDL_Rect posTank){
  int copiePosTourX = posTour.x;
  int copiePosTourY =  posTour.y;
  int copiePosTankX = posTank.x;
  int copiePosTankY = posTank.y;


  return -((copiePosTourX*copiePosTankY) + (copiePosTankX*copiePosTourY));
}

SDL_Rect* genereTourPos(char** map){
  
  int i1 = 0,j1 = 0;
  int i = 0,j = 0;
  int peutPasPoserTour;
  SDL_Rect* tabPosTour = allouer_tab_1D(10);
  srand(time(NULL));
  for(i1=0;i1<10;i1++){
    peutPasPoserTour = 1;
    while(peutPasPoserTour){
      if(map[i][j] == '1'){
        tabPosTour[j1].x = j*SIZE_SPRITE;
        tabPosTour[i1].y = i*SIZE_SPRITE;
       // printf("Map[%d][%d] = %c",i,j,map[i][j]);
        peutPasPoserTour = 0;
        j1++;
      }
      i = rand()%9+0;
      j = rand()%19+0;
      
    }
  }

  return tabPosTour;
}



void afficherTour(SDL_Rect* tabPosTour,SDL_Surface *ecran,SDL_Surface *tour){
  int i;
  for(i=0;i<10;i++){
    SDL_BlitSurface(tour,NULL,ecran,&tabPosTour[i]);
  }
}

SDL_Rect genereFlagPos(char** map){
  int i = 0,j = 0;
  int peutPasPoserFlag = 1;
  SDL_Rect posFlag;
  
  srand(time(NULL));
    
  while(peutPasPoserFlag){
    if(map[i][j] == '0'){
      posFlag.x = j*SIZE_SPRITE;
      posFlag.y = i*SIZE_SPRITE;
      peutPasPoserFlag= 0;
    }
    i = rand()%9+0;
    j = rand()%19+0;    
  }  

  return posFlag;
}
 void next_level(tank_t t){
  /*int l = t->level ;
  t-> level = l++ ;*/
  t->level += 1 ;
 }

 void print(tank_t t){
    printf("level = %d \nmonde = %d\n", t->level, t->monde );
  }

int hasReached(tank_t tank, SDL_Rect posTank,SDL_Rect posFlag){
    
    int iTank,jTank,iFlag,jFlag;
    int boolean = 0;
    jTank =  (posTank.x + (SIZE_SPRITE/2))/32;
    iTank = (posTank.y + (SIZE_SPRITE/2))/32;
    jFlag = (posFlag.x + (SIZE_SPRITE/2))/32;
    iFlag = (posFlag.y + (SIZE_SPRITE/2))/32;

    if(iTank == iFlag && jTank == jFlag){
      boolean = 1;
      next_level(tank) ;
      print(tank);
    }
    return boolean;
}

int get_pv(tank_t t){
  return t->pv ;
}
int get_level(tank_t t){
  return t->level ;
}

int get_monde(tank_t t){
  return t->monde ;
}
int est_mort(tank_t t){
  if(get_pv(t)==0){
    char* monde = (char)(get_monde(t)) ;
    char* level = (char)(get_level(t)) ;
    ecrire_fichier("ecriture_fichier",level) ;
    ecrire_fichier("ecriture_fichier", " ");
    ecrire_fichier("ecriture_fichier", monde) ;
    return 1 ;
  }
  return 0 ;
}