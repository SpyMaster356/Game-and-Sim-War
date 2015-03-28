#include "stdafx.h"

#include "Deck.h"
#include "Card.h"
#include "Suit.h"
#include <time.h>

Card Deck::drawCard() {
  return drawCard(true);
}

Card Deck::drawCard(bool removeFromDeck) {
  Card topCard = cards.back();

  if (removeFromDeck) {
    cards.pop_back();
  }

  return topCard;
}

void Deck::addCard(Card card) {
  addCard(card, true);
}

void Deck::addCard(Card card, bool toBottom) {
  if (toBottom) {
    cards.insert(cards.begin(), card);
  }
  else {
    cards.insert(cards.end(), card);
  }
}

void Deck::shuffle() {
  int maxSize = cards.size() - 1;

  srand(time(NULL));

  for (int index1 = 0; index1 <= maxSize; index1++) {
    int index2 = rand() % maxSize;

    Card card1 = cards[index1];
    Card card2 = cards[index2];

    cards[index1] = card2;
    cards[index2] = card1;
  }
}

int Deck::size() {
  return cards.size();
}

void Deck::clear() {
  cards.clear();
}

std::string Deck::print() {
  std::string line = "";
  if (cards.size() > 0) {
    line += "[{O}]";
  }

  for (int count = cards.size() - 1; count > 0; count--){
    line += "]";
  }

  return line;
}

void Deck::buildFullDeck(Deck &fullDeck) {
  buildSuit(fullDeck, Suit::HEART);
  buildSuit(fullDeck, Suit::SPADE);
  buildSuit(fullDeck, Suit::DIAMOND);
  buildSuit(fullDeck, Suit::CLUB);
}

void Deck::buildSuit(Deck &fullDeck, Suit suit) {
  for (int value = Card::MIN_VALUE; value <= Card::MAX_VALUE; value++) {
    Card card = Card(value, suit);
    fullDeck.addCard(card);
  }
}