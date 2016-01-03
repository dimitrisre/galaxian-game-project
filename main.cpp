#include <allegro.h>
#include <cstdlib>
#include "BitmapLoader.h"
#include "Animation.h"
#include "MovingAnimator.h"
#include "CollisionChecker.h"
#include "AnimatorHolder.h"
#include "FrameListAnimator.h"
#include "Sprite.h"
#include "Rect.h"
#include <ctime>
#include "basics.h"
#include "MovingPathAnimator.h"


static unsigned long currTime = 0;
void setgametime() { currTime = clock(); }
unsigned long getgametime() { return currTime; }
unsigned long tmpTime;
int direction;
bool AtEdge;

BitmapLoader* bitmapLoader;
AnimationFilmHolder* animFholder;
AnimatorHolder* animHolder;

CollisionChecker* colliCheck;

ShipSprite* player_ship;
Sprite* bullet, *exploSpr;
Sprite *stars[30];
AlienShipSprite* red_ship[6], *pink_ship[8], *yellow_ship[2];
AlienShipSprite* green_ship[3][10];

BITMAP *backbuffer = NULL; 
SAMPLE* bleed;
SAMPLE* laser;
SAMPLE* explosion;	
std::list<frame_t> frames,af, sta;
const char *films = "films.txt";
animid_t id = 3;

MovingAnimation* shipMove;

MovingAnimation* bulletMove;

MovingPathAnimation* kamikazeMV;
MovingPathAnimator* kamikazeMVA;
MovingAnimation* MainKamikazeMV;
KamikazeMovingAnimator* MainKamikazeMVA;

FrameListAnimation* greenShipMoves[3][10];
FrameListAnimator* greenShipMovements[3][10];
MovingAnimation* greenShipMV[3][10];
MovingAnimator* greenShipMVA[3][10];

FrameListAnimation* redShipMoves[6];
FrameListAnimator* redShipMovements[6];
MovingAnimation* redShipMV[6];
MovingAnimator* redShipMVA[6];


FrameListAnimation* pinkShipMoves[8];
FrameListAnimator* pinkShipMovements[8];
MovingAnimation* pinkShipMV[8];
MovingAnimator* pinkShipMVA[8];

MovingAnimation* yellowShipMoves[2];
MovingAnimator* yellowShipMovement[2];

FrameListAnimator* starsMovement[30];
FrameListAnimation* starsMoves[30];
MovingAnimation* starsMV[30];
MovingAnimator* starsMVA[30];

FrameListAnimation* explotionMove;
FrameListAnimator* explotionMovement;


void DisplayAll(){
     int i,j,x=220,y=100;
     
     if(yellow_ship[0]!=0)
                       yellow_ship[0]->Display(backbuffer);
     if(yellow_ship[1]!=0)
                       yellow_ship[1]->Display(backbuffer);
     for(i=0; i<6; i++){
              if(red_ship[i]!=0)
                             red_ship[i]->Display(backbuffer);
     }
     
     for(i=0; i<8; i++){
              if(pink_ship[i]!=0)
                                pink_ship[i]->Display(backbuffer);
     }
     for(i=0; i<3; i++){
              for(j=0; j<10; j++){
                       //if(green_ship[2][9]==0)play_sample(explosion, 255, 128, 1000, FALSE);
                       if(green_ship[i][j]!=0)
                                           green_ship[i][j]->Display(backbuffer);       
              }
     }
     if(exploSpr != NULL)
         exploSpr->Display(backbuffer);
     player_ship->Display(backbuffer);
     bullet->Display(backbuffer);
     for(i=0;i<30;i++)
                      if(stars[i] != 0)
                                   stars[i]->Display(backbuffer);
}

void onFinishExplosion(Animator *animator,void *c){
     //explotionMove->~Animation();
     //struct animInfo *e = (struct animInfo *)exploSpr->getLastArg();
     //animHolder->MarkAsSuspended((FrameListAnimator *)animator);
     //animHolder->Cancel((FrameListAnimator *)animator);
     //explotionMovement->Animator();
     exploSpr->SetVisibility(false);
     //explotionMovement->Stop();
     //animHolder->MarkAsSuspended((FrameListAnimator*)e->anim);
     //animHolder->Cancel((FrameListAnimator*)e->anim);
}

void explodeAlien(Sprite *Alien, Sprite *bullet, void *z){
     int x = Alien->GetX();
     int y = Alien->GetY();
     //struct animInfo *expl = (struct animInfo *)malloc(sizeof(struct animInfo));
     
     af.push_back(1);
     af.push_back(0);
     af.push_back(2);
     af.push_back(3);
     
     
     if(exploSpr == NULL)
                 exploSpr = new Sprite(x, y, animFholder->GetFilm("explotion_film.bmp"));
     
     if(explotionMove == NULL){           
                      explotionMove = new FrameListAnimation(af, x, y, 60, false, id, 4);
                      explotionMove->SetDx(0);
                      explotionMove->SetDy(0);
     
                      id++;
     }
     
     exploSpr->SetX(x);
     exploSpr->SetY(y);
     exploSpr->SetFrame(0);                     
     exploSpr->SetVisibility(true);
     
     if(explotionMovement == NULL){
                          explotionMovement = new FrameListAnimator();
                          animHolder->Register(explotionMovement);
                          animHolder->MarkAsRunning(explotionMovement);
     
     }
     //expl->anim = explotionMovement;
     //expl->type = 1;
     //exploSpr->setLastArg(expl);
     explotionMovement->Start(exploSpr, explotionMove, getgametime());
     explotionMovement->SetOnFinish(&onFinishExplosion,NULL);
    
     
     
     bullet->SetX(player_ship->GetX()+(player_ship->GetFrameBox().getWidth())/2);
     bullet->SetY(player_ship->GetY());
     bullet->SetVisibility(false);
     bulletMove->SetDx(0);
     bulletMove->SetDy(0);
     
     struct animInfo *a = (struct animInfo *)Alien->getLastArg();
     if(a->type == 0){
                play_sample(explosion, 255, 128, 1000, FALSE);   
                //((MovingAnimator*)a->anim)->Stop();
                animHolder->MarkAsSuspended(yellowShipMovement[a->i]);
                animHolder->Cancel(yellowShipMovement[a->i]);
                
     }
     else if(a->type == 1){
                play_sample(explosion, 255, 128, 1000, FALSE);   
                //((MovingAnimator*)a->anim)->Stop();
                animHolder->MarkAsSuspended(redShipMovements[a->i]);
                animHolder->Cancel(redShipMovements[a->i]);
                animHolder->MarkAsSuspended(redShipMVA[a->i]);
                animHolder->Cancel(redShipMVA[a->i]);
                
     }
     else if(a->type == 2){
                play_sample(explosion, 255, 128, 1000, FALSE);   
                //((MovingAnimator*)a->anim)->Stop();
                animHolder->MarkAsSuspended(pinkShipMovements[a->i]);
                animHolder->Cancel(pinkShipMovements[a->i]);
                animHolder->MarkAsSuspended(pinkShipMVA[a->i]);
                animHolder->Cancel(pinkShipMVA[a->i]);
                
     }
     else if(a->type == 3){
                play_sample(explosion, 255, 128, 1000, FALSE);   
                //((MovingAnimator*)a->anim)->Stop();
                animHolder->MarkAsSuspended(greenShipMovements[a->i][a->j]);
                animHolder->Cancel(greenShipMovements[a->i][a->j]);
                animHolder->MarkAsSuspended(greenShipMVA[a->i][a->j]);
                animHolder->Cancel(greenShipMVA[a->i][a->j]);
                
     }/*
     else{
          play_sample(explosion, 255, 128, 1000, FALSE);   
          //((FrameListAnimator*)a->anim)->Stop();
          animHolder->MarkAsSuspended((FrameListAnimator*)a->anim);
          animHolder->Cancel((FrameListAnimator*)a->anim);
     }*/
     colliCheck->Cancel(Alien,bullet);
     Alien->SetVisibility(false);
     
     delete Alien;
     //Alien->~AlienShipSprite();
     
  
}

void initShips(void){
     int i,j,x=265,y=85;
     frame_t fr = 2;
     unsigned long tim = getgametime();
     
     for(i=0; i<2; i++){
              struct animInfo *ai = (struct animInfo *)malloc(sizeof(struct animInfo));
              yellow_ship[i] = new AlienShipSprite(x,y,animFholder->GetFilm("yellow_ship_film.bmp"));
              yellow_ship[i]->SetFrame(13);
              yellowShipMoves[i] = new MovingAnimation(x,y,150,true,id);
              id++;
              yellowShipMovement[i] = new MovingAnimator();
              ai->type = 0;
              ai->i = i;
              ai->j=-1;
              yellowShipMoves[i]->SetDx(-5);
              yellowShipMoves[i]->SetDy(0);
              yellowShipMovement[i]->Start(yellow_ship[i],yellowShipMoves[i],tim);
              animHolder->Register(yellowShipMovement[i]);
              animHolder->MarkAsRunning(yellowShipMovement[i]);
              x+=45;
              yellow_ship[i]->setLastArg(ai);
              yellow_ship[i]->SetOnCollision(&explodeAlien);
              colliCheck->Register(yellow_ship[i], bullet);
     }
     x=250;
     y+=15;
     for(i=0; i<6; i++){
              struct animInfo *ai = (struct animInfo *)malloc(sizeof(struct animInfo));
              red_ship[i] = new AlienShipSprite(x,y,animFholder->GetFilm("red_ship_film.bmp"));
              redShipMoves[i] = new FrameListAnimation(frames,x,y,150,true,id,3);
              id++;
              redShipMV[i] = new MovingAnimation(x,y,150,true,id);
              id++;
              redShipMovements[i] = new FrameListAnimator();
              redShipMVA[i] = new MovingAnimator();
              ai->type = 1;
              ai->i = i;
              ai->j=-1;
              redShipMV[i]->SetDx(-5);
              redShipMV[i]->SetDy(0);
              redShipMoves[i]->SetCurrFrame(fr);
              redShipMovements[i]->Start(red_ship[i],redShipMoves[i],tim);
              animHolder->Register(redShipMovements[i]);
              animHolder->MarkAsRunning(redShipMovements[i]);
              redShipMVA[i]->Start(red_ship[i],redShipMV[i],tim);
              animHolder->Register(redShipMVA[i]);
              animHolder->MarkAsRunning(redShipMVA[i]);
              
              x+=15;
              fr++;
              if(fr>=2)
                 fr = 0;
              red_ship[i]->setLastArg(ai);
              red_ship[i]->SetOnCollision(&explodeAlien);
              colliCheck->Register(red_ship[i], bullet);
     }
     x=235;
     y+=15;
     fr=1;
     for(i=0; i<8; i++){
              struct animInfo *ai = (struct animInfo *)malloc(sizeof(struct animInfo));
              pink_ship[i] = new AlienShipSprite(x,y,animFholder->GetFilm("pink_ship_film.bmp"));
              pinkShipMoves[i] = new FrameListAnimation(frames,x,y,150,true,id,3);
              id++;
              pinkShipMV[i] = new MovingAnimation(x,y,150,true,id);
              id++;
              pinkShipMovements[i] = new FrameListAnimator();
              pinkShipMVA[i] = new MovingAnimator();
              ai->type = 2;
              ai->i = i;
              ai->j=-1;
              pinkShipMV[i]->SetDx(-5);
              pinkShipMV[i]->SetDy(0);
              pinkShipMoves[i]->SetCurrFrame(fr);
              pinkShipMovements[i]->Start(pink_ship[i],pinkShipMoves[i],tim);
              animHolder->Register(pinkShipMovements[i]);
              animHolder->MarkAsRunning(pinkShipMovements[i]);
              pinkShipMVA[i]->Start(pink_ship[i],pinkShipMV[i],tim);
              animHolder->Register(pinkShipMVA[i]);
              animHolder->MarkAsRunning(pinkShipMVA[i]);
              x+=15;
              fr++;
              if(fr>=2)
                 fr = 0;
              pink_ship[i]->setLastArg(ai);
              pink_ship[i]->SetOnCollision(&explodeAlien);   
              colliCheck->Register(pink_ship[i], bullet);
     }
     x=220;
     y+=15;
     fr=0;
     for(i=0; i<3; i++){
              for(j=0; j<10; j++){
                       struct animInfo *ai = (struct animInfo *)malloc(sizeof(struct animInfo));
                       green_ship[i][j] = new AlienShipSprite(x,y,animFholder->GetFilm("green_ship_film.bmp"));
                       greenShipMoves[i][j] = new FrameListAnimation(frames,x,y,150,true,id,3);
                       id++;
                       greenShipMV[i][j] = new MovingAnimation(x,y,150,true,id);
                       id++;
                       greenShipMovements[i][j] = new FrameListAnimator();
                       greenShipMVA[i][j] = new MovingAnimator();
                       ai->type = 3;
                       ai->i = i;
                       ai->j= j;
                       greenShipMV[i][j]->SetDx(-5);
                       greenShipMV[i][j]->SetDy(0);
                       greenShipMoves[i][j]->SetCurrFrame(fr);
                       greenShipMovements[i][j]->Start(green_ship[i][j],greenShipMoves[i][j],tim);
                       animHolder->Register(greenShipMovements[i][j]);
                       animHolder->MarkAsRunning(greenShipMovements[i][j]);
                       greenShipMVA[i][j]->Start(green_ship[i][j],greenShipMV[i][j],tim);
                       animHolder->Register(greenShipMVA[i][j]);
                       animHolder->MarkAsRunning(greenShipMVA[i][j]);
                       x+=15;
                       fr++;
                       if(fr>=2)
                         fr = 0;
                       green_ship[i][j]->setLastArg(ai);
                       green_ship[i][j]->SetOnCollision(&explodeAlien);
                       colliCheck->Register(green_ship[i][j], bullet);
              }
              x=220;
              y+=15;
     }
}

std::list<PathEntry> path;

void KamikazeMainAttack(Animator *animator,void *c){
        
     animHolder->MarkAsSuspended(kamikazeMVA);
     animHolder->Cancel(kamikazeMVA);
     
     MainKamikazeMV = new MovingAnimation(5,5,100,false,id++);
     MainKamikazeMVA = new KamikazeMovingAnimator();
     MainKamikazeMVA->Start(green_ship[0][0],MainKamikazeMV,getgametime());
     animHolder->Register(MainKamikazeMVA);
     animHolder->MarkAsRunning(MainKamikazeMVA);
     
     
     
}
void KamikazeRotate(){
     animHolder->MarkAsSuspended(greenShipMovements[0][0]);
     int i=11, x = -5, y = -3;
     PathEntry* pa;
     while(i<=17){
              pa = new PathEntry();
              pa->delay = 100;
              pa->dx = x++;
              pa->dy = y++;
              pa->frame = i;
              i++;
              path.push_back(*pa);
     }
 
     kamikazeMV = new MovingPathAnimation(path,id++,false,0);
     
     kamikazeMVA = new MovingPathAnimator();
     kamikazeMVA->Start(green_ship[0][0], kamikazeMV, getgametime());
     //kamikazeMVA->SetOnFinish(&KamikazeMainAttack,NULL);
     
     animHolder->Register(kamikazeMVA);
     animHolder->MarkAsRunning(kamikazeMVA);
     
     
}


void initStars(){
     int i, x, y;
     unsigned long tim = getgametime();
     
     sta.push_back(0);
     sta.push_back(1);
     sta.push_back(2);
     
     for(i=0; i<30; i++){
              x = rand()%640; 
              y = rand()%480;
              stars[i] = new Sprite(x,y,animFholder->GetFilm("stars_film.bmp"));
              starsMoves[i] = new FrameListAnimation(sta,x,y,200,true,id,3);
              id++;
              starsMV[i] = new MovingAnimation(x,y,200,true,id);
              id++;
              starsMovement[i] = new FrameListAnimator();
              starsMVA[i] = new MovingAnimator();
              starsMV[i]->SetDx(0);
              starsMV[i]->SetDy(7);
              starsMoves[i]->SetCurrFrame(rand()%3);
              starsMovement[i]->Start(stars[i], starsMoves[i], tim);
              animHolder->Register(starsMovement[i]);
              animHolder->MarkAsRunning(starsMovement[i]);
              starsMVA[i]->Start(stars[i],starsMV[i],tim);
              animHolder->Register(starsMVA[i]);
              animHolder->MarkAsRunning(starsMVA[i]);
     }
}

void checkStarMove(){
     int i, x;
     for(i=0; i<30; i++){
              if(stars[i]->collisionCheckBottom(starsMoves[i]->GetDx(), starsMoves[i]->GetDy())){
                                                                        x = rand()%640; 
                                                                        stars[i]->SetX(x);
                                                                        stars[i]->SetY(0);
              }                                      
     }
}

int main(){
    
    allegro_init();
    install_keyboard();
    
    
   
     /* install a digital sound driver */
     if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0) {
        allegro_message("Error initialising sound system\n%s\n", allegro_error);
        return 1;
     }
     
     bleed = load_sample("bleeder.wav");
     if (!bleed) {
        allegro_message("Error reading WAV file 'bleed.wav'\n");
        return 1;
     }
     laser = load_sample("laser.wav");
     if (!laser) {
        allegro_message("Error reading WAV file 'laser.wav'\n");
        return 1;
     }
     explosion = load_sample("explosion.wav");
     if (!explosion) {
        allegro_message("Error reading WAV file 'explosion.wav'\n");
        return 1;
     }
    
    /* start up the sample */
    play_sample(bleed, 255, 128, 1000, TRUE);
    
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0);
    backbuffer = create_bitmap(640,480); 

    bitmapLoader = new BitmapLoader();
    
    
    bitmapLoader->Load("team2.bmp");
	blit(bitmapLoader->GetBitmap("team2.bmp"),backbuffer,0,0,40,10,640,480);
	blit(backbuffer, screen, 0,0,0,0,640,480); 
	while(!key[KEY_ENTER] && !key[KEY_ESC]){
         if(key[KEY_ESC]){
            delete bitmapLoader;
            destroy_bitmap(backbuffer);
            destroy_sample(bleed);
            destroy_sample(laser);
            destroy_sample(explosion);
            exit(1);
         }
    }
    install_timer();
    setgametime();
    direction = 1;
    AtEdge = false;
    tmpTime= 0;
    
    animFholder = new AnimationFilmHolder(films,bitmapLoader);
    animHolder = new AnimatorHolder();
    player_ship = new ShipSprite(320,440,animFholder->GetFilm("player_ship_film.bmp"));
    
  
    bullet = new BulletSprite(0,0,animFholder->GetFilm("fire_film.bmp"));
    bullet->SetVisibility(false);
    
    
    frames.push_back(8);
    frames.push_back(9);
    frames.push_back(10);
    
    shipMove = new MovingAnimation(0,0,30,true,1);
    MovingAnimator* shipMovement = new MovingAnimator();
    
    bulletMove = new MovingAnimation(0,0,30,true,2);
    MovingAnimator* bulletMovement = new MovingAnimator();
    
    
    
    shipMovement->Start(player_ship,shipMove,getgametime());
    animHolder->Register(shipMovement);
    animHolder->MarkAsRunning(shipMovement);
    
    
    bulletMovement->Start(bullet,bulletMove,getgametime());
    animHolder->Register(bulletMovement);
    animHolder->MarkAsRunning(bulletMovement);
    
    colliCheck = new CollisionChecker();
    
    initShips();
    
    initStars();
    bool m = true;
   while( !key[KEY_ESC]){
        acquire_screen();     
        if(key[KEY_LEFT]){
             shipMove->SetDx(-7);
        }
        else if(key[KEY_RIGHT]){
             shipMove->SetDx(7);
        }
        else if(!key[KEY_LEFT] && !key[KEY_RIGHT]){
             shipMove->SetDx(0);    
        }
        
        if(key[KEY_SPACE]){
             
             if(!bullet->IsVisible()){
                play_sample(laser, 255, 128, 1000, FALSE);
                bullet->SetX(player_ship->GetX()+(player_ship->GetFrameBox().getWidth())/2);
                bullet->SetY(player_ship->GetY());
                bullet->SetVisibility(true);
                bulletMove->SetDy(-14);
                bulletMove->SetDx(0);  
             }
        }
        
        setgametime();
        colliCheck->Check();
        checkStarMove();
        if (m)
           KamikazeRotate();
        m = false;
        animHolder->Progress(getgametime());
        DisplayAll();       
        blit(backbuffer, screen, 0,0,0,0,640,480); 
        
        release_screen();
        
        if(AtEdge && (getgametime()-tmpTime)>2000){
            tmpTime = getgametime();
            direction = -direction;
            AtEdge=false;  
        }
        else{
             AtEdge = false;
        }
        
        if(bullet->IsVisible()){
            player_ship->SetFrame(3);
        }
        else{
             player_ship->SetFrame(0);
        }
		clear_bitmap(backbuffer);
    }   
    
    destroy_bitmap(backbuffer);
    destroy_sample(bleed);
    destroy_sample(laser);
    destroy_sample(explosion);
    return 0;
}

END_OF_MAIN();
