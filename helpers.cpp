#include "helpers.h"
#include "tile.h"

using namespace std;

/**
 * @brief makeTile Creates a Tile based on the TileType
 *
 * Remember that the different TileTypes are:
 *      Wall        {{7,16}}
 *      Food        {{10,1}}
 *      Blank       {{1,4}}
 *      Pacman
 *          Up      {{3,1},{3,2},{3,1},{3,3}}
 *          Down    {{4,1},{4,2},{4,1},{4,3}}
 *          Left    {{1,1},{1,2},{1,1},{1,3}}
 *          Right   {{2,1},{2,2},{2,1},{2,3}}
 *      MrsPacman
 *          Up      {{3,5},{3,6},{3,5},{3,7}}
 *          Down    {{4,5},{4,6},{4,5},{4,7}}
 *          Left    {{1,5},{1,6},{1,5},{1,7}}
 *          Right   {{2,5},{2,6},{2,5},{2,7}}
 *      GhostR
 *          Up      {{5,1},{5,2}}
 *          Down    {{5,3},{5,4}}
 *          Left    {{5,5},{5,6}}
 *          Right   {{5,7},{5,8}}
 *      GhostP, GhostY, GhostB
 *
 * @param x X Window co-ordinate in pixels.
 * @param y Y Window co-ordinate in pixels.
 * @param t Type of the Tile to construct.
 * @param dir Direction of the Tile (Up/Down/Left/Right)
 * @return The new Tile created using the parameters.
 */
Tile makeTile(int x, int y, TileType t, Direction dir)
{
//  Hint:
//    switch(t){
//    case Wall:
//        return Tile(x, y, {{7,16}},t,1,1);
//    case Food:
//        ...
//    }

}

bool collision(SDL_Rect a, SDL_Rect b, int a_off, int b_off)
{
    // If A finishs above B - No Collision

    // If A starts below B - No Collision

    // If the right of A is left of B - No Collision

    // If the left of A is right of B - No Collision


    // If we get here there must be an overlap - Collision
    return true;
}


vector<Tile> getTestTiles()
{
    vector<Tile> testTiles;
    testTiles.push_back(makeTile(0 ,0,Pacman, Up));
    testTiles.push_back(makeTile(20,0,Pacman, Down));
    testTiles.push_back(makeTile(40,0,Pacman, Left));
    testTiles.push_back(makeTile(60,0,Pacman, Right));

    testTiles.push_back(makeTile(0 ,20,MrsPacman, Up));
    testTiles.push_back(makeTile(20,20,MrsPacman, Down));
    testTiles.push_back(makeTile(40,20,MrsPacman, Left));
    testTiles.push_back(makeTile(60,20,MrsPacman, Right));

    testTiles.push_back(makeTile(0 ,40,Wall));
    testTiles.push_back(makeTile(20,40,Blank));
    testTiles.push_back(makeTile(40,40,Food));

    int lastY = 40;
    for(TileType t : {GhostR, GhostY, GhostP, GhostB}){
        lastY += 20;
        testTiles.push_back(makeTile(0 ,lastY,t, Up));
        testTiles.push_back(makeTile(20,lastY,t, Down));
        testTiles.push_back(makeTile(40,lastY,t, Left));
        testTiles.push_back(makeTile(60,lastY,t, Right));
    }
    return testTiles;
}
