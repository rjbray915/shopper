
#include "../include/Character.h"
#include <vector>
using namespace std;

Character::Character(double pMaxHitPoints, double pX, double pY,
											double pCharVel, double pAngle,
											SDL_RendererFlip pFlip, int pNumClips,
											int pClipWidth, int pClipHeight,
											string imgPath, vector<string>* pBoard){
	maxHitPoints = pMaxHitPoints;
	curHitPoints = maxHitPoints;
	x = pX;
	y = pY;
	xVel = 0;
	yVel = 0;
	charVel = pCharVel;
	angle = pAngle;
	flip = pFlip;
	numClips = pNumClips;

	//init collider
	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = pClipWidth;
	mCollider.h = pClipHeight;

	//our board
	board = pBoard;

	if( !charTexture.loadFromFile(imgPath.c_str() ) ){
		printf("couldn't load character texture\n");
	}

	for(int i = 0; i < numClips; i++){
		spriteClips.push_back( SDL_Rect{ pClipWidth*i, 0, pClipWidth, pClipHeight } );
	}
}

Character::~Character(){
	//free up our texture
	charTexture.free();
}

void Character::handleEvent( SDL_Event* e ){
	//key was pressed down
	if( e->type == SDL_KEYDOWN && e->key.repeat == 0 ){
		switch( e->key.keysym.sym ){
			case SDLK_UP:
				yVel -= charVel;
				break;

			case SDLK_DOWN:
				yVel += charVel;
				break;

			case SDLK_LEFT:
				xVel -= charVel;
				break;

			case SDLK_RIGHT:
				xVel += charVel;
				break;
		}
	}
	//if key was released
	else if( e->type == SDL_KEYUP && e->key.repeat == 0 ){
		switch( e->key.keysym.sym ){
			case SDLK_UP:
				yVel += charVel;
				break;

			case SDLK_DOWN:
				yVel -= charVel;
				break;

			case SDLK_LEFT:
				xVel += charVel;
				break;

			case SDLK_RIGHT:
				xVel -= charVel;
				break;
		}
	}
}

//the last element in walls is always the boundary for the game window
void Character::move( std::vector<SDL_Rect*>* walls ){
	bool colliding = false;

	//note: we do it this way so that first of all it doesn't render and make
	//it look buggy. also, it can't move into the box and stay there
	//move x
	x += xVel;
	mCollider.x = x;

	//move y
	y += yVel;
	mCollider.y = y;

	//check if we are colliding with anything
	for( int i = 0; i < walls->size() - 1; i++){
		if( checkCollision( walls->at( i ), &mCollider ) ){
			colliding = true;
			break;
		}
	}

	//check if going out of bounds
	if( checkBounds( walls->at(walls->size()-1) ) ){
		colliding = true;
	}

	if( colliding ){
		//move back
		x -= xVel;
		mCollider.x = x;
	}

	if( colliding ){
		//move back
		y -= yVel;
		mCollider.y = y;
	}
}

bool Character::checkBounds( SDL_Rect* border ){
	//left side
	if( mCollider.x < border->x ){
		return true;
	}
	else if( mCollider.y < border->y ){
		return true;
	}
	else if( mCollider.x + mCollider.w > border->x + border->w){
		return true;
	}
	else if( mCollider.y + mCollider.h > border->y + border->h){
		return true;
	}

	return false;
}

bool Character::checkCollision( SDL_Rect* a, SDL_Rect* b ){
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

void Character::render(){
  //change our sprite clip for animation
  movingAnimation();

  charTexture.render( x, y, &spriteClips[ currClip ], angle, NULL, flip );
}

void Character::movingAnimation(){
  static int tracker = 0;

  if( xVel != 0 || yVel != 0 ){
    if( tracker % spriteClips.size() * 2 == 0 ){
      currClip++;

      if( currClip >= numClips ){
        currClip = 0;
      }
    }

    tracker++;
  }
  else{
    currClip = 0;
  }
}

void Character::take_hit(double dmg){
	if(curHitPoints - dmg < 0)
		curHitPoints = 0;
	else
		curHitPoints -= dmg;

	//temp
	printf("HP: %f\n", curHitPoints);
}

SDL_Rect* Character::getCollider(){
	return &mCollider;
}

int Character::getXPos(){
	return x;
}

int Character::getYPos(){
	return y;
}
