#pragma once
#include "basics.h"
#include <list>
#include "Sprite.h"
#include <vector>
class CollisionChecker {
    typedef std::pair<Sprite*, Sprite*> Pair;
	std::vector<Pair> pairs;
	
    public:
    void Register (Sprite* s1, Sprite* s2);
    void Cancel (Sprite* s1, Sprite* s2);
    void Check (void);
};
