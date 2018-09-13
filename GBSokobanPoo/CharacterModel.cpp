// author: chris-scientist
// created at: 25/08/2018
// updated at: 26/06/2018

#include "CharacterModel.h"

CharacterModel::CharacterModel(const int* initPlayerPos) : x(initPlayerPos[0]), y(initPlayerPos[1]), oldTypeOfSprites(TypeOfSprites::FLOOR_TYPE) {
  nextPos[0] = x;
  nextPos[1] = y;
}

const int CharacterModel::getX() const {
  return x;
}

const int CharacterModel::getY() const {
  return y;
}

