#include "AnimatorHolder.h"
#include <algorithm>

void AnimatorHolder::Register (Animator* a) { 
	suspended.push_back(a); 
}
void AnimatorHolder::Cancel (Animator* a) { 
	suspended.remove(a); 
}
void AnimatorHolder::MarkAsRunning (Animator* a){ 
	suspended.remove(a); 
	running.push_back(a); 
}
void AnimatorHolder::MarkAsSuspended (Animator* a){ 
	running.remove(a); 
	suspended.push_back(a); 
}
void AnimatorHolder::Progress (timestamp_t currTime) {
    std::for_each(
		running.begin(), running.end(), ProgressFunctor(currTime)
    ); 
}
