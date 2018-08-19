#pragma once

#include<SFML/Graphics.hpp>
#include "AbstractBaseProjectile.h"

namespace DancingPlutonium
{
	/* Weapon_BasicShot class is the 1st stage bullet object which has a very 'basic' pattern trajectory */
	class Weapon_BasicShot : public AbstractBaseProjectile
	{		
	public:
		#pragma region Ctor/Dtors

		/* BasicBullet constructor accepting RenderTarget, and Position input parameters */
		Weapon_BasicShot(const sf::Vector2f& _pos);
		/* A specialized BasicBullet constructor which also accepts a damage, velocity, and allegiance input */
		Weapon_BasicShot(const sf::Vector2f& _pos, const float& _dmg, const float& _vel, const short& _alle);
		/* BasicBullet copy constructor */
		Weapon_BasicShot(const Weapon_BasicShot& _ref) {}
		/* BasicBullet destructor */
		~Weapon_BasicShot() {}

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

		const float defaultDamage = 50.f;			/* Represents a defaultDamage that is safe to use for this projectile */
		const float defaultSpeed = 200.f;			/* Represents a defaultSpeed that is safe to use for this projectile */

		#pragma endregion
	};
}