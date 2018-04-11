#pragma once

#include<SFML/Graphics.hpp>
#include "Bullet.h"
#include "BasicBulletPlayer.h"

namespace DancingPlutonium
{
	/* BasicBulletPlayer class is the 1st stage bullet object which has a very 'basic' pattern trajectory */
	class TripleBulletPlayer : public Bullet
	{
	private:
		Bullet* leftProjectile;
		Bullet* rightProjectile;

	public:
		#pragma region Ctor/Dtors

		/* BasicBulletPlayer constructor accepting RenderTarget, and Position input parameters */
		TripleBulletPlayer(const sf::RenderTarget& _rt, const sf::Vector2f& _pos);
		/* BasicBulletPlayer copy constructor */
		TripleBulletPlayer(const TripleBulletPlayer& _ref) {}
		/* BasicBulletPlayer deconstructor */
		~TripleBulletPlayer();

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