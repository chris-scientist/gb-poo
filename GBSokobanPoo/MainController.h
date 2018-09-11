// author: chris-scientist
// created at: 08/08/2018
// updated at: 26/08/2018
// description: contrôleur principale, permet de gérer globalement l'application

#ifndef MAINCONTROLLER
#define MAINCONTROLLER

#include <Gamebuino-Meta.h>

#include "MapController.h"
#include "CameraModel.h"
#include "CharacterController.h"

class MainController {
  private:
    CharacterController * characterController;
    MapController *mapController;
    CameraModel *cameraModel;
  public:
    MainController(MapController *aMapController, CameraModel *aCameraModel, CharacterController * aCharacterController);
    void run();
};

#endif
