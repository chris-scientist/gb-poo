// author: chris-scientist
// created at: 08/08/2018
// updated at: 08/09/2018

#include "MainController.h"

MainController::MainController(MapController *aMapController, CameraModel *aCameraModel, CharacterController * aCharacterController) : mapController(aMapController), cameraModel(aCameraModel), characterController(aCharacterController) {
  
}

void MainController::run() {
  gb.display.println("v2.0.0"); // A SUPPRIMER
  gb.display.printf("Player pos %d,%d", characterController->getX(), characterController->getY());
  gb.display.println("");
  const int* cameraPos = cameraModel->getCameraPositions(characterController->getX(), characterController->getY());
  gb.display.printf("Cam %d,%d : %d,%d", cameraPos[0], cameraPos[1], cameraPos[2], cameraPos[3]);
  gb.display.println("");
  mapController->paint(cameraPos);
}

