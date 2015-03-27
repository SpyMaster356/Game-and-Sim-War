#include "stdafx.h"

#include "Player.h"
#include "Game.h"

void Player::flipCards() {
  for (int count = Game::CARDS_PER_TURN; count > 0; count--){
    if (reserves.size() > 0) {
      troops.addCard(reserves.drawCard(), false);
    }
  }
}