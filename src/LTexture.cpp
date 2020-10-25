#include "../include/LTexture.h"

LTexture::LTexture(){
  mWidth = 0;
  mHeight = 0;

  mTexture = NULL;
}

LTexture::~LTexture(){
  free();
}

//loading file
bool LTexture::loadFromFile( std::string path ){
  bool success = true;

  //get our surface first
  SDL_Surface* tempSurface = IMG_Load( path.c_str() );
  if( tempSurface == NULL ){
    printf( "problem loading tempSurface Error: %s\n", IMG_GetError() );
    success = false;
  }
  else{
    //chroma keying
    SDL_SetColorKey( tempSurface, SDL_TRUE, SDL_MapRGB( tempSurface->format, 0x00, 0xFF, 0xFF) );

    mTexture = SDL_CreateTextureFromSurface( gRenderer, tempSurface );
    if( mTexture == NULL ){
      printf( "problem creating texture from surface Error: %s\n", SDL_GetError() );
      success = false;
    }

    mWidth = tempSurface->w;
    mHeight = tempSurface->h;
  }// end texture

  //now free our temp surface
  SDL_FreeSurface( tempSurface );

  return success;
}

//our render function
void LTexture::render( int x, int y,
        SDL_Rect* clip,
        double angle,
        SDL_Point* center,
        SDL_RendererFlip flippage ){
  //our destination for rendering
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  //check in case we are rendering to whole screen
  if( clip != NULL ){
    renderQuad.x = x;
    renderQuad.y = y;
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //use our rendering function that supports the functionality
  SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flippage );
}

//for setting the base color
void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
  SDL_SetTextureColorMod( mTexture, red, green, blue );
}

//blending
void LTexture::setBlending( SDL_BlendMode blending ){
  SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha ){
  SDL_SetTextureAlphaMod( mTexture, alpha );
}

//getters
int LTexture::getWidth(){
  return mWidth;
}
int LTexture::getHeight(){
  return mHeight;
}

//to free up the memory
void LTexture::free(){
  SDL_DestroyTexture( mTexture );
}
