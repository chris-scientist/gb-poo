// author: chris-scientist
// created at: 25/08/2018
// updated at: 26/06/2018

#include "CharacterModel.h"

CharacterModel::CharacterModel(const int* initPlayerPos) : x(initPlayerPos[0]), y(initPlayerPos[1]), oldTypeOfSprites(TypeOfSprites::FLOOR_TYPE) {
  nextPos[0] = x;
  nextPos[1] = y;
}

// Calculer la position si l'on va en haur
void CharacterModel::goUp() {
  nextPos[1] = y - 1;
}

// Calculer la position si l'on va en bas
void CharacterModel::goDown() {
  nextPos[1] = y + 1;
}

// Calculer la position si l'on va à gauche
void CharacterModel::goLeft() {
  nextPos[0] = x - 1;
}

// Calculer la position si l'on va à droite
void CharacterModel::goRight() {
  nextPos[0] = x + 1;
}

// Mettre à jour la position du joueur
void CharacterModel::updatePositions() {
  x = nextPos[0];
  y = nextPos[1];
}

// Remettre à zéro la positions suivante
void CharacterModel::resetNextPositions() {
  nextPos[0] = x;
  nextPos[1] = y;
}

const int CharacterModel::getX() const {
  return x;
}

const int CharacterModel::getY() const {
  return y;
}

const int * CharacterModel::getNextPos() const {
  return nextPos;
}

const char CharacterModel::getOldTypeOfSprites() const {
  return oldTypeOfSprites;
}

void CharacterModel::setOldTypeOfSprites(const char aOldTypeOfSprites) {
  oldTypeOfSprites = aOldTypeOfSprites;
}

