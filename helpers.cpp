#include "helpers.h"
#include "tile.h"
#include <iostream>

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
    switch(t){
        case Wall:
            return Tile(x, y, {{7,16}},t,1,1);
        case Food:
            return Tile(x, y, {{10,1}},t,1,1);
        case Pacman:
            switch(dir){
                case Up:
                    return Tile(x, y, {{3,1},{3,2},{3,1},{3,3}},t,1,1);
                case Left:
                    return Tile(x, y, {{1,1},{1,2},{1,1},{1,3}},t,1,1);
                case Down:
                    return Tile(x, y, {{4,1},{4,2},{4,1},{4,3}},t,1,1);
                case Right:
                default:
                    return Tile(x, y, {{2,1},{2,2},{2,1},{2,3}},t,1,1);
            }
        case MrsPacman:
            switch(dir){
                case Up:
                    return Tile(x, y, {{3,5},{3,6},{3,5},{3,7}},t,1,1);
                case Left:
                    return Tile(x, y, {{1,5},{1,6},{1,5},{1,7}},t,1,1);
                case Down:
                    return Tile(x, y, {{4,5},{4,6},{4,5},{4,7}},t,1,1);
                case Right:
                default:
                    return Tile(x, y, {{2,5},{2,6},{2,5},{2,7}},t,1,1);
            }
        case GhostR:
            switch(dir){
                case Up:
                    return Tile(x, y, {{5,1},{5,2}},t,1,1);
                case Left:
                    return Tile(x, y, {{5,5},{5,6}},t,1,1);
                case Down:
                    return Tile(x, y, {{5,3},{5,4}},t,1,1);
                case Right:
                default:
                    return Tile(x, y, {{5,7},{5,8}},t,1,1);
            }
        case GhostP:
            switch(dir){
                case Up:
                    return Tile(x, y, {{6,1},{6,2}},t,1,1);
                case Left:
                    return Tile(x, y, {{6,5},{6,6}},t,1,1);
                case Down:
                    return Tile(x, y, {{6,3},{6,4}},t,1,1);
                case Right:
                default:
                    return Tile(x, y, {{6,7},{6,8}},t,1,1);
            }
        case GhostB:
            switch(dir){
                case Up:
                    return Tile(x, y, {{7,1},{7,2}},t,1,1);
                case Left:
                    return Tile(x, y, {{7,5},{7,6}},t,1,1);
                case Down:
                    return Tile(x, y, {{7,3},{7,4}},t,1,1);
                case Right:
                default:
                    return Tile(x, y, {{7,7},{7,8}},t,1,1);
            }
        case GhostY:
            switch(dir){
                case Up:
                    return Tile(x, y, {{8,1},{8,2}},t,1,1);
                case Left:
                    return Tile(x, y, {{8,5},{8,6}},t,1,1);
                case Down:
                    return Tile(x, y, {{8,3},{8,4}},t,1,1);
                case Right:
                default:
                    return Tile(x, y, {{8,7},{8,8}},t,1,1);
            }
        case Blank:
        default:
            return Tile(x, y, {{1,4}},t , 1, 1);
   }

}

bool collision(SDL_Rect a, SDL_Rect b, int a_off, int b_off) // a: pacman next      b: maze
{
    // If A finishs above B - No Collision
    // If A starts below B - No Collision
    // If the right of A is left of B - No Collision
    // If the left of A is right of B - No Collision
    // If we get here there must be an overlap - Collision

    if ((a.y - a_off)  < (b.y - b.h + b_off)){ //correct
        return false;
    }
    if ((a.y + a_off) > (b.y + b.h - b_off)){ //correct
        return false;
    }
    if ((a.x + a.h + a_off) < (b.x - b_off - b_off - b_off)){
        return false;
    }
    if ((a.x + a_off) > (b.x + b.w - b_off)){ //correct
        return false;
    }
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
