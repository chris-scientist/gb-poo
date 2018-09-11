// author: chris-scientist
// created at: 08/08/2018
// updated at: 08/09/2018
// description: gestion de la carte du jeu

#ifndef MAPMODEL
#define MAPMODEL

#include "TypeOfSprites.h"

class MapModel {
  public:
    static const int HEIGHT_MAP = 11;
    static const int WIDTH_MAP = 19;
    
    MapModel();
    const int* getPlayerPositions() const;
    const char getTypeOfSprites(const int aXSprites, const int aYSprites);
    void setTypeOfSprites(const int aXSprites, const int aYSprites, const char aTypeOfSprites);
    bool isFinish() const;
  private:
    char mapOfGame[HEIGHT_MAP][WIDTH_MAP] = {
      { ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
      { ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
      { ' ', ' ', ' ', ' ', '#', '$', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
      { ' ', ' ', '#', '#', '#', ' ', ' ', '$', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
      { ' ', ' ', '#', ' ', ' ', '$', ' ', '$', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
      { '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', },
      { '#', ' ', ' ', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', '.', '.', '#', },
      { '#', ' ', '$', ' ', ' ', '$', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', '.', '#', },
      { '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '@', '#', '#', ' ', ' ', '.', '.', '#', },
      { ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
      { ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', }
    };
    int playerPositions[2] = {-1, -1}; // 0 = position X, 1 = position Y
    
    void initPlayerPositions();
};

#endif

