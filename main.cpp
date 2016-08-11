#include <iostream>
#include <thread>
#include <chrono>

#include "window.h"
#include "texture.h"
#include "tile.h"
#include "helpers.h"
#include "character.h"
#include "world.h"

using namespace std;

int main()
{
    // SpriteSheet Filename
    string spriteFilename = SPRITEFILENAME; // Leave this line

    Texture myTexture;
    myTexture.loadFile(spriteFilename, 20, 20);
    bool quit = false;
    bool gameOver = false;
    int frame = 0;
    World myWorld("maze1.txt", 20, 20);
    int midRow = myWorld.rows / 2;
    int midCol = (myWorld.cols / 2) - 2;
    myTexture.scaleGraphics(myWorld.rows, myWorld.cols);

    while(!quit){
        // Handle any SDL Events
        // Such as resize, clicking the close button,
        //  and process and key press events.m
        SDL_Event e;

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            myTexture.handle_event(e, myWorld.rows, myWorld.cols);
            myWorld.pacman.handle_event(e);
        }

        gameOver = !myWorld.UpdateWorld();

        SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 0x00);
        SDL_RenderClear(myTexture.myWin.sdlRenderer);
        myWorld.render(&myTexture, frame);
        if (gameOver){
            myTexture.render(midCol*20, midRow * 20 , 8, 12, 5, 1);
        }
        SDL_RenderPresent(myTexture.myWin.sdlRenderer);

        frame++;
        this_thread::sleep_for(chrono::milliseconds(75));
    }
    return 0;
}
