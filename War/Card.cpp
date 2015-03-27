#include "stdafx.h"

#include <string>

#include "Card.h"
#include "Suit.h"
#include "Value.h"

Card::Card(int value, Suit suit) {
  _value = value;
  _suit = suit;
};

Suit Card::suit() {
  return _suit;
};

int Card::value() {
  return _value;
};

std::string Card::suitName() {
  switch (_suit) {
    case Suit::HEART:
      return "H";
    case Suit::DIAMOND:
      return "D";
    case Suit::SPADE:
      return "S";
    case Suit::CLUB:
      return "C";
    default:
      return "U";
  }
};

std::string Card::valueName() {
  switch (_value) {
    case (int) Value::ACE:
      return "A";
    case (int) Value::KING:
      return "K";
    case (int) Value::QUEEN:
      return "Q";
    case (int) Value::JACK:
      return "J";
    default:
      return std::to_string(_value);
  }
};

std::string Card::toString() {
  return "[" + valueName() + " " + suitName() + "]";
};
