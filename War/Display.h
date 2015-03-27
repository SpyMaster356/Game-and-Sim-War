#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <string>

#include "Deck.h"
#include "Player.h"

class Display {
public:
  static void printScore(int &won, int &lost);
  static void printReserves(std::string playerName, Deck &reserves);
  static void printTroops(std::string playerName, Deck &troops);
  static bool playAgainPrompt();
  static void printLine();
  static void printLine(std::string string);
  static void playerWonWar();
  static void playerLostWar();
  static void clear();
  static void turnStart(int &turnNumber, Player &playerOne, Player &playerTwo);
  static void anyKeyToContinue();

private:
  static void warEnd(std::string message);
};

#endif
