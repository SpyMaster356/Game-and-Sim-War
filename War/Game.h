#ifndef __GAME_H__
#define __GAME_H__

#include "Player.h"
#include "Deck.h"

class Game {
public:
  void start();

private:
  static const int CARDS_PER_TURN = 3;
  static const int NUM_OF_DECKS = 1;
  static const bool AUTOMATE_WAR = false;

  int roundsWon = 0;
  int roundsLost = 0;
  bool gameRunning;
  Player playerOne;
  Player playerTwo;

  void newRound();
  void dealCards(Deck &fullDeck);
  void playRound();
  void turn(int &turnCount);
  void flipCards(Player &player);
  void turnWon(Player &winner, Player &loser);
};

#endif