#pragma once

#include<SFML/Graphics.hpp>
#include "AbstractBaseProjectile.h"
#include "BulletFactory.h"
#include "Weapon_BasicShot.h"

namespace DancingPlutonium
{
	/* Weapon_TripleShot class is a specialized bullet object which has a triple shot action trajectory */
	class Weapon_TripleShot : public AbstractBaseProjectile
	{
	private:
		#pragma region Extra projectile objects

		AbstractBaseProjectile* leftProjectile;		/* Represents a left side trajectory bullet object off the main shot */
		AbstractBaseProjectile* centerProjectile;	/* Represents a center trajectory bullet object */
		AbstractBaseProjectile* rightProjectile;	/* Represents a right side trajectory bullet object off the main shot */

		#pragma endregion		
	public:
		#pragma region Ctor/Dtors

		/* Weapon_TripleShot constructor accepting RenderTarget, and Position input parameters */
		Weapon_TripleShot(const sf::Vector2f& _pos);
		/* A specialized Doubleshot constructor which also accepts a damage, velocity, and allegiance input */
		Weapon_TripleShot(const sf::Vector2f& _pos, const float& _dmg, const float& _vel, const short& _alle);
		/* Weapon_TripleShot copy constructor */
		Weapon_TripleShot(const Weapon_TripleShot& _ref) {}
		/* Weapon_TripleShot destructor */
		~Weapon_TripleShot();

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

		const float defaultDamage = 60.f;			/* Represents a defaultDamage that is safe to use for this projectile */
		const float defaultSpeed = 200.f;			/* Represents a defaultSpeed that is safe to use for this projectile */

		#pragma endregion
	};
}