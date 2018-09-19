// author: chris-scientist
// created at: 08/08/2018
// updated at: 08/09/2018

#include "MainController.h"

MainController::MainController(MapController *aMapController, CameraModel *aCameraModel, CharacterController * aCharacterController) : mapController(aMapController), cameraModel(aCameraModel), characterController(aCharacterController) {
  
}

void MainController::run() {
  if(! mapController->isEndOfGame()) {
    characterController->run();
    const int* cameraPos = cameraModel->getCameraPositions(characterController->getX(), characterController->getY());
    mapController->paint(cameraPos);
  } else {
    gb.display.setFontSize(2);
    gb.display.setColor(BROWN);
    gb.display.println("");
    gb.display.println("");
    gb.display.println("  Gagne");
  }
}

