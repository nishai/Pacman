#include "window.h"

#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

int Window::counter = 0;

Window::Window() : Window(640, 480)
{
    // Nothing else to do.
}

Window::Window(int _width, int _height) :  sdlWindow(nullptr), sdlRenderer(nullptr), width(_width), height(_height)
{
    if(counter > 0)
        throw runtime_error(string("This wrapper only handles one SDL Window at a time. "));
    counter++;

    // Initialise SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw runtime_error(string("Unable to initialise SDL:\n") + SDL_GetError());

    // Try set linear texture filtering - type of anti-aliasing
    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        cout << "Unable to initialise linear texture filtering." << endl;

    // Setup the SDL Window
    sdlWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 width, height , SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(!sdlWindow)
        throw runtime_error(string("Unable to create SDL Window:\n") + SDL_GetError());

    // Setup the SDL Renderer using Hardware acceleration and vsync
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if(!sdlRenderer){
        free();
        throw runtime_error(string("Unable to create SDL renderer:\n") + SDL_GetError());
    }
    // Set the clear renderer colour to White
    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0xFF, 0xFF);

    // Load SDL library for PNG files
    if( ! ( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ){
        free();
        throw runtime_error(string("Unable to initialise SDL_Image: ") + IMG_GetError());
    }
}

Window::~Window()
{
    free();

    IMG_Quit();
    SDL_Quit();
    counter--;
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}

void Window::free()
{
    if(sdlRenderer != nullptr){
        SDL_DestroyRenderer(sdlRenderer);
    }
    if(sdlWindow != nullptr){
        SDL_DestroyWindow(sdlWindow);
    }

}
