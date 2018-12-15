#include <SDL/SDL.h>
#include "fonctions_fichiers.c"
//#include "fonctions_fichiers.h"
#include "jouer.h"
#include "define.h"
#include <SDL/SDL_mixer.h>




void jouer(){
  
    char** map = lire_fichier("ecrire") ;
    int continuer = 1;
    int nbLife = 800;
    tank_t tank2 ;
    tank2 = cons() ;

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
       {
          printf("%s", Mix_GetError());
       }
    printf("je suis dans jouer") ;
    // pour la musique de fond
    Mix_Music *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);  // volume de la musique

    // pour le bruit d'explosion
    Mix_AllocateChannels(32); //Allouer 32 canaux
    Mix_Volume(1, MIX_MAX_VOLUME/5); //Mettre à mi-volume le post 1
    Mix_Chunk *son;//Créer un pointeur pour stocker un .WAV
    Mix_Chunk *son2 ;
    son = Mix_LoadWAV("son.wav"); //Charger un wav dans un pointeur
    son2 = Mix_LoadWAV("Ta Da-SoundBible.com-1884170640.wav") ;
    Mix_VolumeChunk(son, MIX_MAX_VOLUME/2); //Mettre un volume pour ce wav
    Mix_VolumeChunk(son2, MIX_MAX_VOLUME/10); //Mettre un volume pour ce wav



    SDL_Surface *ecran = NULL, *terre = NULL, *mur = NULL, *tank = NULL,*tank_haut = NULL,*tank_bas = NULL ,*tank_gauche = NULL,*tank_droite = NULL, *tour = NULL;
    SDL_Surface *bullet = NULL , *flag = NULL,*explosion = NULL,*life = NULL, *initialise_Pos_Tank = NULL;
    
    SDL_Rect posTank, tankSrc,posMap,posFlag,exploSrc,lifeSrc,posLife;
    
    SDL_Rect* tabPosTour = genereTourPos(map);
    Tir* tabTir = genereTabTir(NB_TOUR);
    SDL_Event event ;

    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)) ;

    /*Chargement des sprites*/
    terre = SDL_LoadBMP("terreBon.bmp") ;
    mur = SDL_LoadBMP("murBon.bmp") ;
    initialise_Pos_Tank = SDL_LoadBMP("tank_bas.bmp") ;
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
    SDL_SetColorKey(initialise_Pos_Tank, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(initialise_Pos_Tank->format, 255,255,255));


    /*Initialisation fiche sprite tank*/
    tank = initialise_Pos_Tank; 
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
    posTank.y = 64;

    posMap.x = 0;
    posMap.y = 0;

    posFlag.x = 64;
    posFlag.y = 32;
    posFlag = genereFlagPos(map, posTank);

    posLife.x = 8;
    posLife.y = 6;

    fire_Down(tabTir);
        int tmp_prec = 0 ;
        int tmp_now = 0 ;

    /* Boucle infini pour jouer tant qu'on a pas perdu ou arreter le programme*/
    while(continuer){
        
        /*Si evenement appel de la fonciton HandleEvent*/
        if(SDL_PollEvent(&event)){
          HandleEvent(event,map,&continuer,&posTank,&tankSrc,tank,tank_haut,tank_droite,tank_gauche,tank_bas);
        }
        
        /*Affichage carte et tourelle*/
        afficherMap(map,posMap,ecran,terre,mur);  
        afficherTour(tabPosTour,ecran,tour);
        
        /*Initialisation, calcul et affichage des tirs*/
        initialise_Tir(tabPosTour,posTank,tabTir);
        calcul_Tir(tabTir);
        afficher_Tir(tabTir,bullet,ecran);

        /*Verification si joueur a récupéré le drapeau*/
        if(hasReached(tank2, posTank,posFlag)){
          posFlag = genereFlagPos(map, posTank);
          Mix_PlayChannel(2, son2, 0) ;
        }
        
        update_monde(tank2) ;
        //print(tank2) ;

        /*Affichage*/
        SDL_BlitSurface(flag,NULL,ecran,&posFlag);
        SDL_BlitSurface(tank, &tankSrc, ecran, &posTank) ; 
        SDL_BlitSurface(life,&lifeSrc,ecran,&posLife);
        int prochain_son = SDL_GetTicks() + 1000 ;
        /*Si joueur touche, decrementation de nbLife et affichage explosion*/
        if(est_Touche(tabTir,posTank)){
          affiche_Explosion(explosion,ecran,posTank,exploSrc);
          nbLife--;
          tmp_now = SDL_GetTicks() ;
          if(tmp_now - tmp_prec > 1000){
            Mix_PlayChannel(1, son, 0);//Joue le son 1 sur le canal 1 ; le joue une fois (0 + 1)
            tmp_prec = tmp_now ;
          }
          if(nbLife>0 ){
            if (nbLife%200 == 0){
              lifeSrc.x += SIZE_SPRITE*2;
            }
          }
          else{
            est_mort(tank2) ; // ne marche pas
            continuer = 0;
            //print(tank2) ;
          }
        }
       /* if (est_mort(tank2)){
          continuer = 0 ;
        }*/
  
        SDL_Flip(ecran) ; 
    }

    /*Free de tous les tabeaux*/
    desallouer_tab_2D(map,10);  
    free(tabTir);
    Mix_FreeChunk(son);//Libération du son 1
    Mix_FreeChunk(son2) ;

    Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio(); //Fermeture de l'API

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
