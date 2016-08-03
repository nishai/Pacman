#ifndef CHARACTER_H
#define CHARACTER_H

#include "tile.h"

class Character
{
public:
    Character(int myX, int myY, TileType t);

    void render(Texture *t, int frame = 0);
    void handle_event(const SDL_Event &e);

    SDL_Rect getNextPosition();

    int x, y;

    Direction dir = Up;
    Tile uTile;
    Tile dTile;
    Tile lTile;
    Tile rTile;
};

#endif // CHARACTER_H
