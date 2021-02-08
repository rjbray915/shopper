#include "../include/Projectile.h"
#include "../include/Character.h"
#include "../include/LTexture.h"
#include <vector>
#include <cmath>
using namespace std;

Projectile::Projectile(double pDamage, Character* started, Character* target, int pProjVel, int pTravelDist, double pAngle, SDL_RendererFlip pFlip, int pNumClips, int pClipWidth, int pClipHeight, string imgPath){
	int subX, subY;

	this->started = started;
	this->target = target;

	x = started->getXPos();
	y = started->getYPos();

	damage = pDamage;
	timer = 0;
	projVel = pProjVel;
	xVel = 0;
	yVel = 0;
	travelDist = pTravelDist;
	distanceTrav = 0;
	angle = pAngle;
	flip = pFlip;
	numClips = pNumClips;

	//make the collider
	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = pClipWidth;
	mCollider.h = pClipHeight;

	//initialize the velocity
	updateVel();

	//get the texture
	if( !projTexture.loadFromFile(imgPath.c_str() ) ){
		printf("could not load projectile texture\n");
	}

	for(int i = 0; i < numClips; i++){
		//add i b/c im a dumbass and each sprite is 1 pixel apart
		spriteClips.push_back( SDL_Rect{ pClipWidth*i + i, 0, pClipWidth, pClipHeight } );
	}
}

Projectile::~Projectile(){
	//free up our texture
	projTexture.free();
}

void Projectile::updateVel(){
	double subX, subY, subDist, fractX, fractY;
	SDL_Rect* targetCollider;

	//aim for target's x
	targetCollider = target->getCollider();
	subX = target->getXPos() + targetCollider->w / 2 - started->getXPos();
	subY = target->getYPos() + targetCollider->h / 2 - started->getYPos();


	//need to calculate the relative distances in x & y to calculate how much
	//it should travel in both directions
	subDist = sqrt(subX*subX + subY*subY);
	fractX = abs(subX) / subDist;
	fractY = abs(subY) / subDist;

	//x
	if(subX > 0)
		xVel = fractX * projVel;
	else if(subX < 0)
		xVel = 0-fractX * projVel;
	else
		xVel = 0;
	//y
	if(subY > 0)
		yVel = fractY * projVel;
	else if(subY < 0)
		yVel = 0-fractY * projVel;
	else
		yVel = 0;

}

//the last element in walls is always the boundary for the game window
void Projectile::move( std::vector<SDL_Rect*>* walls ){
	bool colliding = false;
	bool hitTarget = false;

	//this is a temporary solution to timing without using frames.
	//THIS NEEDS TO BE UPDATED WHEN I LEARN GAME TIMING.
	if(timer != 0){
		if(timer >= 100){
			timer = 0;

			//put it back at the start and
			x = started->getXPos();
			y = started->getYPos();
			mCollider.x = x;
			mCollider.y = y;
			xVel = 0;
			yVel = 0;
			distanceTrav = 0;
			updateVel();
		}
		else{
			timer++;
			return;
		}

	}

	//note: we do it this way so that first of all it doesn't render and make
	//it look buggy. also, it can't move into the box and stay there
	//move x
	x += xVel;
	mCollider.x = x;

	//move y
	y += yVel;
	mCollider.y = y;

	//add to the distance traveled
	distanceTrav += sqrt(xVel*xVel + yVel*yVel);

	//check if we are colliding with any objects
	for( int i = 0; i < walls->size() - 1; i++){
		if( checkCollision( walls->at( i ), &mCollider ) ){
			colliding = true;
			break;
		}
	}

	//check if we collided with the target
	if( checkCollision(target->getCollider(), &mCollider)){
		hitTarget = true;
	}

	//check if going out of bounds
	if( checkBounds( walls->at(walls->size()-1) ) ){
		colliding = true;
	}

	//check to deal damage
	if(hitTarget){
		target->take_hit(damage);
	}
	//check for despawn
	if( colliding || hitTarget || distanceTrav >= travelDist ){
		timer = 1;
	}

}

//check if the projectile is within the game window
bool Projectile::checkBounds( SDL_Rect* border ){
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

bool Projectile::checkCollision( SDL_Rect* a, SDL_Rect* b ){
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

void Projectile::render(){
	if(timer != 0) return;
	//change our sprite clip for animation
	//movingAnimation();

	projTexture.render( x, y, /*&spriteClips[ currClip ]*/NULL, angle, NULL, flip );
}

void Projectile::movingAnimation(){
	static int tracker = 0;

	if( xVel != 0 || yVel != 0 ){
		if( tracker % 12 == 0 ){
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

SDL_Rect* Projectile::getCollider(){
	return &mCollider;
}

int Projectile::getXPos(){
	return x;
}

int Projectile::getYPos(){
	return y;
}
