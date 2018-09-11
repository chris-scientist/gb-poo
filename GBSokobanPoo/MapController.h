// author: chris-scientist
// created: 08/08/2018
// updated at: 08/09/2018

#ifndef MAPCONTROLLER
#define MAPCONTROLLER

#include "MapModel.h"
#include "MapView.h"

class MapController {
  private:
    MapModel *model;
    MapView *view;
  public:
    MapController(MapModel *aMapModel, MapView *aMapView);
    const int* getPlayerPositions() const;
    void paint(const int* aCameraPos) const;
    bool isEndOfGame() const;
};

#endif
