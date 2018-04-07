#pragma once

#include<SFML/Graphics.hpp>
#include "Bullet.h"

namespace DancingPlutonium
{
	/* BasicBullet class is the 1st stage bullet object which has a very 'basic' pattern trajectory */
	class BasicBullet : public Bullet
	{		
	public:
		#pragma region Ctor/Dtors

		/* BasicBullet constructor accepting RenderTarget, and Position input parameters */
		BasicBullet(const sf::RenderTarget& _rt, const sf::Vector2f& _pos);
		/* BasicBullet copy constructor */
		BasicBullet(const BasicBullet& _ref) {}
		/* BasicBullet deconstructor */
		~BasicBullet() {}

		#pragma endregion		

		#pragma region Methods

		/* Sets this projectiles sprite, texture and default position */
		virtual void SetSprite(const sf::Vector2f & _origin) override;

		/* Update this projectile in the world based on the clock */
		virtual void Update(float _dt) override;

		#pragma endregion				
	};
}