// author: chris-scientist
// created at: 22/08/2018
// description: gestion de la caméra

#ifndef CAMERAMODEL
#define CAMERAMODEL

#include "Constantes.h"
#include "SpritesManager.h"
#include "MapModel.h"

class CameraModel {
  private:
    static const int W_CENTER_PLAYER;
    static const int H_CENTER_PLAYER;
  
    const int getNbSpritesInWidth();
    const int getNbSpritesInHeight();
    int cameraPositions[4] = {-1, -1, -1, -1}; // 0 = position X0, 1 = position Y0, 2 = position X1, 3 = position Y1
  public:
    const int* getCameraPositions(const int aX, const int aY);
};

#endif

