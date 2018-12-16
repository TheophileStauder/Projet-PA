#include <SDL/SDL.h>
#include <time.h>
#include "define.h"
#include "fonctions_fichiers.h"
#include "jouer.h"
#include <math.h>


/*Alloue un tableau de char à 2 dimension*/
char** allouer_tab_2D(int n, int m){
	int i;
	char ** tab = malloc(n*sizeof(char*));
	
	
	for(i = 0 ; i < n ; i++){
		tab[i] = malloc(m*sizeof(char*));
	}
	return tab;
}

/*Alloue un tableau de SDL_Rect*/
SDL_Rect* allouer_tab_1D_Rect(int n){
  SDL_Rect* tab = malloc(n*sizeof(SDL_Rect));
  return tab;
}

Tir* allouer_tab_1D_Tir(int n){
  Tir* tab = malloc(n*sizeof(Tir));
  return tab;
}


void desallouer_tab_2D(char** tab, int n){

	int j;
	for(j = 0; j < n ; j++){
		free(tab[j]);
	}
	//free(tab);
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
		perror("Error opening file");  
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
	return tab;
  
}

void ecrire_fichier(const char* nomFichier, char* chaine){
  FILE* ptrFichier = fopen(nomFichier, "w+");
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




int peutDeplacerTankHaut(char** tab, SDL_Rect *posTank){
  int i,j,i2,j2,res;
  
  i = ((posTank->y + 30 ) /32);
  j = ((posTank->x +4) /32) ;
  i2 = ((posTank->y + 30 ) /32);
  j2 = ((posTank->x +28) /32) ;
  
  res = 1;
  
  if(tab[i-1][j]=='1' || tab[i2-1][j2] == '1'){
    res = 0;
  }

  return res;
}

int peutDeplacerTankDroite(char** tab, SDL_Rect *posTank){
  int i,j,i2,j2,res;

  
  i = ((posTank->y + 4) / 32)  ;
  j = (posTank->x /32) ;
  res = 1;
  i2 = ((posTank->y + 28)  / 32)  ;
  j2 = (posTank->x  /32) ;

  if(tab[i][j+1] == '1' || tab[i2][j2+1] == '1'){
    res = 0;
  }

  return res;
}

int peutDeplacerTankBas(char** tab, SDL_Rect *posTank){
  int i,j,i2,j2,res;
  
  i = (posTank->y + 2) / 32 ;
  j = ((posTank->x + 4)/ 32) ;

  i2 = (posTank->y + 2) / 32 ;
  j2 = (posTank->x + 28) / 32;

  res = 1;

  if(tab[i+1][j]=='1'|| tab[i2+1][j2] == '1'){
    res = 0;
  }

  return res;
}

int peutDeplacerTankGauche(char** tab, SDL_Rect *posTank){
  int i,j,i2,j2,res;
  
  i = (posTank->y + 4 )/ 32;
  j = (posTank->x + 30) / 32;
  i2 = (posTank->y + 28)/ 32;
  j2 = (posTank->x + 30) / 32; 

  res = 1;

  if(tab[i][j-1] == '1' || tab[i2][j2-1] == '1'){
    res = 0;
  }

  return res;
}


float calcul_Angle(SDL_Rect posTour , SDL_Rect posTank){
  int dir_x = (posTank.x-posTour.x);
  int dir_y= (posTank.y-posTour.y);
  float res = atan2(dir_x,dir_y);
  return res;
}

SDL_Rect genereFlagPos(char** map,SDL_Rect posTank){
  int i = 0,j = 0;
  int peutPasPoserFlag = 1;
  SDL_Rect posFlag;
  
  srand(time(NULL));
    
  while(peutPasPoserFlag){
    if(map[i][j] == '0'){
      int x = posTank.x - (j*SIZE_SPRITE);
      int y = posTank.y - (i*SIZE_SPRITE);
      int distance = (int)(sqrt((x*x)+(y*y)));
      if(distance > 200){
        posFlag.x = j*SIZE_SPRITE;
        posFlag.y = i*SIZE_SPRITE;
        peutPasPoserFlag= 0;
      }
    }
    i = rand()%9+0;
    j = rand()%19+0;    
  }  

  return posFlag;
}


Tir* genereTabTir(int n){
  Tir* tabTir = allouer_tab_1D_Tir(n);
  return tabTir;
}

void afficherTour(SDL_Rect* tabPosTour,SDL_Surface *ecran,SDL_Surface *tour){
  int i;
  for(i=0;i<NB_TOUR;i++){
    SDL_BlitSurface(tour,NULL,ecran,&tabPosTour[i]);
  }
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
    }
    return boolean;
}

void fire_Down(Tir* tabTir){
  int i;
  for(i=0;i<NB_TOUR;i++){
    tabTir[i].fire = 0;
  }
}

void initialise_Tir(SDL_Rect* tabPosTour,SDL_Rect posTank,Tir* tabTir,float vitesse){
    srand(time(NULL));

    int num_tour = (rand()%(NB_TOUR));
    if(tabTir[num_tour].fire != 1){
      tabTir[num_tour].fire = 1;
      tabTir[num_tour].pos_x = tabPosTour[num_tour].x ;
      tabTir[num_tour].pos_y = tabPosTour[num_tour].y ;
      float angle = calcul_Angle(tabPosTour[num_tour],posTank);
      tabTir[num_tour].dir_x = sin(angle)*vitesse;
      tabTir[num_tour].dir_y = cos(angle)*vitesse;
      printf("initialise_Tir\n");
    }
}

void calcul_Tir(Tir* tabTir){
  int i;
  for(i=0;i<NB_TOUR;i++){
    if(tabTir[i].fire == 1 ){
        tabTir[i].pos_x += tabTir[i].dir_x;
        tabTir[i].pos_y += tabTir[i].dir_y;
    }
  }
}

void afficher_Tir(Tir* tabTir,SDL_Surface *bullet,SDL_Surface *ecran){
  int i;
  for(i=0;i<NB_TOUR;i++){
    if(tabTir[i].fire == 1 ){
      tabTir[i].posBullet.x = tabTir[i].pos_x;
      tabTir[i].posBullet.y = tabTir[i].pos_y;
      SDL_BlitSurface(bullet,NULL,ecran,&tabTir[i].posBullet);
      if(tabTir[i].pos_x < 0 || tabTir[i].pos_x > 640 || tabTir[i].pos_y < 0 || tabTir[i].pos_y > 320){
        tabTir[i].fire = 0;
      }
    }
  }
}

int est_Touche(Tir* tabTir,SDL_Rect posTank){
  int i;
  int res = 0;
  for(i=0;i<NB_TOUR;i++){
    if((tabTir[i].posBullet.x >= posTank.x && (tabTir[i].posBullet.x <= (posTank.x + SIZE_SPRITE))) && ((tabTir[i].posBullet.y >= posTank.y-5) && (tabTir[i].posBullet.y <= (posTank.y +SIZE_SPRITE )))){res = 1;}
  }
  return res;
}

SDL_Rect* genereTourPos(char** map){
  
  int i1 = 0,j1 = 0;
  int i = 0,j = 0;
  int peutPasPoserTour;
  SDL_Rect* tabPosTour = allouer_tab_1D_Rect(NB_TOUR);
  srand(time(NULL));
  for(i1=0;i1<10;i1++){
    peutPasPoserTour = 1;
    while(peutPasPoserTour){
      if(map[i][j] == '1' && (i!= 0 && j !=0)){
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

void affiche_Explosion(SDL_Surface* explosion,SDL_Surface *ecran,SDL_Rect posTank,SDL_Rect exploSrc){
  exploSrc.x = 0;
  SDL_BlitSurface(explosion,&exploSrc,ecran,&posTank);
  exploSrc.x += SIZE_SPRITE;
  SDL_BlitSurface(explosion,&exploSrc,ecran,&posTank);
  exploSrc.x += SIZE_SPRITE;
  SDL_BlitSurface(explosion,&exploSrc,ecran,&posTank);
}




  void HandleEvent(SDL_Event event, char ** map,int *continuer, SDL_Rect *posTank,SDL_Rect *tankSrc, SDL_Surface *tank,SDL_Surface *tank_haut,SDL_Surface *tank_droite,SDL_Surface *tank_gauche,SDL_Surface *tank_bas){
  switch(event.type){
            case SDL_QUIT :
                *continuer = 0 ;
                break ;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym){
                    case SDLK_UP : 

                    if(peutDeplacerTankHaut(map,posTank)){ 
                      
                      *tank = *tank_haut;
                      tankSrc->y = 0;
                      if (tankSrc->x >191){
                         tankSrc->x = 0 ;
                      }

                      tankSrc->x += SIZE_SPRITE;   
                      posTank->y -= 2;
                    }

                    break ;
                    

                    case SDLK_DOWN :
                     
                      if(peutDeplacerTankBas(map,posTank)){
                          
                          *tank = *tank_bas;
                          tankSrc->y = 0;  

                          if (tankSrc->x >191){
                           tankSrc->x = 0 ;
                          }
                          tankSrc->x += SIZE_SPRITE; 
                          posTank->y += 2;  
                       
                      }


                        break ;
                    case SDLK_RIGHT :  
                    

                      if(peutDeplacerTankDroite(map, posTank)){ 
                          
                          *tank = *tank_droite;
                          tankSrc->x = 0;  

                          if (tankSrc->y >191){
                           tankSrc->y = 0 ;
                          }
                          tankSrc->y += SIZE_SPRITE; 
                          if (posTank->x <= WIDTH - SIZE_SPRITE){ 
                            posTank->x += 2;
                          }
                      }
                      
                    break ;
                    
                    case SDLK_LEFT :   
                 
                        if(peutDeplacerTankGauche(map, posTank)){  
                              
                            *tank = *tank_gauche;
                            tankSrc->x = 0;
                            if (tankSrc->y >191){  
                              tankSrc->y = 0 ;
                            }
                            tankSrc->y += SIZE_SPRITE;   
                            posTank->x -= 2; 
                        }

                    break ;
                      default :
                        break ;
                }
                break ;
                    default :
                        break ;
        }
}


 void next_level(tank_t t){
    t->level ++ ;

 }

 void print(tank_t t){
    printf("\nlevel = %d \nmonde = %d\n ", t->level, t->monde);
  }



int get_level(tank_t t){
  return t->level ;
}

int get_monde(tank_t t){
  return t->monde ;
}


void update_monde(tank_t t){
    t->monde ++ ;
    t->level = 0 ;
  
  printf("MONDE : %d\n",t->monde );
  printf("LEVEL: %d\n",t->level );
}

/* ecrit le score dans ecriture_fichier ma fait une erreur de seg*/
void est_mort(tank_t t){
  char monde[2] ;
  char level[2] ;
  sprintf(monde, "%d", t->monde) ;
  sprintf(level, "%d", t->level) ;
  printf("je suis dans estmort\n");
  printf("char monde = %s et char level = %s\n", monde, level);
  char res[4] ;
  res[0] = level[0] ;
  res[1] = monde[0] ;
  printf("et res = %s\n",res );
  ecrire_fichier("ecriture_fichier",res) ;

 }



tank_t cons(){
      
        tank_t a = (tank_t) malloc(sizeof(s_tank_t));
        a->level = 0;
        a->monde = 1 ;
        return a ; 
    }

