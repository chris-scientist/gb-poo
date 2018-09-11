// author: chris-scientist
// created at: 25/08/2018
// updated at: 26/08/2018
// description: gestion du personnage

#ifndef CHARACTERMODEL
#define CHARACTERMODEL

#include "TypeOfSprites.h"

class CharacterModel {
  private:
    int x;
    int y;
    int nextPos[2] = {-1, -1}; // 0 = x, 1 = y
    char oldTypeOfSprites;
  public:
    CharacterModel(const int* initPlayerPos);
    const int getX() const;
    const int getY() const;
    const int * getNextPos() const;
    const char getOldTypeOfSprites() const;
    void setOldTypeOfSprites(const char aOldTypeOfSprites);
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    void updatePositions();
    void resetNextPositions();
};

#endif

