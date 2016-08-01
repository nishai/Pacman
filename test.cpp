/*
    Don't look at this file, it'll make you sad.
    This just has the code that tests all the functions you write.
*/

#include "window.h"

#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

#include "tile.h"

class Tex2 : public Texture{
public:
    bool called = false;
    int called_x, called_y, called_sprite_row, called_sprite_col, called_sprite_width, called_sprite_height;
    virtual void render(int x, int y, int ssRow, int ssCol, int w, int h) override{
        called = true;
        called_x = x; called_y = y; called_sprite_row = ssRow; called_sprite_col = ssCol; called_sprite_width = w; called_sprite_height = h;
        //Texture::render(x, y, ssRow, ssCol, w, h);
    }
    SDL_Renderer *getSDLRenderer(){
        return myWin.sdlRenderer;
    }
};

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Testing the Tile Constructor."){
    for(int i = 0; i < 10; i++){
        // Generate Some Random Info
        int myX = rand() % 640, myY = rand() % 480;
        vector<pair<int, int>> myV;
        int n = (rand() % 5) + 1;
        stringstream ss;
        myV.push_back({rand() % 15, rand() % 15});
        for(int j = 1; j < n; j++){
            myV.push_back({rand() % 15, rand() % 15});
        }
        ss << "{";
        for(size_t i = 0; i < myV.size()-1; i++){
            auto& p = myV[i];
            ss << "{" << p.first << "," << p.second << "},";
        }
        auto& p = myV[myV.size()-1];
        ss << "{" << p.first << "," << p.second << "}";
        ss << "}";
        TileType myT = static_cast<TileType>(rand()%9);
        int myW = rand() % 3, myH = rand() % 3;

        // Create a tile with the random info
        Tile myTile(myX, myY, myV, myT, myW, myH);
        //INFO("Created myTile(" << myX << "," << myY << "," << myV << "," << myT << "," << myW << "," << myH << ")");
        INFO("Created Tile(" << myX << "," << myY << "," << ss.str() << "," << myT << "," << myW << "," << myH << ")");
        SECTION("Checking the co-ordinates in the window."){
            REQUIRE(myTile.x == myX);
            REQUIRE(myTile.y == myY);

            SECTION("Checking the type is saved correctly."){
                REQUIRE(myTile.myType == myT);

                SECTION("Checking the dimensions are saved correctly."){
                    REQUIRE(myTile.w == myW);
                    REQUIRE(myTile.h == myH);

                    SECTION("Checking the frames are saved correctly."){
                        REQUIRE(myTile.myFrames.size() == myV.size());
                        for(size_t j = 0; j < myV.size(); j++){
                            REQUIRE(myTile.myFrames[j].first == myV[j].first);
                            REQUIRE(myTile.myFrames[j].second == myV[j].second);
                        }

                        SECTION("Testing Renderer"){
                            //WARN("Render testing just checks that you're calling render with the correct arguments. Nothing will be displayed yet.");
                            Tex2 myTexture;
                            myTexture.loadFile(SPRITEFILENAME, 20, 20);
                            for(int f = 0; f < 20; f++){
                                INFO("  Rendering Frame " << f);
                                myTile.render(&myTexture, f);
                                if(myTexture.called != true){
                                    FAIL("You didn't call the row/col version of render.");
                                }
                                if(myTexture.called_x != myX){
                                    FAIL("Incorrect X co-ordinate: Expected " << myX << ", Received: " << myTexture.called_x);
                                }
                                if(myTexture.called_y != myY){
                                    FAIL("Incorrect Y co-ordinate: Expected " << myY << ", Received: " << myTexture.called_y);
                                }
                                if(myTexture.called_sprite_row != myV[f % myV.size()].first){
                                    FAIL("Incorrect sprite row: Expected " << myV[f % myV.size()].first << ", Received: " << myTexture.called_sprite_row);
                                }
                                if(myTexture.called_sprite_col != myV[f % myV.size()].second){
                                    FAIL("Incorrect sprite col: Expected " << myV[f % myV.size()].second << ", Received: " << myTexture.called_sprite_col);
                                }
                                //SECTION("Checking correct animation dimensions?"){
                                //REQUIRE(myTexture.called_sprite_width == myW);
                                if(myTexture.called_sprite_width != myW){
                                    FAIL("Incorrect sprite width: Expected " << myW << ", Received: " << myTexture.called_sprite_width);
                                }
                                //REQUIRE(myTexture.called_sprite_height == myH);
                                if(myTexture.called_sprite_height != myH){
                                    FAIL("Incorrect sprite height: Expected " << myH << ", Received: " << myTexture.called_sprite_height);
                                }
                                myTexture.called = false;
                            }
                        }
                    }
                }
            }
        }
    }
}
