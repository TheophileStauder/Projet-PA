#include <SDL/SDL.h>
#include <time.h>
#include "define.h"
#include "fonctions_fichiers.h"
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
	
	return tab;
  
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
void fire_Down(Tir* tabTir){
  int i;
  for(i=0;i<NB_TOUR;i++){
    tabTir[i].fire = 0;
  }
}
void initialise_Tir(SDL_Rect* tabPosTour,SDL_Rect posTank,Tir* tabTir){
    srand(time(NULL));

    int num_tour = (rand()%(NB_TOUR));
    if(tabTir[num_tour].fire != 1){
      tabTir[num_tour].fire = 1;
      tabTir[num_tour].pos_x = tabPosTour[num_tour].x ;
      tabTir[num_tour].pos_y = tabPosTour[num_tour].y ;
      float angle = calcul_Angle(tabPosTour[num_tour],posTank);
      tabTir[num_tour].dir_x = sin(angle)*VELOCITY;
      tabTir[num_tour].dir_y = cos(angle)*VELOCITY;
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
      if(tabTir[i].pos_x < 0 || tabTir[i].pos_x > 640 || tabTir[i].pos_y < 0 || tabTir[i].pos_y > 320){tabTir[i].fire = 0;}
    }
  }
}

int est_Touche(Tir* tabTir,SDL_Rect posTank){
  int i;
  int res = 0;
  for(i=0;i<NB_TOUR;i++){
    if((tabTir[i].posBullet.x > posTank.x && (tabTir[i].posBullet.x < (posTank.x + SIZE_SPRITE))) && ((tabTir[i].posBullet.y > posTank.y) && (tabTir[i].posBullet.y < (posTank.y +SIZE_SPRITE)))){res = 1;}
  }
  return res;
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
                          
                          *tank = *tank_haut;
                          tankSrc->y = 0;  

                          if (tankSrc->x >191){
                           tankSrc->x = 0 ;
                          }
                          tankSrc->x += SIZE_SPRITE; 
                          posTank->y += 2;  
                          printf("SrcX = %d\n",tankSrc->x  );            
                          printf("SrcY = %d\n",tankSrc->y  );             
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



void jouer(){
  
    char** map = lire_fichier("ecrire") ;
    int continuer = 1;
    int nbLife = 1000;

    SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL,*tank_haut = NULL,*tank_bas = NULL ,*tank_gauche = NULL,*tank_droite = NULL, *tour = NULL;
    SDL_Surface *bullet = NULL , *flag = NULL,*explosion = NULL,*life = NULL;
    SDL_Rect posTank, tankSrc,posMap,posFlag,exploSrc,lifeSrc,posLife;
    SDL_Rect* tabPosTour = genereTourPos(map);
    Tir* tabTir = genereTabTir(NB_TOUR);
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
    tour = SDL_LoadBMP("tourelle.bmp") ;
    bullet = SDL_LoadBMP("bullet.bmp");
    flag = SDL_LoadBMP("flag.bmp");
    explosion = SDL_LoadBMP("explosion.bmp");
    life = SDL_LoadBMP("life.bmp");

    /*Gestion de la transparence des sprites*/
    SDL_SetColorKey(tank_droite, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_droite->format, 255,255,255));
    SDL_SetColorKey(tank_gauche, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_gauche->format, 255,255,255));
    SDL_SetColorKey(tank_bas, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_bas->format, 255,255,255));
    SDL_SetColorKey(tank_haut, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tank_haut->format, 255,255,255));
    SDL_SetColorKey(tour, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tour->format, 255,255,255));
    SDL_SetColorKey(bullet, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(bullet->format, 255,255,255));
    SDL_SetColorKey(flag, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(flag->format, 255,255,255));
    SDL_SetColorKey(explosion, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(explosion->format, 255,255,255));
    SDL_SetColorKey(life, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(life->format, 106,116,126));
    


    /*Initialisation fiche sprite tank*/
    tank = tank_bas; 
    tankSrc.x = 0;
    tankSrc.y = 0;
    tankSrc.w = SIZE_SPRITE;
    tankSrc.h = SIZE_SPRITE;  

    exploSrc.x = 0;
    exploSrc.y = 0;
    exploSrc.w = SIZE_SPRITE;
    exploSrc.h = SIZE_SPRITE; 

    lifeSrc.x = 0;
    lifeSrc.y = 0;
    lifeSrc.w = SIZE_SPRITE;
    lifeSrc.h = SIZE_SPRITE; 
  
    
    /*Chargement de la map, positionement des sprites mur et terre*/
    afficherMap(map,posMap,ecran,terre,mur);

    posTank.x = 64 + (12*32);
    posTank.y = 160;

    posMap.x = 0;
    posMap.y = 0;

    posFlag.x = 64;
    posFlag.y = 32;
    posFlag = genereFlagPos(map);

    posLife.x = 10;
    posLife.y = 10;

    fire_Down(tabTir);

    /* Boucle infini pour jouer tant qu'on a pas perdu ou arreter le programme*/
    while(continuer){
        
        /*Si evenement appel de la fonciton HandleEvent*/
        if(SDL_PollEvent(&event)){
          HandleEvent(event,map,&continuer,&posTank,&tankSrc,tank,tank_haut,tank_droite,tank_gauche,tank_bas);
        }
        
        /*Affichage carte et tourelle*/
        afficherMap(map,posMap,ecran,terre,mur);  
        afficherTour(tabPosTour,ecran,tour);
        
    
        initialise_Tir(tabPosTour,posTank,tabTir);
        calcul_Tir(tabTir);
        afficher_Tir(tabTir,bullet,ecran);

        /*Verification si joueur a récupéré le drapeau*/
        if(hasReached(posTank,posFlag)){
          posFlag = genereFlagPos(map);
        }
        
        SDL_BlitSurface(flag,NULL,ecran,&posFlag);
        SDL_BlitSurface(tank, &tankSrc, ecran, &posTank) ; 
        SDL_BlitSurface(life,&lifeSrc,ecran,&posLife);
        if(est_Touche(tabTir,posTank)){
          printf("TOUCHE\n");
          affiche_Explosion(explosion,ecran,posTank,exploSrc);
          nbLife--;
          if(nbLife>0 ){lifeSrc.x += SIZE_SPRITE;}
          else{continuer = 0;}
        }
  
        SDL_Flip(ecran) ; 
    }

    /*Free de tous les tabeaux*/
    desallouer_tab_2D(map,10);  
    free(tabTir);

    /*Free de toutes les SDL_Surfaces*/
    //SDL_FreeSurface(tank_droite) ; 
    //SDL_FreeSurface(tank_gauche) ;
    //SDL_FreeSurface(tank_haut) ;
    //SDL_FreeSurface(tank_bas) ;
    //SDL_FreeSurface(tank);
    SDL_FreeSurface(life);
    SDL_FreeSurface(flag);
    SDL_FreeSurface(tour);
    SDL_FreeSurface(mur) ;
    SDL_FreeSurface(terre) ;
    SDL_FreeSurface(bullet);
}
