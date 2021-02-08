#pragma once
#include "./Character.h"
#include "./Projectile.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>

class Antagonist : public Character{
	public:
		using Character::Character;
		void initProjectile(double damage, Character* target);
		void setVelocity(int randNum);
		void followCharacter(Character* followed);
		void move( std::vector<SDL_Rect*>* walls );
		void walk_isle();
		void set_target(Character* pTarget);
		void render();

		Character* target;
		Projectile* antProjectile;
};
