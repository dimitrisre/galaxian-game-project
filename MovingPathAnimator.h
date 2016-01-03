#pragma once
#include "Animation.h"
#include "Sprite.h"

class MovingPathAnimator : public Animator {
	Sprite*		sprite;
	MovingPathAnimation*	anim;

	public:
		void Progress (timestamp_t currTime);
		void Start (Sprite* s, MovingPathAnimation* a, timestamp_t t);
		MovingPathAnimator (void);
		~MovingPathAnimator();
};
