#include "stdafx.h"

#include <string>

#include "Player.h"
#include "Deck.h"
#include "Display.h"
#include "Game.h"
#include "Outcome.h"

const int Game::TROOPS_PER_TURN = 3;
const int Game::NUM_OF_DECKS = 1;
const bool Game::AUTOMATE_WAR = false;

void Game::start() {
  this->gameRunning = true;
  this->roundsWon = 0;
  this->roundsLost = 0;

  while (gameRunning) {
    newRound();
    playRound();

    Display::printScore(roundsWon, roundsLost);
    bool playAgain = Display::playAgainPrompt();

    if (!playAgain) {
      gameRunning = false;
    }
  }
}

void Game::newRound() {
  Deck fullDeck;
  //Burn the decks!! BURN THEM!
  playerOne.reserves.clear();
  playerTwo.reserves.clear();

  for (int count = Game::NUM_OF_DECKS; count > 0; count--) {
    Deck::buildFullDeck(fullDeck);
  }

  fullDeck.shuffle();
  dealCards(fullDeck);
}

void Game::dealCards(Deck &fullDeck) {
  int nextDeck = 1;

  while (fullDeck.size() > 0) {
    if (nextDeck == 1) {
      playerOne.reserves.addCard(fullDeck.drawCard());
      nextDeck = 2;
    }
    else {
      playerTwo.reserves.addCard(fullDeck.drawCard());
      nextDeck = 1;
    }
  }
}

void Game::playRound() {
  Display::printLine();

  int turnCount = 0;
  while (playerOne.reserves.size() > 0 && playerTwo.reserves.size() > 0) {
    nextTurn(turnCount);
  }

  if (playerOne.reserves.size() == 0) {
    roundsLost++;
    Display::playerLostWar();
  }
  else if (playerTwo.reserves.size() == 0) {
    roundsWon++;
    Display::playerWonWar();
  }
}

void Game::nextTurn(int &turnCount) {
  turnCount++;
  Outcome battleOutcome;

  Display::clear();
  Display::printLine("Turn " + std::to_string(turnCount));
  Display::printReserves("Your", playerOne.reserves);
  Display::printReserves("CPU", playerTwo.reserves);
  Display::anyKeyToContinue();

  do {
    battleOutcome = Game::performBattle();
    
    Display::anyKeyToContinue();
    
    if (battleOutcome == Outcome::TIE) {
      Display::printLine("Tie!");
    }

  } while (battleOutcome == Outcome::TIE);

  turnComplete(battleOutcome);

  Display::anyKeyToContinue();
}

Outcome Game::performBattle() {
  Display::printLine();

  playerOne.readyTroops();
  playerTwo.readyTroops();

  Card playerOneCard = playerOne.troops.drawCard(false);
  Card playerTwoCard = playerTwo.troops.drawCard(false);

  Display::printTroops("Your", playerOne.troops);
  Display::printTroops(" CPU", playerTwo.troops);
  Display::printLine();

  Display::printLine(playerOneCard.toString() + " vs. " + playerTwoCard.toString());
  Display::printLine();

  if (playerOneCard > playerTwoCard) {
    return Outcome::PLAYER_WON;
  }
  else if (playerOneCard < playerTwoCard) {
    return Outcome::PLAYER_LOST;
  }
  else {
    return Outcome::TIE;
  }
}

void Game::turnComplete(Outcome outcome) {
  Player *winnerPtr;
  Player *loserPtr;

  if (outcome == Outcome::PLAYER_WON) {
    Display::printLine("You won the battle");
    winnerPtr = &playerOne;
    loserPtr = &playerTwo;
  }
  else if (outcome == Outcome::PLAYER_LOST) {
    Display::printLine("You lost the battle");
    winnerPtr = &playerTwo;
    loserPtr = &playerOne;
  }
  else {
    return;
  }

  for (int count = loserPtr->troops.size(); count > 0; count--){
    Card card = loserPtr->troops.drawCard();
    Display::printLine("  " + card.toString());
    winnerPtr->reserves.addCard(card);
  }

  for (int count = winnerPtr->troops.size(); count > 0; count--){
    Card card = winnerPtr->troops.drawCard();
    winnerPtr->reserves.addCard(card);
  }
}
