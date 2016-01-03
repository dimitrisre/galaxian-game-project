#pragma once
#include "basics.h"

Bitmap	LoadBitmap (const std::string& path);
void	DestroyBitmap (Bitmap);

class BitmapLoader {
    typedef std::map<std::string, Bitmap> BitmapMap;
    BitmapMap bitmaps;
    

public:
	Bitmap GetBitmap (const std::string path) const;
    Bitmap Load (const std::string& path);
    BitmapLoader (void);
    ~BitmapLoader();
};
