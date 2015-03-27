#include "stdafx.h"

#include <string>
#include <iostream>

#include "Player.h"
#include "Deck.h"
#include "Printer.h"
#include "Game.h"

void Game::start() {
  gameRunning = true;

  while (gameRunning) {
    newRound();
    playRound();

    Printer::printScore(roundsWon, roundsLost);

    bool validInput = false;
    std::string input;

    while (!validInput) {
      std::cout << std::endl;
      std::cout << "Play again? (y/n)" << std::endl;
      std::cin >> input;

      if (input == "y") {
        validInput = true;
      }
      else if (input == "n") {
        validInput = true;
        gameRunning = false;
      }
      else {
        validInput = false;
        std::cout << "Please enter 'y' or 'n'" << std::endl;
      }
    }
  }
}

void Game::newRound() {
  Deck fullDeck;
  //Burn the decks!! BURN THEM!
  playerOne.deck.clear();
  playerTwo.deck.clear();

  for (int count = Game::NUM_OF_DECKS; count > 0; count--){
    Deck::buildFullDeck(fullDeck);
  }

  fullDeck.shuffle();
  dealCards(fullDeck);
}

void Game::dealCards(Deck &fullDeck) {
  std::cout << "dealing cards..." << std::endl;
  int nextDeck = 1;

  while (fullDeck.size() > 0) {
    if (nextDeck == 1) {
      playerOne.deck.addCard(fullDeck.drawCard());
      nextDeck = 2;
    }
    else {
      playerTwo.deck.addCard(fullDeck.drawCard());
      nextDeck = 1;
    }
  }
}

void Game::playRound() {
  std::cout << std::endl;
  int turnCount = 0;
  while (playerOne.deck.size() > 0 && playerTwo.deck.size() > 0) {
    turn(turnCount);
  }

  if (playerOne.deck.size() == 0) {
    roundsLost++;
    std::cout << "You have lost the war." << std::endl;
  }
  else if (playerTwo.deck.size() == 0) {
    roundsWon++;
    std::cout << "You have won the war!" << std::endl;
  }

  std::cout << " === GAME OVER === " << std::endl;
}

void Game::turn(int &turnCount) {
  turnCount++;
  system("cls");

  std::cout << "Turn " << turnCount << std::endl;

  bool winner = false;

  Printer::printReserves("Your", playerOne.deck);
  Printer::printReserves("CPU", playerTwo.deck);

  while (!winner) {
    std::cout << std::endl;

    flipCards(playerOne);
    flipCards(playerTwo);

    Printer::printTroops("Your", playerOne.pile);
    Printer::printTroops(" CPU", playerTwo.pile);
    std::cout << std::endl;

    Card playerOneCard = playerOne.pile.drawCard(false);
    Card playerTwoCard = playerTwo.pile.drawCard(false);

    std::cout << playerOneCard.toString() << " vs. " << playerTwoCard.toString() << std::endl;
    std::cout << std::endl;

    if (playerOneCard.value() > playerTwoCard.value()) {
      winner = true;
      std::cout << "You won the battle" << std::endl;
      turnWon(playerOne, playerTwo);
    }
    else if (playerTwoCard.value() > playerOneCard.value()) {
      winner = true;
      std::cout << "You lost the battle" << std::endl;
      turnWon(playerTwo, playerOne);
    }
    else {
      std::cout << "tie!" << std::endl;
    }

    if (!AUTOMATE_WAR) {
      system("pause");
    }
  }

  std::cout << std::endl;
}

void Game::flipCards(Player &player) {
  for (int count = Game::CARDS_PER_TURN; count > 0; count--){
    if (player.deck.size() > 0) {
      player.pile.addCard(player.deck.drawCard(), false);
    }
  }
}

void Game::turnWon(Player &winner, Player &loser) {
  for (int count = loser.pile.size(); count > 0; count--){
    Card card = loser.pile.drawCard();
    std::cout << "  " << card.toString() << std::endl;
    winner.deck.addCard(card);
  }

  for (int count = winner.pile.size(); count > 0; count--){
    Card card = winner.pile.drawCard();
    winner.deck.addCard(card);
  }
}
