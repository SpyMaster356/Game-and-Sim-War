#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Deck.h"

class Player {
public:
  Deck pile;
  Deck deck;

  void flipCards();
};

#endif