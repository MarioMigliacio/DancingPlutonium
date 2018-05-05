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
		/* BasicBullet copy constructor */
		Weapon_BasicShot(const Weapon_BasicShot& _ref) {}
		/* BasicBullet destructor */
		~Weapon_BasicShot() {}

		#pragma endregion

		#pragma region Methods

		/* Sets this projectiles sprite, texture and default position */
		virtual void SetSprite(const sf::Vector2f & _origin) override;
		/* Update this projectile in the world based on the clock */
		virtual void Update(float _dt) override;
		// Draw this projectile in the world
		virtual void Draw(sf::RenderTarget& _rt) override;

		#pragma endregion

		// Inherited via AbstractBaseProjectile
		virtual std::vector<sf::FloatRect> GetBounds() override;
	};
}