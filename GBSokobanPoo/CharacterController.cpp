// author: chris-scientist
// created at: 26/08/2018
// updated at: 08/08/2018

#include "CharacterController.h"

CharacterController::CharacterController(CharacterModel *aCharacter, MapModel *aMapModel) : character(aCharacter), mapModel(aMapModel), stopMove(false) {
  
}

void CharacterController::goUp() {
  // calcul de la nouvelle position
  character->goUp();
  // récupérer la tuile de la nouvelle position
  char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
  // si la nouvelle position du personnage est sur la carte
  if(character->getNextPos()[1] >= 0) {
    // écraser nouvelle position par la tuile du joueur
    mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
    // remplacer ancienne position par la tuile qui était à cette position précédement
    mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
    // stocker la tuile de la nouvelle position
    character->setOldTypeOfSprites(newTypeOfSprites);
    // mettre à jour la position
    character->updatePositions();
  } else {
    // remettre à zéro la position suivante
    character->resetNextPositions();
  }
}

void CharacterController::goDown() {
  // calcul de la nouvelle position
  character->goDown();
  // récupérer la tuile de la nouvelle position
  char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
  // si la nouvelle position du personnage est sur la carte et que ce n'est pas un mur
  if(character->getNextPos()[1] < MapModel::HEIGHT_MAP) {
    // écraser nouvelle position par la tuile du joueur
    mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
    // remplacer ancienne position par la tuile qui était à cette position précédement
    mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
    // stocker la tuile de la nouvelle position
    character->setOldTypeOfSprites(newTypeOfSprites);
    // mettre à jour la position
    character->updatePositions();
  } else {
    // remettre à zéro la position suivante
    character->resetNextPositions();
  }
}

void CharacterController::goLeft() {
  // calcul de la nouvelle position
  character->goLeft();
  // récupérer la tuile de la nouvelle position
  char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
  // si la nouvelle position du personnage est sur la carte et que ce n'est pas un mur
  if(character->getNextPos()[0] >= 0) {
    // écraser nouvelle position par la tuile du joueur
    mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
    // remplacer ancienne position par la tuile qui était à cette position précédement
    mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
    // stocker la tuile de la nouvelle position
    character->setOldTypeOfSprites(newTypeOfSprites);
    // mettre à jour la position
    character->updatePositions();
  } else {
    // remettre à zéro la position suivante
    character->resetNextPositions();
  }
}

void CharacterController::goRight() {
  // calcul de la nouvelle position
  character->goRight();
  // récupérer la tuile de la nouvelle position
  char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
  // si la nouvelle position du personnage est sur la carte et que ce n'est pas un mur
  if(character->getNextPos()[0] < MapModel::WIDTH_MAP) {
    // écraser nouvelle position par la tuile du joueur
    mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
    // remplacer ancienne position par la tuile qui était à cette position précédement
    mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
    // stocker la tuile de la nouvelle position
    character->setOldTypeOfSprites(newTypeOfSprites);
    // mettre à jour la position
    character->updatePositions();
  } else {
    // remettre à zéro la position suivante
    character->resetNextPositions();
  }
}

// Calculer la tuile du joueur en fonction de celle à remplacer
char CharacterController::getPlayerSprites(const char aReplacedSprites) const {
  if((aReplacedSprites == TypeOfSprites::DESTINATION_TYPE) || (aReplacedSprites == TypeOfSprites::BOX_ON_ZONE_TYPE)) {
    return TypeOfSprites::PLAYER_ON_ZONE_TYPE;
  }
  return TypeOfSprites::PLAYER_TYPE;
}

void CharacterController::run() {
  if(gb.buttons.pressed(BUTTON_UP)) {
    goUp();
  } else if(gb.buttons.pressed(BUTTON_RIGHT)) {
    goRight();
  }  else if(gb.buttons.pressed(BUTTON_DOWN)) {
    goDown();
  } else if(gb.buttons.pressed(BUTTON_LEFT)) {
    goLeft();
  }
}

const int CharacterController::getX() const {
  return character->getX();
}

const int CharacterController::getY() const {
  return character->getY();
}

