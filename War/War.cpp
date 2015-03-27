#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "Card.h"
#include "Suit.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

const int CARDS_PER_TURN = 3;
const int NUM_OF_DECKS = 1;
const bool AUTOMATE_WAR = true;


void printCard(Card);

class Printer {
  public:
    static void printScore(int &won, int &lost) {
      cout << endl;
      cout << "Score:" << endl;
      cout << "Won:" << won << endl;
      cout << "Lost:" << lost << endl;
    }

    static void printReserves(string playerName, Deck &reserves) {
      cout << playerName << " reserves: " << reserves.size() << endl;
      cout << reserves.print();
      cout << endl;
    }

    static void printTroops(string playerName, Deck &troops) {
      cout << playerName << " troops: " << troops.print() << endl;
    }
};

class Game {
  int roundsWon = 0;
  int roundsLost = 0;

  public:
    void start() {
      gameRunning = true;

      while (gameRunning) {
        newRound();
        playRound();

        Printer::printScore(roundsWon, roundsLost);

        bool validInput = false;
        string input;

        while (!validInput) {
          cout << endl;
          cout << "Play again? (y/n)" << endl;
          cin >> input;

          if (input == "y") {
            validInput = true;
          }
          else if (input == "n") {
            validInput = true;
            gameRunning = false;
          }
          else {
            validInput = false;
            cout << "Please enter 'y' or 'n'" << endl;
          }
        }
      }
    }

  private:
    bool gameRunning;
    Player playerOne;
    Player playerTwo;

    void newRound() {
      Deck fullDeck;
      //Burn the decks!! BURN THEM!
      playerOne.deck.clear();
      playerTwo.deck.clear();

      for (int count = NUM_OF_DECKS; count > 0; count--){
        Deck::buildFullDeck(fullDeck);
      }

      fullDeck.shuffle();
      dealCards(fullDeck);
    }

    void dealCards(Deck &fullDeck) {
      cout << "dealing cards..." << endl;
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

    void playRound() {
      cout << endl;
      int turnCount = 0;
      while (playerOne.deck.size() > 0 && playerTwo.deck.size() > 0) {
        turn(turnCount);
      }

      if (playerOne.deck.size() == 0) {
        roundsLost++;
        cout << "You have lost the war." << endl;
      }
      else if (playerTwo.deck.size() == 0) {
        roundsWon++;
        cout << "You have won the war!" << endl;
      }

      cout << " === GAME OVER === " << endl;
    }

    void turn(int &turnCount) {
      turnCount++;
      system("cls");

      cout << "Turn " << turnCount << endl;

      bool winner = false;

      Printer::printReserves("Your", playerOne.deck);
      Printer::printReserves("CPU", playerTwo.deck);

      while (!winner) {
        cout << endl;

        flipCards(playerOne);
        flipCards(playerTwo);

        Printer::printTroops("Your", playerOne.pile);
        Printer::printTroops(" CPU", playerTwo.pile);
        cout << endl;

        Card playerOneCard = playerOne.pile.drawCard(false);
        Card playerTwoCard = playerTwo.pile.drawCard(false);

        cout << playerOneCard.toString() << " vs. " << playerTwoCard.toString() << endl;
        cout << endl;

        if (playerOneCard.value() > playerTwoCard.value()) {
          winner = true;
          cout << "You won the battle" << endl;
          turnWon(playerOne, playerTwo);
        }
        else if (playerTwoCard.value() > playerOneCard.value()) {
          winner = true;
          cout << "You lost the battle" << endl;
          turnWon(playerTwo, playerOne);
        }
        else {
          cout << "tie!" << endl;
        }

        if (!AUTOMATE_WAR) {
          system("pause");
        }
      }

      cout << endl;
    }

    void flipCards(Player &player) {
      for (int count = CARDS_PER_TURN; count > 0; count--){
        if (player.deck.size() > 0) {
          player.pile.addCard(player.deck.drawCard(), false);
        }
      }
    }

    void turnWon(Player &winner, Player &loser) {
      for (int count = loser.pile.size(); count > 0; count--){
        Card card = loser.pile.drawCard();
        cout << "  " << card.toString() << endl;
        winner.deck.addCard(card);
      }

      for (int count = winner.pile.size(); count > 0; count--){
        Card card = winner.pile.drawCard();
        winner.deck.addCard(card);
      }
    }
};

int _tmain(int argc, _TCHAR* argv[]) {
  Game game;

  game.start();

  return 0;
}
