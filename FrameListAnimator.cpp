#include "FrameListAnimator.h"
#include <iterator>
#include <list>
void FrameListAnimator::Progress (timestamp_t currTime) {
     const std::list<frame_t> frames=anim->GetFrames();
	 std::list<frame_t>::const_iterator it = frames.begin();
     int  i=0;
    if (currTime - lastTime >= anim->GetDelay()) {
        if(anim->GetCurrFrame() >= (anim->GetNoFrames())){
            anim->SetCurrFrame(0);
        }
        
        for(i=0; i<anim->GetCurrFrame();i++){
                 it++;
        }
        sprite->SetFrame(*it);
		//sprite->move(anim->GetDx(), anim->GetDy());
		anim->SetCurrFrame(anim->GetCurrFrame()+1);
		
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		
		}
		else {
			lastTime += anim->GetDelay();
			Progress(currTime);  // Recursion (make loop)
		}
  }
}

void FrameListAnimator::Start (Sprite* s, FrameListAnimation* a, timestamp_t t) {
		sprite	= s;
		anim 	= a;
		lastTime 	= t;
		state 	= ANIMATOR_RUNNING;
}

FrameListAnimator::FrameListAnimator (void):sprite((Sprite*) 0), anim((FrameListAnimation*) 0){}
FrameListAnimator::~FrameListAnimator(){}
