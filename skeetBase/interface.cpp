//
//  interface.cpp
//  Lab03
//
//  Created by Journey Curtis on 2/24/22.
//

#include "Interface.h"

void Interface::input(const UserInput &ui) {
   lgoic.input(isUp() + ui.isRight(), ui.isDown() + ui.isLeft(), ui.isSpace(), ui.isM(), ui.isB());
}

void Interface::processing() {
   if (logic.isPlaying())
      logic.spawn();
   logic.advance();
}

void Interface::output() {
   if (!logic.isPlaying())
   {
      bool isGameOver = logic.isGameOver();
      double percentLEft = logic.getPercentLeft();
}
