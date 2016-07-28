/*
    Don't look at this file, it'll make you sad.
    This just has the code that tests all the functions you write.
*/

#include "texture.h"

#include <string>
#include <thread>
#include <chrono>

#ifndef SPRITEFILENAME
#define SPRITEFILENAME "sprites.png"
#endif

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


using namespace std;

TEST_CASE_METHOD(Texture, "Testing the Texture Class."){
    SECTION("Testing that the default constructor"){
        REQUIRE(myTexture == nullptr);
        REQUIRE(myWidth == -1);
        REQUIRE(myHeight == -1);
        REQUIRE(myTileWidth == -1);
        REQUIRE(myTileHeight == -1);

        SECTION("Loading a file that doesn't exist should throw."){
            REQUIRE_THROWS(loadFile("/this/file/doesnt/exist.png", 1, 1));
        }

        SECTION("Testing against sprites.png"){
            REQUIRE_NOTHROW(loadFile(SPRITEFILENAME, 20, 10));
            REQUIRE(myWidth == 356);
            REQUIRE(myHeight == 316);
            REQUIRE(myTileWidth == 20);
            REQUIRE(myTileHeight == 10);
            REQUIRE(myTexture != nullptr);

            GIVEN("A correctly loaded texture"){
                THEN("Try to free it."){
                    free();

                    REQUIRE(myTexture == nullptr);
                    REQUIRE(myWidth == -1);
                    REQUIRE(myHeight == -1);
                    REQUIRE(myTileWidth == -1);
                    REQUIRE(myTileHeight == -1);
                }

                THEN("Test the Texture Accessor Methods and Render(int,int,SDL_Rect)."){
                    REQUIRE(myWidth == sheetWidth());
                    REQUIRE(myHeight == sheetHeight());
                    REQUIRE(myTileWidth == tileWidth());
                    REQUIRE(myTileHeight == tileHeight());
                    REQUIRE_NOTHROW(loadFile(SPRITEFILENAME, 20, 10));
                    REQUIRE(myWidth == sheetWidth());
                    REQUIRE(myHeight == sheetHeight());
                    REQUIRE(myTileWidth == tileWidth());
                    REQUIRE(myTileHeight == tileHeight());

                    WARN("Running render(0, 0, {0,0,sheetWidth(),sheetHeight()}) - This doesn't actually test anything but you should see the sprite sheet on the window.");

                    REQUIRE_NOTHROW(loadFile(SPRITEFILENAME, 20, 20));
                    SDL_RenderClear(myWin.sdlRenderer);
                    render(0,0,SDL_Rect{0,0,sheetWidth(),sheetHeight()});
                    SDL_RenderPresent(myWin.sdlRenderer);
                    SDL_Event e;

                    for(auto i = 0; i < 50;i++){
                        SDL_PollEvent(&e);
                        this_thread::sleep_for(chrono::milliseconds(100));
                    }

                    WARN("Running render(20,20*5, {20,20*5,20,20}) - This doesn't actually test anything but you should see the red ghost on the window.");
                    SDL_RenderClear(myWin.sdlRenderer);
                    render(20,20*5, SDL_Rect{20,20*5,20,20});
                    SDL_RenderPresent(myWin.sdlRenderer);
                    for(auto i = 0; i < 50;i++){
                        SDL_PollEvent(&e);
                        this_thread::sleep_for(chrono::milliseconds(100));
                    }
                    SECTION("Testing getSpritePosition & render(int,int,int,int,int,int)"){
                        REQUIRE_NOTHROW(loadFile(SPRITEFILENAME, 30, 20));
                        SDL_Rect a;
                        a = getSpritePosition(0,0);
                        REQUIRE(a.x == 0);
                        REQUIRE(a.y == 0);
                        REQUIRE(a.w == 30);
                        REQUIRE(a.h == 20);

                        a = getSpritePosition(1,1,1,1);
                        REQUIRE(a.x == 30);
                        REQUIRE(a.y == 20);
                        REQUIRE(a.w == 30);
                        REQUIRE(a.h == 20);

                        a = getSpritePosition(5,7,1,1);
                        REQUIRE(a.x == 210);
                        REQUIRE(a.y == 100);
                        REQUIRE(a.w == 30);
                        REQUIRE(a.h == 20);

                        a = getSpritePosition(1,15,2,2);
                        REQUIRE(a.x == 450);
                        REQUIRE(a.y == 20);
                        REQUIRE(a.w == 60);
                        REQUIRE(a.h == 40);

                        SECTION("Running render Version 2 - This doesn't actually test anything."){
                            REQUIRE_NOTHROW(loadFile(SPRITEFILENAME, 20, 20));
                            WARN("Running render(0,0,1,1,3,4) - This doesn't actually test anything but you should see all the different pacman images.");
                            SDL_RenderClear(myWin.sdlRenderer);
                            render(0,0,1,1,3,4);
                            SDL_RenderPresent(myWin.sdlRenderer);
                            SDL_Event e;

                            for(auto i = 0; i < 2;i++){
                                SDL_PollEvent(&e);
                                this_thread::sleep_for(chrono::milliseconds(1000));
                            }
                            WARN("Running render(20*c, 20*r, r,c, 1, 1) - This doesn't actually test anything but you should see the program cycling through sprites in a 10x10 window.");

                            for(int r = 0; r < 10; r++){
                                for(int c = 0; c < 10; c++){
                                    SDL_RenderClear(myWin.sdlRenderer);
                                    render(20*c, 20*r, r,c, 1, 1);
                                    SDL_RenderPresent(myWin.sdlRenderer);
                                    SDL_PollEvent(&e);
                                    this_thread::sleep_for(chrono::milliseconds(100));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
