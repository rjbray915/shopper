#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>
#include "LTexture.h"
#include "Character.h"
using namespace std;

class Projectile{
  public:
    //construct/destruct
    Projectile(double pDamage, Character* started, Character* target, int pProjVel, int pTravelDist, double pAngle, SDL_RendererFlip pFlip, int pNumClips, int pClipWidth, int pClipHeight, string imgPath);
    ~Projectile();

		//this is for changing velocity based on where the player is
		void updateVel();

    //movement functions. characters will move at different speeds
    void move(std::vector<SDL_Rect*> walls);

		//check if we went out of bounds
		bool checkBounds( SDL_Rect* border );

    //our render function
    void render();

    //for changing sprites
    void movingAnimation();

    //collision detection between two rectangles
    bool checkCollision( SDL_Rect* a, SDL_Rect* b );

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			getters
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//return our collider so we can add it to our vector for check
		SDL_Rect* getCollider();
		int getXPos();
		int getYPos();

  protected:
		double damage;
		Character* started;
		Character* target;
    int x, y;
		int timer;
   	double xVel, yVel;
		int travelDist;
		int distanceTrav;
    int projVel;
    double angle;
    SDL_RendererFlip flip;
    LTexture projTexture;

    //collision box
    SDL_Rect mCollider;

    //our sprite clips and stuff
    vector< SDL_Rect > spriteClips;
    int currClip;
		int numClips;
};
