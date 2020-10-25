#include "../include/Character.h"
#include "../include/Antagonist.h"
#include "../include/Projectile.h"
#include <cmath>

void Antagonist::initProjectile(Character* target){
	antProjectile = new Projectile(this, target, 4, 500, 0.0, SDL_FLIP_NONE, 1, 50, 50, "./images/projectile.png");
}

void Antagonist::setVelocity(int randNum){

	switch(randNum){
		//left
		case 0:
			xVel -= charVel;
			break;
		//right
		case 1:
			xVel += charVel;
			break;
		//up
		case 2:
			yVel -= charVel;
			break;
		//down
		case 3:
			yVel += charVel;
			break;
		//stop
		case 4:
			xVel = 0;
			yVel = 0;
			break;
		//default is stay the same 1/2 time
	};
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

	printf("subX: %f subY: %f subDist: %f\n", subX, subY, subDist);
	printf("fractX: %f fractY: %f\n", fractX, fractY);
  //printf("x: %d y: %d\n", targetCollider->x, targetCollider->y);
  //printf("w: %d h: %d\n", (targetCollider->w)/2, (targetCollider->h)/2);

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

  printf("xVel: %f yVel: %f\n", xVel, yVel);

/*	//vars
	int subX, subY;

	//subtract the followed positions from ours
	subX = followed->getXPos() - this->x;
	subY = followed->getYPos() - this->y;

	if(subX > 0){
		xVel = charVel;
	}
	else if(subX < 0){
		xVel = 0-charVel;
	}
	else{
		xVel = 0;
	}

	if(subY > 0){
		yVel = charVel;
	}
	else if(subY < 0){
		yVel = 0-charVel;
	}
	else{
		yVel = 0;
	}*/
}
