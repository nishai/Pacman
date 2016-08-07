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
    int frame = 0;
    World myWorld("maze1.txt", 20, 20);
    Character pac(100, 180, Pacman);

    while(!quit){
        // Handle any SDL Events
        // Such as resize, clicking the close button,
        //  and process and key press events.m
        SDL_Event e;

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            myWorld.pacman.handle_event(e);
        }

        myWorld.UpdateWorld();

        SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 0x00);
        SDL_RenderClear(myTexture.myWin.sdlRenderer);
        myWorld.render(&myTexture, frame);
        SDL_RenderPresent(myTexture.myWin.sdlRenderer);

        frame++;
        this_thread::sleep_for(chrono::milliseconds(75));
    }

    return 0;
}
