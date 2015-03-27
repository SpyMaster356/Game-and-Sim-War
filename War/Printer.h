#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <string>

#include "Deck.h"

class Printer {
public:
  static void printScore(int &won, int &lost);
  static void printReserves(std::string playerName, Deck &reserves);
  static void printTroops(std::string playerName, Deck &troops);
  static bool playAgainPrompt();
  static void printLine();
  static void printLine(std::string string);
};

#endif