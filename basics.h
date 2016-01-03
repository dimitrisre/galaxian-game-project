#pragma once
#include <allegro.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include <map>
#include <string>
#include <list>

//int MovingAnimType = 0;
//int FrameListAnimType = 1;

using namespace std;

typedef char byte;
typedef BITMAP* Bitmap;

struct animInfo{
       int type;
       int i,j;
};
