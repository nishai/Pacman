#ifndef WORLD_H
#define WORLD_H

/** \file world.h
 * \brief World class header file.
 */

#include "tile.h"
#include "character.h"

/** \brief Represents the entire state of the game.
 *
 * The class stores the maze, pacman, ghosts and is responsible for
 * calling the relevant \ref{render} functions on each object.
 */
class World
{
public:
    int cols;                       ///< Number of columns in the maze (measured in tiles).
    int rows;                       ///< Number of rows in the maze (measured in tiles).
    int food;                       ///< The number of food pellets left in the maze.
    int points;                     ///< The number of food pellets eaten so far.

    bool ready;                     ///< Whether or not the game should continue running for another step.
    /** True: the game can advance another step. False: the game is finished.*/

    Character pacman;               ///< Character object representing pacman.
    Character red;
    Character blue;
    Character pink;
    Character yellow;

    std::vector<std::vector<Tile>> maze; ///< Stores maze Tile objects, used to store the background tile states.

    World(std::string filename, int tileWidth, int tileHeight);    ///< Constructor.

    void render(Texture *t, int frame = 0);     ///< Blit all tiles & characters to the ::sdlRenderer.

    bool UpdateWorld();                    ///< Advance the world 1 timestep.
};

#endif // WORLD_H
