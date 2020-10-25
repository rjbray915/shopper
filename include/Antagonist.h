#include "./Character.h"
#include "./Projectile.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>

class Antagonist : public Character{
	public:
		using Character::Character;
		void initProjectile(Character* target);
		void setVelocity(int randNum);
		void followCharacter(Character* followed);
	
		Projectile* antProjectile;
};
