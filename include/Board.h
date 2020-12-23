#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "LTexture.h"
using namespace std;

class Board{
  public:
    Board(int sHeight, int sWidth, string textureFile);
    void make_board(string path);
    void render_board();

  protected:
    int spaceHeight, spaceWidth;
    vector<string > board;
    LTexture* texture_plate;
    vector<SDL_Rect> squares;
};
