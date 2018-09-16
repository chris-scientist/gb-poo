// author: chris-scientist
// created at: 09/08/2018
// updated at: 26/08/2018

#include "MapView.h"

MapView::MapView(MapModel *aMapModel) : mapModel(aMapModel) {
  
}

// Dessiner la carte
void MapView::paint(const int* aCameraPos) const {
  //gb.display.printf("Init pos %d,%d", mapModel->getPlayerPositions()[0], mapModel->getPlayerPositions()[1]);
  /*gb.display.drawImage(0, 0, getSprites(TypeOfSprites::PLAYER_TYPE));
  gb.display.drawImage(16, 0, getSprites(TypeOfSprites::WALL_TYPE));
  gb.display.drawImage(32, 0, getSprites(TypeOfSprites::BOX_TYPE));
  gb.display.drawImage(48, 0, getSprites(TypeOfSprites::DESTINATION_TYPE));
  gb.display.drawImage(0, 16, getSprites(TypeOfSprites::PLAYER_ON_ZONE_TYPE));
  gb.display.drawImage(16, 16, getSprites(TypeOfSprites::FLOOR_TYPE));
  gb.display.drawImage(32, 16, getSprites(TypeOfSprites::BOX_ON_ZONE_TYPE));*/
  int l = 0;
  for(int y = aCameraPos[1] ; y < aCameraPos[3] ; y++) {
    int c = 0;
    for(int x = aCameraPos[0] ; x < aCameraPos[2] ; x++) {
      gb.display.drawImage(c*SpritesManager::WIDTH_SPRITES, l*SpritesManager::HEIGHT_SPRITES, getSprites(mapModel->getTypeOfSprites(x, y)));
      c++;
    }
    l++;
  }
}

// Récupérer l'image en fonction du type de sprites
Image& MapView::getSprites(const char typeOfSprites) const {
  switch(typeOfSprites) {
    case TypeOfSprites::WALL_TYPE:
      return SpritesManager::getWall();
    break;
    case TypeOfSprites::BOX_TYPE:
      return SpritesManager::getBox();
    break;
    case TypeOfSprites::DESTINATION_TYPE:
      return SpritesManager::getArea();
    break;
    case TypeOfSprites::BOX_ON_ZONE_TYPE:
      return SpritesManager::getBoxOnArea();
    break;
    case TypeOfSprites::PLAYER_TYPE:
      return SpritesManager::getCharacter();
    break;
    case TypeOfSprites::PLAYER_ON_ZONE_TYPE:
      return SpritesManager::getCharacterOnArea();
    break;
    case TypeOfSprites::FLOOR_TYPE:
      return SpritesManager::getFloorImg();
    break;
  }
}

