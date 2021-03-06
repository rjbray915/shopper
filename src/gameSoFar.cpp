#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  CLASSES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "../include/LTexture.h"
#include "../include/Character.h"
#include "../include/Antagonist.h"
#include "../include/Projectile.h"
#include "../include/Board.h"
//#include "../include/Protagonist.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  SDL PROTOTYPES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//start our stuff up
bool init();

//loads images and stuff
bool loadMedia();

//quit everything
void close();



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  GLOBALS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main( int argc, char* argv[] ){
	srand( time(NULL) );

  if( init() ){
    if( loadMedia() ){
      //background textures
			Board board(50, 50, "images/boardTextures.png");
			board.make_board("boards/main.txt");
      LTexture grocery;
      grocery.loadFromFile( "images/groceryBack.jpg" );

			//quit flag
      bool quit = false;

      //our event
      SDL_Event e;

      //gamer loop
      while( !quit ){

        //poll for events
        while( SDL_PollEvent( &e ) ){
          if( e.type == SDL_QUIT ){
            quit = true;
          }

          //dan->handleEvent( &e );
					board.dan_handle(&e);
        }

        //our rendering stuff
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //rendering and movement
				board.render_board();
				board.move_entities( &(board.walls) );
				board.render_entities();

        SDL_RenderPresent( gRenderer );

      } //end gamer loop

    }//load
  }//init

  close();
  return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  SDL DEFINITIONS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//start our stuff up
bool init(){
  bool success = true;

  //start sdl
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
    printf( "problem initializing SDL Error:%s\n", SDL_GetError() );
    success = false;
  }
  else{
    //make window
    gWindow = SDL_CreateWindow( "quarantine shopper",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN );
    if( gWindow == NULL ){
      printf( "problem making window Error:%s\n", SDL_GetError() );
      success = false;
    }
    else{
      //start renderer
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if( gRenderer == NULL ){
        printf( "problem making renderer Error:%s\n", SDL_GetError() );
        success = false;
      }
      else{
        //initialize image loading
        int img_flags = IMG_INIT_PNG;
        if( !( IMG_Init( img_flags ) & img_flags ) ){
          printf( "problem starting image loading Error:%s\n", IMG_GetError() );
          success = false;
        }
      }
    }
  }

  return success;
}//end init

//loads images and stuff
bool loadMedia(){
  //does nothing rn
  return true;
}

//quit everything
void close(){


  //get rid of window
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;

  //get rid of renderer
  SDL_DestroyRenderer( gRenderer );
  gRenderer = NULL;

  SDL_Quit();
  IMG_Quit();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  LTexture definitions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  collision functions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
