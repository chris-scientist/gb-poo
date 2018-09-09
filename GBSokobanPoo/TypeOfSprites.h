// author: chris-scientist
// created at: 08/08/2018
// updated at: 09/08/2018
// description: type des cases

#ifndef TYPEOFSPRITES
#define TYPEOFSPRITES

#include <Gamebuino-Meta.h>

class TypeOfSprites {
  private:
  public:
    static const char WALL_TYPE = '#';
    static const char BOX_TYPE = '$';
    static const char DESTINATION_TYPE = '.';
    static const char BOX_ON_ZONE_TYPE = '*';
    static const char PLAYER_TYPE = '@';
    static const char PLAYER_ON_ZONE_TYPE = '+';
    static const char FLOOR_TYPE = ' ';
};

#endif

