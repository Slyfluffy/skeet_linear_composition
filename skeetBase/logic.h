//
//  logic.h
//  Skeet
//
//  Created by Journey Curtis on 2/24/22.
//

#ifndef logic_h
#define logic_h

#include "storage.h"

class Logic {
private:
   Storage storage;
   
public:
   Logic();
   
   void advance();
   void spawn();
   void input();
   
   class iterator;
   std::vector<StorageElement*> :: iterator begin() { return storage.begin(); }
   std::vector<StorageElement*> :: iterator end()   { return storage.end();   }
   
   int getFramesLeft();
   int getLevelNumber();
   
   double getGunAngle();
   double getPercentLeft();
   
   bool isPlaying();
   bool isGameOver();
};

class Logic :: iterator {
   
};
#endif /* logic_h */
