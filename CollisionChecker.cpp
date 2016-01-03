#include "CollisionChecker.h"
#include "algorithm"


void CollisionChecker::Register (Sprite* s1, Sprite* s2) {
	pairs.push_back(make_pair(s1,s2));
}
void CollisionChecker::Cancel (Sprite* s1, Sprite* s2) {
     if(pairs.size() !=0){
        vector<Pair>::iterator i;
    	for(i=pairs.begin();i!= pairs.end(); i++)
         {
                 Pair pair = *i;
                 if(pair.first == s1 && pair.second==s2){
                               pairs.erase(i);
                               return;
                 }        
         }
         Pair pair= *i;
         
         if(pair.first == s1 && pair.second == s2)
             pairs.erase(i);
     }
}

void CollisionChecker::Check (void) {
 	
 	if(pairs.size() !=0){
        int j = 0;
     	vector<Pair>::iterator i;
    	for(i=pairs.begin();j < pairs.size(); j++,i++)
         {
                 Pair pair = *i;
                 pair.first->CollisionCheck(pair.second);      
         }
        //Pair pair= *i;
        //if(i == pairs.end())
          //      pair.first->CollisionCheck(pair.second);  
     }
}

