#include <SDL/SDL.h>
#include <time.h>
#include "define.h"
#include "fonctions_fichiers.h"


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
	j = ((posTank.x + 2)/ 32) ;

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

	printf("On a i = %d et j = %d et tab[i][j] (position du tank)= %c \n",i, j, tab[i][j] );
	printf("Position au dessus du tank)= %c \n", tab[i-1][j] );


	if(tab[i][j-1] == '1' || tab[i2][j2-1] == '1'){
		res = 0;
	}
	printf("posTank.y : %d \n" ,posTank.y);
	printf("posTank.x : %d \n" ,posTank.x);

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
        printf("Map[%d][%d] = %c",i,j,map[i][j]);
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

int hasReached(SDL_Rect posTank,SDL_Rect posFlag){
    
    int iTank,jTank,iFlag,jFlag;
    int boolean = 0;
    jTank =  (posTank.x + (SIZE_SPRITE/2))/32;
    iTank = (posTank.y + (SIZE_SPRITE/2))/32;
    jFlag = (posFlag.x + (SIZE_SPRITE/2))/32;
    iFlag = (posFlag.y + (SIZE_SPRITE/2))/32;

    if(iTank == iFlag && jTank == jFlag){
      boolean = 1;
    }
    return boolean;
}

void jouer(){
  
    char** map = lire_fichier("ecrire") ;
    int continuer = 1;
    int compteur_droite = 0; 
    int a,b,c;
    

    SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL, *grass = NULL ,*tank_haut = NULL,*tank_bas = NULL ,*tank_gauche = NULL,*tank_droite = NULL, *tour = NULL;
    SDL_Surface *bullet = NULL , *flag = NULL;
    SDL_Rect posTank, tankSrc ,posMap,tourSrc,posBullet,posFlag,tourTest;
    SDL_Rect* tabPosTour = genereTourPos(map);
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
    flag = SDL_LoadBMP("flag.bmp");

    /*Gestion de la transparence des sprites*/
   
    SDL_SetColorKey(tank_droite, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_droite->format, 255,255,255));
    SDL_SetColorKey(tank_gauche, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_gauche->format, 255,255,255));
    SDL_SetColorKey(tank_bas, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_bas->format, 255,255,255));
    SDL_SetColorKey(tank_haut, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_haut->format, 255,255,255));
    SDL_SetColorKey(tour, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tour->format, 255,255,255));
    SDL_SetColorKey(bullet, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(bullet->format, 255,255,255));
    SDL_SetColorKey(flag, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(flag->format, 255,255,255));


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
    afficherMap(map,posMap,ecran,terre,mur);

    posTank.x = 64;
    posTank.y = 160;

    posMap.x = 0;
    posMap.y = 0;

    posFlag.x = 64;
    posFlag.y = 32;
    posFlag = genereFlagPos(map);


    /*Pour les tests de tirs*/
    tourTest.x = 5*32;
    tourTest.y =0;

    posBullet.x = 5.32;
    posBullet.y = 0;

    /*a = calculA(tourTest,posBullet);
    b = calculB(tourTest,posBullet);
    c = calculC(tourTest,posBullet);
    int x = -(b*posBullet.y +c)/a;
    int y = -(a*posBullet.x+c)/b;*/


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

                    if(peutDeplacerTankHaut(map,posTank)){ 
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
                     
                    if(peutDeplacerTankBas(map,posTank)){
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
                      

                      if(peutDeplacerTankDroite(map, posTank)){ 
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
                   
                          if(peutDeplacerTankGauche(map, posTank)){       
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

        

        
        /*Affichage carte et tourelle*/
        afficherMap(map,posMap,ecran,terre,mur);  
        afficherTour(tabPosTour,ecran,tour);
        
        /*TEST*/
        //posBullet.x = x;
        //posBullet.y = y;
        //SDL_BlitSurface(tour,NULL,ecran,&tourTest);
        //SDL_BlitSurface(bullet,NULL,ecran,&posBullet);
        /*TEST*/
        /*Verification si joueur a récupéré drapeau*/
        if(hasReached(posTank,posFlag)){
          posFlag = genereFlagPos(map);
        }
        
        SDL_BlitSurface(flag,NULL,ecran,&posFlag);
        SDL_BlitSurface(tank, &tankSrc, ecran, &posTank) ; 
 
        

        SDL_Flip(ecran) ; 
    }

  
    /*Free de tous les tabeaux*/
    //desallouer_tab_2D(tab, 20,10);  
    //free(tab);
    //free(tabPosTour);

    /*Free de toutes les SDL_Surfaces*/
    SDL_FreeSurface(tank_droite) ; 
    SDL_FreeSurface(tank_gauche) ;
    SDL_FreeSurface(tank_haut) ;
    SDL_FreeSurface(tank_bas) ;
    SDL_FreeSurface(grass) ;
    SDL_FreeSurface(tour);
    SDL_FreeSurface(mur) ;
    SDL_FreeSurface(terre) ;
    SDL_FreeSurface(bullet);
}
