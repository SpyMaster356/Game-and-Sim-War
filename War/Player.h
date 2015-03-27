#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Deck.h"

class Player {
public:
  Deck reserves;
  Deck troops;

  void flipCards();
};

#endif