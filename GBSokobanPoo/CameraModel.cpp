// author: chris-scientist
// created at: 22/08/2018
// updated at: 25/08/2018

#include "CameraModel.h"

const int CameraModel::W_CENTER_PLAYER = 5; // si possible, on dessine 5 sprites avant de dessiner le joueur
const int CameraModel::H_CENTER_PLAYER = 4; // si possible, on dessine 4 sprites avant de dessiner le joueur

// Calculer le nombres de sprites en largeur
const int CameraModel::getNbSpritesInWidth() {
  return (WIDTH_SCREEN / SpritesManager::WIDTH_SPRITES);
}

// Calculer le nombre de sprites en hauteur
const int CameraModel::getNbSpritesInHeight() {
  return (HEIGHT_SCREEN / SpritesManager::HEIGHT_SPRITES);
}

// Calculer la position de la caméra
const int* CameraModel::getCameraPositions(const int aX, const int aY) {

  // Par défaut, nous essayons de centrer la caméra sur le personnage soit :
  // - en largeur : 5 sprites + le personnage + 4 sprites
  // - en hauteur : 4 sprites + le personnage + 3 sprites
  cameraPositions[0] = aX - CameraModel::W_CENTER_PLAYER;
  cameraPositions[1] = aY - CameraModel::H_CENTER_PLAYER;
  cameraPositions[2] = cameraPositions[0] + getNbSpritesInWidth() + 1;
  cameraPositions[3] = cameraPositions[1] + getNbSpritesInHeight() + 1;

  // si la caméra est en-dehors de la carte
  bool cameraX0Out = (cameraPositions[0] < 0);
  bool cameraY0Out = (cameraPositions[1] < 0);
  bool cameraX1Out = (cameraPositions[2] >= MapModel::WIDTH_MAP);
  bool cameraY1Out = (cameraPositions[3] >= MapModel::HEIGHT_MAP);
  if(cameraX0Out || cameraY0Out || cameraX1Out || cameraY1Out) {
    if(cameraX0Out) {
      cameraPositions[0] = 0;
      cameraPositions[2] = cameraPositions[0] + getNbSpritesInWidth() + 1;
    }
    if(cameraY0Out) {
      cameraPositions[1] = 0;
      cameraPositions[3] = cameraPositions[1] + getNbSpritesInHeight() + 1;
    }
    if(cameraX1Out) {
      cameraPositions[2] = MapModel::WIDTH_MAP;
      cameraPositions[0] = cameraPositions[2] - getNbSpritesInWidth();
    }
    if(cameraY1Out) {
      cameraPositions[3] = MapModel::HEIGHT_MAP;
      cameraPositions[1] = cameraPositions[3] - getNbSpritesInHeight();
    }
  }

  return cameraPositions;
}

