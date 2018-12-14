typedef struct Tir Tir;


/*Structure de tir dans laquelle on met l'équation de droite(a,b,c) d'un tir, un booléen (fire) 
pour savoir si la structure doit être utilisé et enfin un enum (position_tank) pour savoir ou se trouve le tank par rapport à la tour*/
/*pos_x et pos_y pour la position de posBullet sans arrondi (qu'on passe dans posBullet au moment de l'affichage) et dir_x et dir_y pour calculer la pos*/
struct Tir{
	SDL_Rect posBullet;
	int fire;
	int angle;
	float pos_x;
	float pos_y;
	float dir_x;
	float dir_y;

};

typedef struct s_tank { 
    //SDL_Surface *tank; 
    int level;
    int monde ;
    //int pv ;
  } s_tank_t, *tank_t ;