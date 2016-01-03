#pragma once
#include "Animation.h"
#include <list>
class AnimatorHolder {
	std::list<Animator*> running, suspended;
	class ProgressFunctor : public std::unary_function<Animator*, void> {
	    timestamp_t t;
	public: 
	    void operator()(Animator* a) const { a->Progress(t); }
	    ProgressFunctor (timestamp_t _t) : t(_t){}
	};

public:
	void Register (Animator* a); 
	void Cancel (Animator* a); 
	void MarkAsRunning (Animator* a);
	void MarkAsSuspended (Animator* a);
	void Progress (timestamp_t currTime); 
};
