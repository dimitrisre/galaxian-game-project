#include "MovingPathAnimator.h"
#include <iterator>
#include <list>

void MovingPathAnimator::Progress (timestamp_t currTime) {
     const std::list<PathEntry> path=anim->GetPath();
	 std::list<PathEntry>::const_iterator it = path.begin();
     int  i=0;
     for(i=0; i<anim->GetCurPath(); i++){
                 it++;
     }
     if (currTime - lastTime >= (*it).delay) {
        //if(anim->GetCurrFrame() >= (anim->GetNoFrames())){
          //  anim->SetCurrFrame(0);
        //}
        
        
        sprite->SetFrame((*it).frame);
		sprite->move((*it).dx, (*it).dy);
		
		
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		
		}
		else {
			lastTime += (*it).delay;
			Progress(currTime);  // Recursion (make loop)
		}
		anim->SetCurPath(anim->GetCurPath()+1);
  }
}

void MovingPathAnimator::Start (Sprite* s, MovingPathAnimation* a, timestamp_t t) {
		sprite	= s;
		anim 	= a;
		lastTime 	= t;
		state 	= ANIMATOR_RUNNING;
}

MovingPathAnimator::MovingPathAnimator (void):sprite((Sprite*) 0), anim((MovingPathAnimation*) 0){}
MovingPathAnimator::~MovingPathAnimator(){}
