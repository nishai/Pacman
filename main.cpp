#include <iostream>
#include <thread>
#include <chrono>

#include "window.h"
#include "texture.h"
#include "tile.h"
#include "helpers.h"
#include "character.h"

using namespace std;

int main()
{
    // SpriteSheet Filename
    string spriteFilename = SPRITEFILENAME; // Leave this line

    Texture myTexture;
    myTexture.loadFile(spriteFilename, 20, 20);
    bool quit = false;
    int frame = 0;
    Character Pac(0,0,Pacman);
    while(!quit){
        // Handle any SDL Events
        // Such as resize, clicking the close button,
        //  and process and key press events.m
        SDL_Event e;
        Pac.handle_event(e);

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }

        Tile pm(0,0,{ {1,1}, {1,2}, {1,1}, {1,3}},Pacman,1,1);
        SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(myTexture.myWin.sdlRenderer);
        //pm.render(&myTexture, frame);
        Pac.render(&myTexture, frame);
        SDL_RenderPresent(myTexture.myWin.sdlRenderer);

        frame++;
        this_thread::sleep_for(chrono::milliseconds(75));
    }

    return 0;
}
