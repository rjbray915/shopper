#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

class LTexture{
  public:
    LTexture();
    ~LTexture();

    //loading file
    bool loadFromFile( std::string path );

    //our render function
    void render( int x, int y,
            SDL_Rect* clip = NULL,
            double angle = 0,
            SDL_Point* center = NULL,
            SDL_RendererFlip flippage = SDL_FLIP_NONE );

    //for setting the base color
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //blending
    void setBlending( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );

    //getters
    int getWidth();
    int getHeight();

    //to free up the memory
    void free();

  private:
    int mWidth, mHeight;

    SDL_Texture* mTexture;
};
