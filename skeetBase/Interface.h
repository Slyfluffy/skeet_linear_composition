//
//  Interface.h
//  Skeet
//
//  Created by Journey Curtis on 2/24/22.
//

#ifndef Interface_h
#define Interface_h

#include "logic.h"

class Interface {
private:
   Logic logic;
   
public:
   Interface();
   
   void input(const UserInput &ui);
   void processing();
   void output();
};



#endif /* Interface_h */
