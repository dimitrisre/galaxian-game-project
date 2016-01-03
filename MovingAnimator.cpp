#include "MovingAnimator.h"

void MovingAnimator::Progress (timestamp_t currTime) {
	if (currTime - lastTime >= anim->GetDelay()) {
		sprite->move(anim->GetDx(), anim->GetDy());
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

void MovingAnimator::Start (Sprite* s, MovingAnimation* a, timestamp_t t) {
		sprite	= s;
		anim 	= a;
		lastTime 	= t;
		state 	= ANIMATOR_RUNNING;
}

MovingAnimator::MovingAnimator (void):sprite((Sprite*) 0), anim((MovingAnimation*) 0){}
MovingAnimator::~MovingAnimator(){}

extern ShipSprite* player_ship;
extern MovingAnimation* shipMove;

void KamikazeMovingAnimator::Progress (timestamp_t currTime) {
	int dx = shipMove->GetDx()-5;
	int dy = 5;
	
    if (currTime - lastTime >= anim->GetDelay()) {
        
		sprite->move(dx,dy);
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

void KamikazeMovingAnimator::Start (Sprite* s, MovingAnimation* a, timestamp_t t) {
		sprite	= s;
		anim 	= a;
		lastTime 	= t;
		state 	= ANIMATOR_RUNNING;
}



KamikazeMovingAnimator::KamikazeMovingAnimator(void):sprite((Sprite*) 0), anim((MovingAnimation*) 0){}
KamikazeMovingAnimator::~KamikazeMovingAnimator(){}
