#include "../include/Protagonist.h"
#include "../include/Character.h"
#include "../include/LTexture.h"

Protagonist::Protagonist() : Character(){
  if( !charTexture.loadFromFile( "images/protagonist.png" ) ){
    //urmomlol
  }

  //initialize position
  /*x = SCREEN_WIDTH / 2;
  y = SCREEN_HEIGHT / 2;*/
  x = 485;
  y = 289;

  //initialize collision box
  mCollider.x = x;
  mCollider.y = y;
  mCollider.w = PROTAG_WIDTH;
  mCollider.h = PROTAG_HEIGHT;

  //initialize sprite clips
  currentClip = 0;
  protagSpriteClips[ 0 ].x = 0;
  protagSpriteClips[ 0 ].y = 0;
  protagSpriteClips[ 0 ].w = PROTAG_WIDTH;
  protagSpriteClips[ 0 ].h = PROTAG_HEIGHT;

  protagSpriteClips[ 1 ].x = 41;
  protagSpriteClips[ 1 ].y = 0;
  protagSpriteClips[ 1 ].w = PROTAG_WIDTH;
  protagSpriteClips[ 1 ].h = PROTAG_HEIGHT;

  protagSpriteClips[ 2 ].x = 82;
  protagSpriteClips[ 2 ].y = 0;
  protagSpriteClips[ 2 ].w = PROTAG_WIDTH;
  protagSpriteClips[ 2 ].h = PROTAG_HEIGHT;

  protagSpriteClips[ 3 ].x = 123;
  protagSpriteClips[ 3 ].y = 0;
  protagSpriteClips[ 3 ].w = PROTAG_WIDTH;
  protagSpriteClips[ 3 ].h = PROTAG_HEIGHT;

  protagSpriteClips[ 4 ].x = 164;
  protagSpriteClips[ 4 ].y = 0;
  protagSpriteClips[ 4 ].w = PROTAG_WIDTH;
  protagSpriteClips[ 4 ].h = PROTAG_HEIGHT;
}



void Protagonist::move( std::vector<SDL_Rect*> walls ){
  bool colliding = false;

//note: we do it this way so that first of all it doesn't render and make
//it look buggy. also, it can't move into the box and stay there
  //move x
  x += xVel;
  mCollider.x = x;

  for( int i = 0; i < walls.size(); i++){
    if( checkCollision( walls.at( i ), &mCollider ) ){
      colliding = true;
      break;
    }
  }

  if( colliding ){
    //move back
    x -= xVel;
    mCollider.x = x;
  }

  //move y
  y += yVel;
  mCollider.y = y;

  if( colliding ){
    //move back
    y -= yVel;
    mCollider.y = y;
  }
}

bool Protagonist::checkCollision( SDL_Rect* a, SDL_Rect* b ){
  //use axis separation to find out. we need to calculate
  //all of the sides in order to do this
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int botA, botB;

  //calculate sides
  leftA = a->x;
  leftB = b->x;
  rightA = a->x + a->w;
  rightB = b->x + b->w;
  topA = a->y;
  topB = b->y;
  botA = a->y + a->h;
  botB = b->y + b->h;

  //check if sides are not colliding, return false
  if( leftA >= rightB ){
    return false;
  }

  if( leftB >= rightA ){
    return false;
  }

  if( topA >= botB ){
    return false;
  }

  if( topB >= botA ){
    return false;
  }

  //if it passes all those tests, we return true :)
  return true;
}

void Protagonist::render(){
  //change our sprite clip for animation
  movingAnimation();

  charTexture.render( x, y, &protagSpriteClips[ currentClip ], angle, NULL, flip );
}

void Protagonist::movingAnimation(){
  static int tracker = 0;

  if( xVel != 0 || yVel != 0 ){
    if( tracker % 12 == 0 ){
      currentClip++;

      if( currentClip >= TOTAL_PROTAG_CLIPS ){
        currentClip = 0;
      }
    }

    tracker++;
  }
  else{
    currentClip = 0;
  }
}
