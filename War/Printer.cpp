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