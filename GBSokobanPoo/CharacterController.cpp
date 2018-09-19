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
  if(character->getNextPos()[1] >= 0 && !isWall(newTypeOfSprites)) {
    // déplacer une caisse
    if(isBox(newTypeOfSprites)) {
      newTypeOfSprites = moveBox(newTypeOfSprites, character->getNextPos()[0], character->getNextPos()[1], character->getNextPos()[0], character->getNextPos()[1] - 1);
    } else {
      stopMove = false;
    }

    if(!stopMove) {
      // écraser nouvelle position par la tuile du joueur
      mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
      // remplacer ancienne position par la tuile qui était à cette position précédement
      mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
      // stocker la tuile de la nouvelle position
      character->setOldTypeOfSprites(newTypeOfSprites);
      // mettre à jour la position
      character->updatePositions();
    } else {
      character->resetNextPositions();
    }
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
  if(character->getNextPos()[1] < MapModel::HEIGHT_MAP && !isWall(newTypeOfSprites)) {
    // déplacer une caisse
    if(isBox(newTypeOfSprites)) {
      newTypeOfSprites = moveBox(newTypeOfSprites, character->getNextPos()[0], character->getNextPos()[1], character->getNextPos()[0], character->getNextPos()[1] + 1);
    } else {
      stopMove = false;
    }

    if(!stopMove) {
      // écraser nouvelle position par la tuile du joueur
      mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
      // remplacer ancienne position par la tuile qui était à cette position précédement
      mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
      // stocker la tuile de la nouvelle position
      character->setOldTypeOfSprites(newTypeOfSprites);
      // mettre à jour la position
      character->updatePositions();
    } else {
      character->resetNextPositions();
    }
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
  if(character->getNextPos()[0] >= 0 && !isWall(newTypeOfSprites)) {
    // déplacer une caisse
    if(isBox(newTypeOfSprites)) {
      newTypeOfSprites = moveBox(newTypeOfSprites, character->getNextPos()[0], character->getNextPos()[1], character->getNextPos()[0] - 1, character->getNextPos()[1]);
    } else {
      stopMove = false;
    }

    if(!stopMove) {
      // écraser nouvelle position par la tuile du joueur
      mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
      // remplacer ancienne position par la tuile qui était à cette position précédement
      mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
      // stocker la tuile de la nouvelle position
      character->setOldTypeOfSprites(newTypeOfSprites);
      // mettre à jour la position
      character->updatePositions();
    } else {
      character->resetNextPositions();
    }
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
  if(character->getNextPos()[0] < MapModel::WIDTH_MAP && !isWall(newTypeOfSprites)) {
    // déplacer une caisse
    if(isBox(newTypeOfSprites)) {
      newTypeOfSprites = moveBox(newTypeOfSprites, character->getNextPos()[0], character->getNextPos()[1], character->getNextPos()[0] + 1, character->getNextPos()[1]);
    } else {
      stopMove = false;
    }

    if(!stopMove) {
      // écraser nouvelle position par la tuile du joueur
      mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
      // remplacer ancienne position par la tuile qui était à cette position précédement
      mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
      // stocker la tuile de la nouvelle position
      character->setOldTypeOfSprites(newTypeOfSprites);
      // mettre à jour la position
      character->updatePositions();
    } else {
      character->resetNextPositions();
    }
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

// Déterminer si le sprites est un mur
const bool CharacterController::isWall(const char aReplacedSprites) const {
  return (aReplacedSprites == TypeOfSprites::WALL_TYPE);
}

// Déterminer si le sprites est une caisse (sur zone de "chargement" ou non)
const bool CharacterController::isBox(const char aReplacedSprites) const {
  return (aReplacedSprites == TypeOfSprites::BOX_TYPE) || 
    (aReplacedSprites == TypeOfSprites::BOX_ON_ZONE_TYPE);
}

// Déplacer la caisse
const char CharacterController::moveBox(const char aReplacedSprites, const int aX1, const int aY1, const int aX2, const int aY2) {
  // on récupère le sprites en X2, Y2
  const char sprites = mapModel->getTypeOfSprites(aX2, aY2);
  // si c'est le sol ou une zone de chargement alors on déplace la caisse
  stopMove = !((sprites == TypeOfSprites::FLOOR_TYPE) || (sprites == TypeOfSprites::DESTINATION_TYPE));
  if(!stopMove) {
    // on calcul le sprites X2, Y2
    const char replacedSprites2 = (sprites == TypeOfSprites::DESTINATION_TYPE) ? TypeOfSprites::BOX_ON_ZONE_TYPE : TypeOfSprites::BOX_TYPE ;
    // on affecte le sprites X2, Y2
    mapModel->setTypeOfSprites(aX2, aY2, replacedSprites2);
    return (aReplacedSprites == TypeOfSprites::BOX_ON_ZONE_TYPE) ? TypeOfSprites::DESTINATION_TYPE : TypeOfSprites::FLOOR_TYPE;
  }
  return aReplacedSprites;
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

