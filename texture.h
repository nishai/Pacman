#ifndef TEXTURE_H
#define TEXTURE_H

/**
 * \file texture.h Header file for SDL Texture Wrapper
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"

#include <string>
/**
 * @brief The Texture class wraps around the SDL hardware textures.
 *
 * This class allows us to render portions of a larger sprite sheet
 * to specific co-ordinates on the screen.
 */

class Texture
{
public:    
    Texture();
    ~Texture();

    void loadFile(std::string filename, int tileWidth, int tileHeight);
    void free();
    virtual void render(int x, int y, SDL_Rect src);
    virtual void render(int x, int y, int ssRow, int ssCol, int w = 1, int h = 1);

    SDL_Rect getSpritePosition(int ssRow, int ssCol, int width = 1, int height = 1);

    int sheetWidth();
    int sheetHeight();
    int tileWidth();
    int tileHeight();

    void handle_event(SDL_Event &e, int rows, int cols);
    void scaleGraphics(int rows, int cols);

    Window myWin;
protected:
    SDL_Texture *myTexture; ///< Pointer to the SDL Hardware Texture
    int myWidth, myHeight;  ///< Width & Height of the Sprite Sheet
    int myTileWidth, myTileHeight; ///< Width & Height of each tile

};

#endif // TEXTURE_H
