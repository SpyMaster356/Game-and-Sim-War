#ifndef __DECK_H__
#define __DECK_H__

#include "stdafx.h"

#include <vector>
#include <string>

#include "Card.h"
#include "Suit.h"

class Deck {
private:
  std::vector<Card> cards;

public:
  Card drawCard();
  Card drawCard(bool removeFromDeck);
  void addCard(Card card);
  void addCard(Card card, bool toBottom);
  void shuffle();
  int size();
  void clear();
  std::string print();

  static void buildFullDeck(Deck &fullDeck);
  static void buildSuit(Deck &fullDeck, Suit suit);
};

#endif