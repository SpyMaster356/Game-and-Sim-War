#include "stdafx.h"

#include <iostream>
#include <string>

#include "Printer.h"
#include "Deck.h"

void Printer::printScore(int &won, int &lost) {
  std::cout << std::endl;
  std::cout << "Score:" << std::endl;
  std::cout << "Won:" << won << std::endl;
  std::cout << "Lost:" << lost << std::endl;
}

void Printer::printReserves(std::string playerName, Deck &reserves) {
  std::cout << playerName << " reserves: " << reserves.size() << std::endl;
  std::cout << reserves.print();
  std::cout << std::endl;
}

void Printer::printTroops(std::string playerName, Deck &troops) {
  std::cout << playerName << " troops: " << troops.print() << std::endl;
}

bool Printer::playAgainPrompt() {
  bool validInput = false;
  bool returnValue;
  std::string input;

  while (!validInput) {
    std::cout << std::endl;
    std::cout << "Play again? (y/n)" << std::endl;
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
      std::cout << "Please enter 'y' or 'n'" << std::endl;
    }
  }

  return returnValue;
}