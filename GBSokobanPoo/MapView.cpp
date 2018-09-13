// author: chris-scientist
// created at: 09/08/2018
// updated at: 26/08/2018

#include "MapView.h"

MapView::MapView(MapModel *aMapModel) : mapModel(aMapModel) {
  
}

// Dessiner la carte
void MapView::paint(const int* aCameraPos) const {
  gb.display.printf("Init pos %d,%d", mapModel->getPlayerPositions()[0], mapModel->getPlayerPositions()[1]);
}

