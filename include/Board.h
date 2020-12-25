#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "LTexture.h"
#include "Character.h"
#include "Antagonist.h"
#include "Projectile.h"
using namespace std;

class Board{
  public:
    Board(int sHeight, int sWidth, string textureFile);
    void make_board(string path);
    void render_board();
    void move_entities(vector<SDL_Rect*> walls);
    void render_entities();
    void dan_handle(SDL_Event* e);

  protected:
    int spaceHeight, spaceWidth, num_enemies;
    vector<string > board;
    LTexture* texture_plate;
    vector<SDL_Rect> squares;
    Character* protag;
    vector<Antagonist*> enemies;
};
