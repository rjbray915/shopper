#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "LTexture.h"
using namespace std;

class Character{
  public:
    //construct/destruct
    Character(double pMaxHitPoints, double pX, double pY, double pCharVel, double pAngle, SDL_RendererFlip pFlip,
							int pNumClips, int pClipWidth, int pClipHeight, string imgPath);
    ~Character();

    //handles events. characters will handle different events
    void handleEvent( SDL_Event* e );

    //movement functions. characters will move at different speeds
    void move( std::vector<SDL_Rect*> walls );

		//check if we went out of bounds
		bool checkBounds( SDL_Rect* border );

    //our render function
    void render();

    //for changing sprites
    void movingAnimation();

    //collision detection between two rectangles
    bool checkCollision( SDL_Rect* a, SDL_Rect* b );

		//take a hit
		void take_hit(double dmg);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			getters
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//return our collider so we can add it to our vector for check
		SDL_Rect* getCollider();
		int getXPos();
		int getYPos();

  protected:
		double curHitPoints, maxHitPoints;
    double x, y;
    double xVel, yVel;
    double charVel;
    double angle;
    SDL_RendererFlip flip;
    LTexture charTexture;

    //collision box
    SDL_Rect mCollider;

    //our sprite clips and stuff
    vector< SDL_Rect > spriteClips;
    int currClip;
		int numClips;
};
