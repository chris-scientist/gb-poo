// author: chris-scientist
// created at: 08/08/2018
// updated at: 08/09/2018

#include "MapController.h"

MapController::MapController(MapModel *aMapModel, MapView *aMapView) : model(aMapModel), view(aMapView) {
  
}

// Récupérer la position du joueur
const int* MapController::getPlayerPositions() const {
  return model->getPlayerPositions();
}

// Dessiner la carte
void MapController::paint(const int* aCameraPos) const {
  view->paint(aCameraPos);
}

// Déterminer si le jeu est terminée
bool MapController::isEndOfGame() const {
  return model->isFinish();
}

