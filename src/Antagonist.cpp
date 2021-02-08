#include "../include/Character.h"
#include "../include/Antagonist.h"
#include "../include/Projectile.h"
#include <cmath>

void Antagonist::initProjectile(double damage, Character* target){
	antProjectile = new Projectile(damage, this, target, 6, 500, 0.0, SDL_FLIP_NONE, 1, 50, 50, "./images/projectile.png");
}

void Antagonist::setVelocity(int randNum){
	//this is bad :p
}

void Antagonist::followCharacter(Character* followed){
  double subX, subY, subDist, fractX, fractY;
  SDL_Rect* targetCollider;

  //aim for target's x
  targetCollider = followed->getCollider();
  subX = followed->getXPos() + targetCollider->w / 2 - x;
  subY = followed->getYPos() + targetCollider->h / 2 - y;

  //need to calculate the
  subDist = sqrt(subX*subX + subY*subY);
  fractX = abs(subX) / subDist;
  fractY = abs(subY) / subDist;

	//x direction
  if(subX > 0)
    xVel = fractX * charVel;
  else if(subX < 0)
    xVel = 0-fractX * charVel;
  else
    xVel = 0;
  //y
  if(subY > 0)
    yVel = fractY * charVel;
  else if(subY < 0)
    yVel = 0-fractY * charVel;
  else
    yVel = 0;
}

void Antagonist::set_target(Character* pTarget){
	target = pTarget;
}

//overloading the function so i can put characters in vector
void Antagonist::move( std::vector<SDL_Rect*>* walls ){
	double subX, subY, subDist, fractX, fractY;
  SDL_Rect* targetCollider;
	bool colliding = false;

  //aim for target's x
  targetCollider = target->getCollider();
  subX = target->getXPos() + targetCollider->w / 2 - x;
  subY = target->getYPos() + targetCollider->h / 2 - y;

  //need to calculate the
  subDist = sqrt(subX*subX + subY*subY);
  fractX = abs(subX) / subDist;
  fractY = abs(subY) / subDist;

	//x direction
  if(subX > 0)
    xVel = fractX * charVel;
  else if(subX < 0)
    xVel = 0-fractX * charVel;
  else
    xVel = 0;
  //y
  if(subY > 0)
    yVel = fractY * charVel;
  else if(subY < 0)
    yVel = 0-fractY * charVel;
  else
    yVel = 0;

	//then the actual movement code

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

	//finally, move the Projectile
	antProjectile->move(walls);
}

//this will make them follow an isle while their sight to the target is blocked
void walk_isle(){

}

void Antagonist::render(){
  //change our sprite clip for animation
  movingAnimation();

  charTexture.render( x, y, &spriteClips[ currClip ], angle, NULL, flip );

	//render projectile
	antProjectile->render();
}
