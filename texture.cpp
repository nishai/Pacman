#include "texture.h"
#include "stdexcept"

using namespace std;

/**
 * @brief Texture::Texture Default constructor.
 *
 * Initialises variables to sensible defaults.
 */
Texture::Texture()
{
    myTexture = NULL;
    myWidth = -1;
    myHeight = -1;
    myTileWidth = -1;
    myTileHeight = -1;
}

/**
 * @brief Texture::~Texture Destructor.
 *
 * Should free the underlying SDL texture if it exists.
 */
Texture::~Texture()
{
    
}

/**
 * @brief Texture::loadFile Load a sprite sheet from a PNG file.
 * @param filename Sprite sheet filename.
 * @param tileWidth The width of each tile in pixels.
 * @param tileHeight The height of each tile in pixels.
 */
void Texture::loadFile(std::string filename, int tileWidth, int tileHeight)
{
    // Make sure we don't leak memory
    free();

    // Load the image
    SDL_Surface* loadedSurface = IMG_Load( filename.c_str() );
    // Check that it loaded successfully
    if(loadedSurface == nullptr)
        throw runtime_error(std::string("Couldn't load sprite sheet: ") + IMG_GetError());

    // Key out the background of the image (Black = 0, 0, 0)
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) );

    // Create the SDL Texuture to effeciently access parts of the image
    myTexture = SDL_CreateTextureFromSurface(myWin.sdlRenderer, loadedSurface );
    if(myTexture == nullptr)
        throw runtime_error(std::string("Couldn't create sprite texture: ") + SDL_GetError());

    // Remember width and height
    myWidth  = loadedSurface->w;
    myHeight = loadedSurface->h;

    // Remember the tile width and height
    myTileWidth  = tileWidth;
    myTileHeight = tileHeight;

    // Now that we've created the texture, we can free the surface
    SDL_FreeSurface(loadedSurface);
}

/**
 * @brief Texture::free If the SDL texture exists, then free it.
 */
void Texture::free()
{
    // Check whether there is actually a texture to free
    if(myTexture != nullptr){
        // Destroy the SDL texture
        SDL_DestroyTexture(myTexture);

        // Reset all the variables.
        // You need to do this...
    }
}

/**
 * @brief Texture::render An area of the sprite sheet to the screen.
 * @param x Screen co-ordinate to render the sprite.
 * @param y Screen co-ordinate to render the sprite.
 * @param src Area of the sprite sheet that should be rendered.
 */
void Texture::render(int x, int y, SDL_Rect src)
{
    // Find the section of the texture to render
    // SDL_Rect dest = ??????

    // Blit the src rectangle to the renderer
    // Note that this copies the section of the texture
    //   to the renderer's buffer - it doesn't actually
    //   put it on the screen yet.
    // Call SDL_RenderCopy(?????)

}
/**
 * @brief Texture::render Render a sprite tile to the screen.
 * @param x Screen co-ordinate to render the sprite.
 * @param y Screen co-ordinate to render the sprite.
 * @param ssRow The sprite row in the sprite sheet grid
 * @param ssCol The sprite column in the sprite sheet grid
 * @param w The width of the sprite in tiles.
 * @param h The height of the sprite in tiles.
 */
void Texture::render(int x, int y, int ssRow, int ssCol, int w, int h)
{
    // Get the SDL_Rect source using getSpritePosition

    // Call the other version of render

}

/**
 * @brief Texture::getSpritePosition Calculate the exact co-ordinates of a sprite in the grid
 * @param ssRow Sprite Row
 * @param ssCol Sprite Column
 * @param width Width of the sprite measured in Tiles
 * @param height Height of the sprite measured in Tiles
 * @return An SDL_Rect that can be used by the render function to blit the sprit to the screen
 */
SDL_Rect Texture::getSpritePosition(int ssRow, int ssCol, int width, int height)
{

}

/**
 * @brief Texture::sheetWidth
 * @return Width of the sprite sheet in pixels
 */
int Texture::sheetWidth()
{
    return myWidth;
}

/**
 * @brief Texture::sheetHeight
 * @return Height of the sprite sheet in pixels
 */
int Texture::sheetHeight()
{   
    return myHeight;
}

/**
 * @brief Texture::tileWidth
 * @return Width of each sprite tile in pixels
 */
int Texture::tileWidth()
{
    return myTileWidth;
}

/**
 * @brief Texture::tileHeight
 * @return Height of each sprite tile in pixels
 */
int Texture::tileHeight()
{
    return myTileHeight;
}

/**
 * @brief Texture::handle_event Handles Window Resize Events
 * @param e SDL_Event object.
 * @param rows Number of rows in the world.
 * @param rows Number of columns in the world.
 */
void Texture::handle_event(SDL_Event &e, int rows, int cols)
{
    if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED){
        scaleGraphics(rows, cols);
    }
}

/**
 * @brief Texture::scaleGraphics Scales the SDL_Renderer
 * @param rows Number of rows in the world.
 * @param rows Number of columns in the world.
 */
void Texture::scaleGraphics(int rows, int cols)
{
    int win_width, win_height;
    SDL_GetWindowSize(myWin.sdlWindow, &win_width, &win_height);

    float scaleX = win_width/(cols*double(tileWidth()));
    float scaleY = win_height/(rows*double(tileHeight()));

    SDL_RenderSetScale(myWin.sdlRenderer, scaleX, scaleY );
}
