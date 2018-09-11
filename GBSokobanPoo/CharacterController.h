// author: chris-scientist
// created at: 26/08/2018
// updated at: 08/08/2018

#ifndef CHARACTERCONTROLLER
#define CHARACTERCONTROLLER

#include <Gamebuino-Meta.h>

#include "CharacterModel.h"
#include "MapModel.h"
#include "TypeOfSprites.h"
#include "MapModel.h"

class CharacterController {
  private:
    bool stopMove;
    CharacterModel *character;
    MapModel *mapModel;
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    const char moveBox(const char aReplacedSprites, const int aX1, const int aY1, const int aX2, const int aY2);
    char getPlayerSprites(const char aReplacedSprites) const;
    const bool isWall(const char aReplacedSprites) const;
    const bool isBox(const char aReplacedSprites) const;
  public:
    CharacterController(CharacterModel * aCharacter, MapModel *aMapModel);
    void run();
    const int getX() const;
    const int getY() const;
};

#endif

