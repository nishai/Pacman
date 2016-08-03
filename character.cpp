#include "character.h"
#include "tile.h"
#include "helpers.h"

/**
 * @brief Character::Character
 * @param myX X window co-ordinate.
 * @param myY Y window co-ordinate.
 * @param t Type of character.
 */
Character::Character(int myX, int myY, TileType t)
    : uTile(/* ??? */), dTile(/* ??? */), lTile(/* ??? */), rTile(/* ??? */)
{
    // The tiles above have to be constructed with the class above.
    // Why can't we rather just set their value in here using uTile = makeTile(...)?
}

/**
 * @brief Character::render Call the relevant tiles render function based on current direction.
 * @param t Texture object for rendering.
 * @param frame Frame number to render.
 */
void Character::render(Texture *t, int frame)
{

}
/**
 * @brief Character::getNextPosition Calculates the position of the character based on direction.
 * @return SDL_Rect of the position and dimensions (in pixels) of the character.
 */
SDL_Rect Character::getNextPosition()
{

}
/**
 * @brief Character::handle_event Handles the SDL Events for Arrow Keypresses
 * @param e SDL_Event to check.
 */
void Character::handle_event(const SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:    dir = Up; break;
            case SDLK_DOWN:  dir = Down; break;
            case SDLK_LEFT:  dir = Left; break;
            case SDLK_RIGHT: dir = Right; break;
        }
    }
}
