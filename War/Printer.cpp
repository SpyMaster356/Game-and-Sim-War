#include "stdafx.h"

#include <iostream>
#include <string>

#include "Printer.h"
#include "Deck.h"

void Printer::printScore(int &won, int &lost) {
  Printer::printLine();
  std::cout << "Score:" << std::endl;
  std::cout << "Won:" << won << std::endl;
  std::cout << "Lost:" << lost << std::endl;
}

void Printer::printReserves(std::string playerName, Deck &reserves) {
  std::cout << playerName << " reserves: " << reserves.size() << std::endl;
  std::cout << reserves.print();
  Printer::printLine();
}

void Printer::printTroops(std::string playerName, Deck &troops) {
  std::cout << playerName << " troops: " << troops.print() << std::endl;
}

bool Printer::playAgainPrompt() {
  bool validInput = false;
  bool returnValue;
  std::string input;

  while (!validInput) {
    Printer::printLine();
    Printer::printLine("Play again? (y/n)");

    std::cin >> input;

    if (input == "y") {
      returnValue = true;
      validInput = true;
    }
    else if (input == "n") {
      returnValue = false;
      validInput = true;
    }
    else {
      Printer::printLine("Please enter 'y' or 'n'");
    }
  }

  return returnValue;
}

void Printer::printLine() {
  Printer::printLine("");
}

void Printer::printLine(std::string line) {
  std::cout << line << std::endl;
}