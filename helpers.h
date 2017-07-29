#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include "tile.h"

Tile makeTile(int x, int y, TileType t, Direction dir = Up);
std::vector<Tile> getTestTiles();

bool collision(SDL_Rect a, SDL_Rect b, int a_off = 0, int b_off = 0);

void DFS(std::vector<std::vector<Tile>> maze, std::pair<int, int> currentPos);
void BFS(std::vector<std::vector<Tile>> maze, std::pair<int, int> currentPos);

#endif // SDL_HELPERS_H
