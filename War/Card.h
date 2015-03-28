#ifndef __CARD_H__
#define __CARD_H__

#include <string>

#include "Suit.h"

class Card {
private:
  int value;
  Suit suit;

public:
  static const int MAX_VALUE = 14;
  static const int MIN_VALUE = 2;

  Card(int value, Suit suit);

  Suit getSuit();
  int  getValue();
  std::string getSuitName();
  std::string getValueName();
  std::string toString();

  bool operator == (Card other);
  bool operator <  (Card other);
  bool operator <= (Card other);
  bool operator >  (Card other);
  bool operator >= (Card other);
};

#endif
