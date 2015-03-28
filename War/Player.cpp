#include "stdafx.h"

#include "Player.h"
#include "Game.h"

void Player::readyTroops() {
  for (int count = Game::TROOPS_PER_TURN; count > 0; count--){
    if (reserves.size() > 0) {
      troops.addCard(reserves.drawCard(), false);
    }
  }
}