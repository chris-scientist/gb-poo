// author: chris-scientist
// created at: 26/08/2018
// updated at: 08/08/2018

#include "CharacterController.h"

CharacterController::CharacterController(CharacterModel *aCharacter, MapModel *aMapModel) : character(aCharacter), mapModel(aMapModel), stopMove(false) {
  
}

const int CharacterController::getX() const {
  return character->getX();
}

const int CharacterController::getY() const {
  return character->getY();
}

