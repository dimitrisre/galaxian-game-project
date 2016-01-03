#include "Animation.h"
#include <fstream>
#include "basics.h"
#include "BitmapLoader.h"



const std::list<PathEntry>& MovingPathAnimation::GetPath (void) const { return path; }
void MovingPathAnimation::SetPath (const std::list<PathEntry>& p){ path.clear(); path = p; curPath=0;}
int MovingPathAnimation::GetCurPath(void){return curPath;}
void MovingPathAnimation::SetCurPath(int _curPath){curPath=_curPath;}
 Animation* MovingPathAnimation::Clone (animid_t newId) const{ return new MovingPathAnimation(path, newId,continuous, curPath); }
 MovingPathAnimation::MovingPathAnimation (const std::list<PathEntry>& _path, animid_t id, bool c,int _curPath) :
	path(_path), curPath(_curPath),MovingAnimation(0, 0, 0, c, id){}

