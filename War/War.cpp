#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>

#include "Card.h"
#include "Suit.h"

using namespace std;

const int MAX_CARD_VALUE = 14; //Aces high
const int MIN_CARD_VALUE = 2;
const int CARDS_PER_TURN = 3;
const int NUM_OF_DECKS = 1;
const bool AUTOMATE_WAR = false;


void printCard(Card);

class Deck {
  vector<Card> cards;

  public:
    Card drawCard() {
      return drawCard(true);
    }

    Card drawCard(bool removeFromDeck) {
      Card topCard = cards.back();

      if (removeFromDeck) {
        cards.pop_back();
      }

      return topCard;
    }

    void addCard(Card card) {
      addCard(card, true);
    }

    void addCard(Card card, bool toBottom) {
      if (toBottom) {
        cards.insert(cards.begin(), card);
      }
      else {
        cards.insert(cards.end(), card);
      }
    }

    void shuffle() {
      cout << "Shuffling cards..." << endl;
      int maxSize = cards.size() - 1;

      srand(time(NULL));

      for (int index1 = 0; index1 <= maxSize; index1++) {
        int index2 = rand() % maxSize;

        Card card1 = cards[index1];
        Card card2 = cards[index2];

        cards[index1] = card2;
        cards[index2] = card1;
      }
    }

    int size() {
      return cards.size();
    }

    void clear() {
      cards.clear();
    }

    string print() {
      string line = "";
      if (cards.size() > 0) {
        line += "[{O}]";
      }

      for (int count = cards.size() - 1; count > 0; count--){
        line += "]";
      }

      return line;
    }

    static void buildFullDeck(Deck &fullDeck) {
      buildSuit(fullDeck, Suit::HEART);
      buildSuit(fullDeck, Suit::SPADE);
      buildSuit(fullDeck, Suit::DIAMOND);
      buildSuit(fullDeck, Suit::CLUB);
    }

    static void buildSuit(Deck &fullDeck, Suit suit) {
      for (int value = MIN_CARD_VALUE; value <= MAX_CARD_VALUE; value++) {
        Card card = Card(value, suit);
        fullDeck.addCard(card);
      }
    }
};

struct Player {
  Deck pile;
  Deck deck;
};

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
