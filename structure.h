typedef struct Tir Tir;


/*Structure de tir dans laquelle on met l'équation de droite(a,b,c) d'un tir , un entier (velocity) pour moduler la vitesse de la balle, un booléen (fire) 
pour savoir si la structure doit être utilisé et enfin un enum (position_tank) pour savoir ou se trouve le tank par rapport à la tour*/
struct Tir{
	SDL_Rect posBullet;
	SDL_Rect objectif;
	int a;
	int b;
	long c;
	int velocity;
	int fire;
	int position_tank;
};


/*POUBELLLE TEMP

if(copiePosTankX < tourTest.x && copiePosTankY > tourTest.y){
              posBullet.y ++;
              posBullet.x = (int)(-(b*posBullet.y + c)/a);
              printf(" 1A\n");
            }

            if(copiePosTankX < tourTest.x && copiePosTankY < tourTest.y){
              posBullet.y++;
              posBullet.x = (int)(-(b*posBullet.y + c)/a);
              printf(" 2A\n");
            }
           
            if(copiePosTankX > tourTest.x && copiePosTankY < tourTest.y){
              posBullet.y++;
              posBullet.x = (int)(-(b*posBullet.y + c)/a);
              printf("3A\n");
            }
            
            if(copiePosTankX > tourTest.x && copiePosTankY > tourTest.y){
              posBullet.y--;
              posBullet.x = (int)(-(b*posBullet.y + c)/a);
              printf(" 4A\n");
            }


if(b<=a){
            if(copiePosTankX < tourTest.x && copiePosTankY > tourTest.y){
              posBullet.x --;
              posBullet.y =  (int)((-(a*posBullet.x + c)/b));
              printf(" 1B\n");
            }
            if(copiePosTankX < tourTest.x && copiePosTankY < tourTest.y){
              posBullet.x --;
              posBullet.y = (int)(-(a*posBullet.x + c)/b);
              printf(" 2B\n");
            }

            if(copiePosTankX > tourTest.x && copiePosTankY < tourTest.y){
              posBullet.x ++;
              posBullet.y = (int)(-(a*posBullet.x + c)/b);
              printf(" 3B\n");
            }

            if(copiePosTankX > tourTest.x && copiePosTankY > tourTest.y){
              posBullet.x ++;
              posBullet.y = (int)(-(a*posBullet.x + c)/b);
              printf(" 4B\n");
            }
          
        }
     */


