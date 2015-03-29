#include "stdafx.h"

#include <string>

#include "Card.h"
#include "Suit.h"
#include "Value.h"

Card::Card(int value, Suit suit) {
  this->value = value;
  this->suit = suit;
};

Suit Card::getSuit() {
  return suit;
}

int Card::getValue() {
  return value;
};

std::string Card::getSuitName() {
  switch (this->suit) {
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

std::string Card::getValueName() {
  switch (this->value) {
    case (int) Value::ACE:
      return "A";
    case (int) Value::KING:
      return "K";
    case (int) Value::QUEEN:
      return "Q";
    case (int) Value::JACK:
      return "J";
    default:
      return std::to_string(this->value);
  }
};

std::string Card::toString() {
  return "[" + getValueName() + " " + getSuitName() + "]";
};

bool Card::operator == (const Card &other) {
  return this->value == other.value;
};

bool Card::operator >= (const Card &other) {
  return this->value >= other.value;
};

bool Card::operator <= (const Card &other) {
  return this->value <= other.value;
};
bool Card::operator > (const Card &other) {
  return this->value > other.value;
};

bool Card::operator < (const Card &other) {
  return this->value < other.value;
};