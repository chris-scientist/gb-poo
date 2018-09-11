// author: chris-scientist
// created at: 08/08/2018
// updated at: 25/08/2018
// description: gestion de l'affichage de la carte

#ifndef MAPVIEW
#define MAPVIEW

#include <Gamebuino-Meta.h>

#include "TypeOfSprites.h"
#include "SpritesManager.h"
#include "MapModel.h"

class MapView {
  private:
    MapModel *mapModel;
    Image& getSprites(const char typeOfSprites) const;
  public:
    MapView(MapModel *aMapModel);
    void paint(const int* aCameraPos) const;
};

#endif

