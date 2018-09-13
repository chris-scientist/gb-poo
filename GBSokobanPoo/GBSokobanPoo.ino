// author: chris-scientist
// created at: 08/08/2018
// updated at: 26/08/2018

#include <Gamebuino-Meta.h>

#include "MainController.h"
#include "MapController.h"
#include "MapModel.h"
#include "MapView.h"
#include "CameraModel.h"
#include "CharacterController.h"
#include "CharacterModel.h"

MainController * mainController;
MapModel * mapModel;
MapController * mapController;

void setup() {
  // initialiser la gamebuino
  gb.begin();
  // initialision de l'application
  mapModel = new MapModel();
  mapController = new MapController(mapModel, new MapView(mapModel));
  mainController = new MainController(mapController, new CameraModel(), new CharacterController(new CharacterModel(mapController->getPlayerPositions()), mapModel));
}

void loop() {
  // boucle d'attente
  while(!gb.update());

  // effacer l'écran
  gb.display.clear();

  mainController->run();
}
