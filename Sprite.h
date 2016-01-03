#pragma once
#include "basics.h"
#include "Rect.h"
#include "Animation.h"


class Sprite {
    protected:
              byte frameNo;
              Rect frameBox;
              int	x,y;
              bool isVisible;
              AnimationFilm*	currFilm;
	          void* lastArg;
	
	
	public: typedef void (*onCollision)(Sprite* self, Sprite* other, void*);
	private: onCollision CollisionCallback;
	void * parent;
	public:
		
    void SetFrame (byte i);
    byte GetFrame (void) const;
    void SetVisibility (bool v);
    bool IsVisible (void) const;
    bool RectCollisionCheck (Sprite* s);
	int GetX();
	int GetY();
	void SetX(int _x);
	void SetY(int _y);
	Rect GetFrameBox();
	bool collisionCheckRight(int dx,int dy);
	bool collisionCheckLeft(int dx,int dy);
	bool collisionCheckBottom(int dx,int dy);
	bool collisionCheckUp(int dx,int dy);
    Sprite (int _x, int _y, AnimationFilm* film);
    ~Sprite();
    void Sprite::Display (Bitmap dest);
	virtual void move(int dx, int dy);
	bool CollisionCheck(Sprite* s);
	void SetOnCollision(onCollision);
	void SetOnCollisionCallbacLastArg(void * what);
	void SetParent(void *p) {parent = p;}
	void* getParent() { return parent;}
	void setLastArg(void *A) {lastArg = A;}
	void *getLastArg() {return lastArg;}
};

class  ShipSprite:public Sprite{
       public:
              ShipSprite(int _x, int _y, AnimationFilm* film);
              void move(int dx, int dy);
};

class BulletSprite:public Sprite{
      public:
             BulletSprite(int _x, int _y, AnimationFilm* film);
              void move(int dx, int dy);
};    

class AlienShipSprite: public Sprite{
      
      public:
             AlienShipSprite(int _x, int _y, AnimationFilm* film);
             ~AlienShipSprite();
              void move(int dx, int dy);
        
};
