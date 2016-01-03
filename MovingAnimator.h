#pragma once
#include "Animation.h"
#include "Sprite.h"

class MovingAnimator : public Animator {
	Sprite*		sprite;
	MovingAnimation*	anim;

	public:
		void Progress (timestamp_t currTime);
		void Start (Sprite* s, MovingAnimation* a, timestamp_t t);
		MovingAnimator (void);
		~MovingAnimator();
};

class KamikazeMovingAnimator : public Animator{
    Sprite*		sprite;
	MovingAnimation*	anim;
	
	public:
           void Progress (timestamp_t currTime);
		void Start (Sprite* s, MovingAnimation* a, timestamp_t t);
		KamikazeMovingAnimator (void);
		~KamikazeMovingAnimator();
};
