#include "BitmapLoader.h"
#include "basics.h"

Bitmap	LoadBitmap (const std::string& path) {
	const char* name = path.c_str();
	return load_bitmap(name, NULL);
}

void DestroyBitmap (Bitmap a) {
	destroy_bitmap(a);
}

Bitmap BitmapLoader::GetBitmap(const std::string path) const {
	BitmapMap::const_iterator i = bitmaps.find(path);
	return i != bitmaps.end() ? i->second : (Bitmap) 0;
}

Bitmap BitmapLoader::Load (const std::string& path) {
	Bitmap b = GetBitmap(path);
	if (!b) {
		bitmaps[path] = (b = LoadBitmap(path));
		assert(b);
	}
	return b;
}

BitmapLoader::BitmapLoader() {}

BitmapLoader::~BitmapLoader() {
	bitmaps.clear();
}
