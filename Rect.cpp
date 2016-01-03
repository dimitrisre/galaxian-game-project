#include "Rect.h"

bool Rect::collisionCheck(Rect B) {
	int x3 = B.x1;
	int y3 = B.y1;
	int x4 = B.x2;
	int y4 = B.y2;
	
	if (x4 < x1 || x2 < x3 ||
		y4 < y1 || y2 < y3) 
			return false;
	return true;
}

void Rect::move(int dx, int dy) {
		x1+=dx;
		x2+=dx;
		y1+=dy;
		y2+=dy;
}

void Rect::display(Bitmap dest) {
	line(dest, x1,y1,x2,y1, makecol(255,0,0));
	line(dest, x2,y1,x2,y2, makecol(255,0,0));
	line(dest, x2,y2,x1,y2, makecol(255,0,0));
	line(dest, x1,y2,x1,y1, makecol(255,0,0));
}
Rect::Rect(int _x1, int _y1, int _x2, int _y2) {
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
}

Rect::Rect() {
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
}

int Rect::getWidth() {
	return x2-x1;
}
int Rect::getHeight() {
	return y2-y1;
}
int Rect::getX1() {
		return x1;
}
int Rect::getY1() {
		return y1;
}
int Rect::getX2() {
		return x2;
}
int Rect::getY2() {
		return y2;
}
