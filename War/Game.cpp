#include "stdafx.h"

#include <string>

#include "Player.h"
#include "Deck.h"
#include "Display.h"
#include "Game.h"
#include "Outcome.h"

void Game::start() {
  gameRunning = true;

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
  playerOne.deck.clear();
  playerTwo.deck.clear();

  for (int count = Game::NUM_OF_DECKS; count > 0; count--){
    Deck::buildFullDeck(fullDeck);
  }

  fullDeck.shuffle();
  dealCards(fullDeck);
}

void Game::dealCards(Deck &fullDeck) {
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
  Display::printLine();

  int turnCount = 0;
  while (playerOne.deck.size() > 0 && playerTwo.deck.size() > 0) {
    nextTurn(turnCount);
  }

  if (playerOne.deck.size() == 0) {
    roundsLost++;
    Display::playerLostWar();
  }
  else if (playerTwo.deck.size() == 0) {
    roundsWon++;
    Display::playerWonWar();
  }
}

void Game::nextTurn(int &turnCount) {
  turnCount++;
  Outcome battleOutcome;

  Display::clear();
  Display::printLine("Turn " + std::to_string(turnCount));
  Display::printReserves("Your", playerOne.deck);
  Display::printReserves("CPU", playerTwo.deck);
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

  playerOne.flipCards();
  playerTwo.flipCards();

  Card playerOneCard = playerOne.pile.drawCard(false);
  Card playerTwoCard = playerTwo.pile.drawCard(false);

  Display::printTroops("Your", playerOne.pile);
  Display::printTroops(" CPU", playerTwo.pile);
  Display::printLine();

  Display::printLine(playerOneCard.toString() + " vs. " + playerTwoCard.toString());
  Display::printLine();

  if (playerOneCard.value() > playerTwoCard.value()) {
    return Outcome::PLAYER_WON;
  }
  else if (playerOneCard.value() < playerTwoCard.value()) {
    return Outcome::PLAYER_LOST;
  }
  else {
    return Outcome::TIE;
  }
}

void Game::turnComplete(Outcome outcome) {
  Player winner;
  Player loser;

  if (outcome == Outcome::PLAYER_WON) {
    Display::printLine("You won the battle");
    winner = playerOne;
    loser = playerTwo;
  }
  else if (outcome == Outcome::PLAYER_LOST) {
    Display::printLine("You lost the battle");
    winner = playerTwo;
    loser = playerOne;
  }

  for (int count = loser.pile.size(); count > 0; count--){
    Card card = loser.pile.drawCard();
    Display::printLine("  " + card.toString());
    winner.deck.addCard(card);
  }

  for (int count = winner.pile.size(); count > 0; count--){
    Card card = winner.pile.drawCard();
    winner.deck.addCard(card);
  }
}
