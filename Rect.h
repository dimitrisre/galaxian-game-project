#pragma once
#include "basics.h"


class Rect {
	int x1,y1;
	int x2,y2;

	public:
	       bool collisionCheck(Rect B);
	       
           void move(int dx, int dy);
	       
           Rect(int x1, int y1, int x2, int y2);
	       Rect();
	       
	       int getX1();
	       int getY1();
	       int getX2();
	       int getY2();
	       int getWidth();
	       int getHeight();
	       
           void display(Bitmap dest);
};
