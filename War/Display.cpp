#include "stdafx.h"

#include <iostream>
#include <string>

#include "Display.h"
#include "Deck.h"
#include "Game.h"

void Display::printScore(int &won, int &lost) {
  Display::printLine();
  std::cout << "Score:" << std::endl;
  std::cout << "Won:" << won << std::endl;
  std::cout << "Lost:" << lost << std::endl;
}

void Display::printReserves(std::string playerName, Deck &reserves) {
  std::cout << playerName << " reserves: " << reserves.size() << std::endl;
  std::cout << reserves.print();
  Display::printLine();
}

void Display::printTroops(std::string playerName, Deck &troops) {
  std::cout << playerName << " troops: " << troops.print() << std::endl;
}

bool Display::playAgainPrompt() {
  bool validInput = false;
  bool returnValue;
  std::string input;

  while (!validInput) {
    Display::printLine();
    Display::printLine("Play again? (y/n)");

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
      Display::printLine("Please enter 'y' or 'n'");
    }
  }

  return returnValue;
}

void Display::printLine() {
  Display::printLine("");
}

void Display::printLine(std::string line) {
  std::cout << line << std::endl;
}

void Display::playerWonWar() {
  Display::warEnd("You won the war");
}

void Display::playerLostWar() {
  Display::warEnd("You lost the war");
}

void Display::warEnd(std::string message) {
  Display::printLine(message);
  Display::printLine("== GAME OVER ==");
}

void Display::clear() {
  system("cls");
}

void Display::anyKeyToContinue() {
  if (!Game::AUTOMATE_WAR) {
    system("pause");
  }
}
