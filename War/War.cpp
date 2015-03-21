#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>

using namespace std;

const int MAX_CARD_VALUE = 14; //Aces high
const int MIN_CARD_VALUE = 2;
const int FACE_DOWN_CARDS = 3;

enum Suit {
  HEART, CLUB, DIAMOND, SPADE
};

enum Value {
  JACK = 11, QUEEN, KING, ACE
};

class Card {
  int _value;
  Suit _suit;

  public:
    Card(int value, Suit suit) {
      _value = value;
      _suit = suit;
    }

    Suit suit() {
      return _suit;
    }

    int value() {
      return _value;
    }

    string suitName() {
      switch (_suit) {
        case HEART:
          return "Hearts";
        case DIAMOND:
          return "Hearts";
        case SPADE:
          return "Spades";
        case CLUB:
          return "Clubs"; 
        default:
          return "Unknown";
      }
    }

    string valueName() {
      switch (_value) {
        case ACE:
          return "Ace";
        case KING:
          return "King";
        case QUEEN:
          return "Queen";
        case JACK:
          return "Jack";
        default:
          return to_string(_value);
      }
    }

    string toString() {
      return valueName() + " of " + suitName();
    }
};

void printCard(Card);

class Deck {
  vector<Card> cards;

  public:
    Card drawCard() {
      Card topCard = cards.back();
      cards.pop_back();
      return topCard;
    }

    void addCard(Card card) {
      cards.insert(cards.begin(), card);
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

    static void buildFullDeck(Deck &fullDeck) {
      buildSuit(fullDeck, HEART);
      buildSuit(fullDeck, SPADE);
      buildSuit(fullDeck, DIAMOND);
      buildSuit(fullDeck, CLUB);
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

class Game {
  public:
    void start() {
      gameRunning = true;

      while (gameRunning) {
        newRound();
        playRound();

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

      Deck::buildFullDeck(fullDeck);
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
        cout << "You have lost the war." << endl;
      }
      else if (playerTwo.deck.size() == 0) {
        cout << "You have won the war!" << endl;
      }

      cout << " === GAME OVER === " << endl;
    }

    void turn(int &turnCount) {
      turnCount++;
      cout << "Turn " << turnCount << endl;

      bool winner = false;

      cout << "Your reserves: " << playerOne.deck.size() << endl;
      if (playerOne.deck.size() > 0) {
        cout << "[:-:";
      }

      for (int count = playerOne.deck.size(); count > 0; count--){
        cout << "]";
      }
      cout << endl;
      
      cout << "CPU reserves:  " << playerTwo.deck.size() << endl;
      if (playerTwo.deck.size() > 0) {
        cout << "[:-:";
      }

      for (int count = playerTwo.deck.size(); count > 0; count--){
        cout << "]";
      }
      cout << endl;

      while (!winner) {
        cout << endl;

        cout << "Your troops: ";
        flipCards(playerOne.pile, playerOne.deck);
        cout << endl;

        cout << "CPU troops:  ";
        flipCards(playerTwo.pile, playerTwo.deck);
        cout << endl;

        Card playerOneCard = playerOne.pile.drawCard();
        Card playerTwoCard = playerTwo.pile.drawCard();

        cout << playerOneCard.toString() << " vs. " << playerTwoCard.toString() << endl;

        playerOne.pile.addCard(playerOneCard);
        playerTwo.pile.addCard(playerTwoCard);

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

        system("pause");
      }

      cout << endl;
    }

    void flipCards(Deck &pile, Deck &deck) {
      for (int count = FACE_DOWN_CARDS; count > 0; count--){
        if (deck.size() > 0) {
          pile.addCard(deck.drawCard());
        }
      }

      if (pile.size() > 0) {
        cout << "[:-:";
      }

      for (int count = pile.size(); count > 0; count--){
        cout << "]";
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
