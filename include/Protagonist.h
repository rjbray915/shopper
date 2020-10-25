#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "LTexture.h"
#include "Character.h"
//urmomlol
class Protagonist: public Character{
  public:
    explicit Protagonist() : Character();

    //handle our movement keys
    void handleEvent( SDL_Event* e );

    //movement functions
    void move( std::vector<SDL_Rect*> walls );

    //our collision function
    bool checkCollision( SDL_Rect* a, SDL_Rect* b );

    //our rendering function
    void render();

    //for animating movement
    void movingAnimation();

  protected:
    const int PROTAG_WIDTH = 40;
    const int PROTAG_HEIGHT = 100;
    const int PROTAG_VEL = 5;

    //our sprite clips and stuff
    const static int TOTAL_PROTAG_CLIPS = 5;
    SDL_Rect protagSpriteClips[ TOTAL_PROTAG_CLIPS ];
    int currentClip;
};
