#ifndef __CARD_H__
#define __CARD_H__

#include "stdafx.h"

#include <string>

#include "Suit.h"

class Card {
private:
  int _value;
  Suit _suit;

public:
  Card(int value, Suit suit);

  Suit suit();
  int value();
  std::string suitName();
  std::string valueName();
  std::string toString();
};

#endif
