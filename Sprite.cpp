#include "Sprite.h"
#include "CollisionChecker.h"

#define WIDTH 640
#define HEIGHT 480
extern int direction;
extern bool AtEdge;

void Sprite::SetFrame (byte i) {	
	if (i != frameNo) {
		assert(i < currFilm->GetTotalFrames());
		frameBox = currFilm->GetFrameBox(frameNo = i);
	}
}

byte Sprite::GetFrame (void) const {
	return frameNo; 
}

void Sprite::SetVisibility (bool v) { 
	isVisible = v; 
}

bool Sprite::IsVisible (void) const { 
	return isVisible; 
}

int Sprite::GetX() { return x; }
int Sprite::GetY() { return y; }
void Sprite::SetX(int _x) {x = _x;}
void Sprite::SetY(int _y) {y = _y;}
Rect Sprite::GetFrameBox() { return frameBox; }

bool Sprite::RectCollisionCheck (Sprite* s) {
	Rect boundingBox1(x,y, x + frameBox.getWidth(), y+frameBox.getHeight());
	int sX = s->GetX(), sY = s->GetY();
	Rect boundingBox2(sX, sY, sX+ s->GetFrameBox().getWidth(), sY+s->GetFrameBox().getHeight());

	return (boundingBox1.collisionCheck(boundingBox2));
}

void Sprite::Display (Bitmap dest) {
	if (!this->IsVisible()) return;
	masked_blit(currFilm->GetBitmap(), dest,
				frameBox.getX1(), frameBox.getY1(),  
				x,y,
				frameBox.getWidth(), frameBox.getHeight()
		);

	Rect boundingBox(x,y, x + frameBox.getWidth(), y+frameBox.getHeight());
}

Sprite::Sprite (int _x, int _y, AnimationFilm* film): 
			x(_x), y(_y), currFilm(film), isVisible(true) { 
	//frameNo = currFilm->GetTotalFrames(); 
	frameNo = 0;
	frameBox = film->GetFrameBox(frameNo);
    SetFrame(0); 
	this->SetOnCollision(0);
	lastArg=0;
}

Sprite::~Sprite(){
                  free(lastArg);                  
}
bool Sprite::collisionCheckRight(int dx, int dy) {
	if (x+frameBox.getWidth()+dx < WIDTH )
		return true;
	else return false;
}
bool Sprite::collisionCheckLeft(int dx,int dy) {	
		if (x+dx > 0)
		return true;
	else return false;
}
bool Sprite::collisionCheckBottom(int dx,int dy) {
	if (y+dy > HEIGHT )
		return true;
	else return false;
}

bool Sprite::collisionCheckUp(int dx, int dy) {	
		if (y+dy > 0)
		return true;
	else return false;
}

void Sprite::move(int dx,int dy) {

        x += dx;
        y += dy;	
}

bool Sprite::CollisionCheck(Sprite* S) {
	if (RectCollisionCheck(S)) {
		if (CollisionCallback) {
			CollisionCallback(this, S, lastArg);
		}
		else cout << "Collision Detected, but there is no callback registered.\n";
		return true;
	}
	return false;
}

void Sprite::SetOnCollision(onCollision a) {
	CollisionCallback=a;
}

void Sprite::SetOnCollisionCallbacLastArg(void *what) {
	lastArg = what;
}



ShipSprite::ShipSprite(int _x, int _y, AnimationFilm* film) :Sprite(_x, _y, film)
{
    
}

void ShipSprite::move(int dx, int dy){
      if(x+dx < 5)
		x=5;
	 else if(x+dx > 620)
        x = 620;
     else
        x += dx;
		
     if(y+dy < 5)
		y=5;
	 else if(y+dy > 475)
        y = 475;
     else
        y += dy;	                
}

BulletSprite::BulletSprite(int _x, int _y, AnimationFilm* film) :Sprite(_x, _y, film)
{
    
}

void BulletSprite::move(int dx, int dy){
     if(x+dx < 0)
	    SetVisibility(false);	
	 else if(x+dx > 640)
        SetVisibility(false); 
     else
        x += dx;
		
     
	 if(y+dy > 480)
        SetVisibility(false);
     else if(y+dy <0)
         SetVisibility(false); 
     else
        y += dy;
        	                
}

AlienShipSprite::AlienShipSprite(int _x,int _y,AnimationFilm* film):Sprite(_x, _y, film)
{
}

//AlienShipSprite::~~AlienShipSprite(){

//}

void AlienShipSprite::move(int dx, int dy){
     int i=0;
     if(x+dx <= 20 ){
 	    AtEdge=true;     
      }
     else if(x+dx >= 600)
        AtEdge = true; 
        
     x += (direction)*dx;
		
     
	 if(y+dy > 480)
        SetVisibility(false);
     else if(y+dy <0)
         SetVisibility(false); 
     else
        y += dy;
     
        	                
}
