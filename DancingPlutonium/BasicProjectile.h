#pragma once

#include<SFML/Graphics.hpp>
#include "Projectile.h"
#include "BasicShip.h"

namespace DancingPlutonium
{
	/* BasicProjectile class is the 1st stage bullet object which has a very 'basic' pattern trajectory */
	class BasicProjectile : public Projectile
	{		
	public:
		#pragma region Ctor/Dtors

		/* BasicBullet constructor accepting RenderTarget, and Position input parameters */
		BasicProjectile(const sf::Vector2f& _pos);
		/* BasicBullet copy constructor */
		BasicProjectile(const BasicProjectile& _ref) {}
		/* BasicBullet destructor */
		~BasicProjectile() {}

		#pragma endregion

		#pragma region Methods

		/* Sets this projectiles sprite, texture and default position */
		virtual void SetSprite(const sf::Vector2f & _origin) override;
		/* Update this projectile in the world based on the clock */
		virtual void Update(float _dt) override;
		// Draw this projectile in the world
		virtual void Draw(sf::RenderTarget& _rt) override;

		#pragma endregion
	};
}