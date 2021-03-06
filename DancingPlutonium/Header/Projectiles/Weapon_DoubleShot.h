#pragma once

#include<SFML/Graphics.hpp>
#include "AbstractBaseProjectile.h"
#include "BulletFactory.h"
#include "Weapon_BasicShot.h"

namespace DancingPlutonium
{
	/* Weapon_DoubleShot class is the 1st stage bullet object which has a very 'basic' pattern trajectory */
	class Weapon_DoubleShot : public AbstractBaseProjectile
	{
	private:
		#pragma region Extra projectile objects

		AbstractBaseProjectile* leftProjectile;		/* Represents a left side trajectory bullet object off the main shot */
		AbstractBaseProjectile* rightProjectile;	/* Represents a right side trajectory bullet object off the main shot */

		#pragma endregion		
	public:
		#pragma region Ctor/Dtors

		/* Weapon_DoubleShot constructor accepting RenderTarget, and Position input parameters */
		Weapon_DoubleShot(const sf::Vector2f& _pos);
		/* A specialized Doubleshot constructor which also accepts a damage, velocity, and allegiance input */
		Weapon_DoubleShot(const sf::Vector2f& _pos, const float& _dmg, const float& _vel, const short& _alle);
		/* Weapon_DoubleShot copy constructor */
		Weapon_DoubleShot(const Weapon_DoubleShot& _ref) {}
		/* Weapon_DoubleShot destructor */
		~Weapon_DoubleShot();

		#pragma endregion

		#pragma region Methods

		/* Sets this projectiles sprite, texture and default position */
		virtual void SetSprite(const sf::Vector2f& _origin) override;
		/* Update this projectile in the world based on the clock */
		virtual void Update(float _dt) override;
		// Draw this projectile in the world
		virtual void Draw(sf::RenderTarget& _rt) override;
		/* Returns true if this projectile is active, false otherwise */
		virtual bool GetActiveState(const sf::RenderTarget& _rt) override;
		/* Returns the sprites representing the shots for this projectile */
		virtual std::vector<sf::Sprite> GetAllSprites() override;
		/* Returns the projectiles used to represent this type of bullet spray pattern */
		virtual std::vector<AbstractBaseProjectile*> GetAllComponentBullets() override;

		#pragma endregion		

	private:
		#pragma region Default values

		const float defaultDamage = 55.f;			/* Represents a defaultDamage that is safe to use for this projectile */
		const float defaultSpeed = 200.f;			/* Represents a defaultSpeed that is safe to use for this projectile */

		#pragma endregion
	};
}