#pragma once

#include<SFML/Graphics.hpp>
#include "Bullet.h"
#include "BasicBulletPlayer.h"

namespace DancingPlutonium
{
	/* TripleBulletPlayer class is a specialized bullet object which has a triple shot action trajectory */
	class TripleBulletPlayer : public Bullet
	{
	private:
		#pragma region Extra projectile objects

		Bullet* leftProjectile;		/* Represents a left side trajectory bullet object off the main shot */
		Bullet* rightProjectile;	/* Represents a right side trajectory bullet object off the main shot */

		#pragma endregion		
	public:
		#pragma region Ctor/Dtors

		/* TripleBulletPlayer constructor accepting RenderTarget, and Position input parameters */
		TripleBulletPlayer(const sf::Vector2f& _pos);
		/* TripleBulletPlayer copy constructor */
		TripleBulletPlayer(const TripleBulletPlayer& _ref) {}
		/* TripleBulletPlayer deconstructor */
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