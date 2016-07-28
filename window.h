#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window
{
public:
    Window();
    Window(int _width, int _height);
    ~Window();

    int getWidth() const;
    int getHeight() const;

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
protected:
    int width, height;
    static int counter;
    void free();
};

#endif // WINDOW_H
