#include "world.h"
#include "helpers.h"
#include "character.h"
#include "tile.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;
/**
 * Constructs the World object loading a maze from the supplied file.
 * It should initialise the \ref{map} array with the relevant tiles as well
 * as the pacman and ghost objects.
 *
 * @param filename - File from which the maze should be read.
 * @param tileWidth - Width of each tile
 * @param tileHeight - Height of each tile
 */
World::World(string filename, int tileWidth, int tileHeight)
    : food(0), points(0), ready(true), pacman(0,0,Pacman)
{
    ifstream f(filename);
    string line;

    if(!f.is_open())
        throw runtime_error("Couldn't open maze file " + filename);
    // Code to read in the file...
    f>>rows>>cols;
    Tile myTile(0, 0, {{}}, Blank, 1, 1);
   	TileType t;
    getline(f, line); //get rid of the blank line

    vector<Tile> empty;
    for (int i = 0; i < rows; i++){
        maze.push_back(empty);
    }

    for (int i = 0; i < rows; ++i)
    {
        getline(f, line);
    	for (int j = 0; j < cols; j++){
    		switch (line[j]){
    			case 'x': t = Wall; break;
    			case ' ': t = Blank; break;
    			case '.': {
                    t = Food;
                    food++;
                    break;
                }
    			case '0': {
                    t = Pacman;
                    pacman.x = j * tileWidth;
                    pacman.y = i * tileHeight;
                    break;
                }
    			case '1': t = GhostR; break;
    			case '2': t = GhostY; break;
    			case '3': t = GhostP; break;
    			case '4': t = GhostB; break;
                default: t = Wall; break;
    		}

    		myTile = makeTile(j*tileWidth, i*tileHeight, t, Up);
    		maze[i].push_back(myTile);				    
    	} 
    }
}

/**
 * Renders the World to the ::sdlRenderer buffer.
 * It calls the respective render functions on each tile first.
 * Following this, it calls the pacman and ghost objects to render
 * them above the background.
 * @param frame [optional] An optional frame number to pass to the objects to handle animation.
 */
void World::render(Texture *t, int frame)
{
	for (int i = 0; i < rows; i++){
	    for (int j = 0; j < cols; ++j)
        {
            if (maze[i][j].myType != Pacman){
    			maze[i][j].render(t, frame);
            }
	    }
        pacman.render(t, frame);
    }
}

/**
 * This function is responsible for advancing the game state.
 * Pacman and the ghosts should be moved (if possible). If pacman is
 * captured by a ghost pacman.dead should be set to true. If pacman eats
 * a food pellet the relevant totals should be updated.
 *
 * @return The same value as World::ready, indicating whether the game is finished.
 */
bool World::UpdateWorld()
{
    SDL_Rect next = pacman.getNextPosition();
    SDL_Rect block;
    bool col = false;
    bool eat = false;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; ++j)
        {
            switch (maze[i][j].myType){
                case Wall: {
                    block.x = maze[i][j].x;
                    block.y = maze[i][j].y;
                    block.w = maze[i][j].w * 20;
                    block.h = maze[i][j].h * 20;

                    if (collision(next, block, 2, 3)){
                        col = true;
                    }
                    break;
                }
                case Food:{
                    block.x = maze[i][j].x;
                    block.y = maze[i][j].y;
                    block.w = maze[i][j].w * 20;
                    block.h = maze[i][j].h * 20;

                    if (collision(next, block, 1, 1)){
                        eat = true;
                        maze[i][j] = makeTile(i * maze[i][j].tileWidth, i * maze[i][j].tileHeight, Blank, Up);
                        goto x;
                    }
                }
                default: break;
            }
        }
    }

    x:if  (col == false){
        pacman.x = next.x;
        pacman.y = next.y;
    }

    if (eat){
        points++;
        cout<<"Points: "<<points<<endl;
    }

    if (food == points){
        ready = false;
    }

    return ready;
}
