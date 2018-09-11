// author: chris-scientist
// created at: 17/08/2018
// updated at: 22/08/2018
// description: permet de gérer les images des sprites

#ifndef SPRITESMANAGER
#define SPRITESMANAGER

#include <Gamebuino-Meta.h>

class SpritesManager {
  private:
    static bool areaInitialized;
    static Image area;
    static bool boxInitialized;
    static Image box;
    static bool boxOnAreaInitialized;
    static Image boxOnArea;
    static bool characterInitialized;
    static Image character;
    static bool characterOnAreaInitialized;
    static Image characterOnArea;
    static bool floorInitialized;
    static Image floorImg;
    static bool wallInitialized;
    static Image wall;
  public:
    static const uint16_t WIDTH_SPRITES;
    static const uint16_t HEIGHT_SPRITES;
    
    static Image& getArea();
    static Image& getBox();
    static Image& getBoxOnArea();
    static Image& getCharacter();
    static Image& getCharacterOnArea();
    static Image& getFloorImg();
    static Image& getWall();
};

#endif
