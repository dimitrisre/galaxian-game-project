#pragma once
#include "Animation.h"
#include "Sprite.h"

class FrameListAnimator : public Animator {
	Sprite*		sprite;
	FrameListAnimation*	anim;

	public:
		void Progress (timestamp_t currTime);
		void Start (Sprite* s, FrameListAnimation* a, timestamp_t t);
		FrameListAnimator (void);
		~FrameListAnimator();
};
