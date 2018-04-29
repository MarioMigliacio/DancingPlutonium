#pragma once

#include<SFML/Graphics.hpp>
#include "AbstractBaseProjectile.h"

namespace DancingPlutonium
{
	/* Weapon_GrowingShot class is the 1st stage bullet object which has a very 'basic' pattern trajectory */
	class Weapon_GrowingShot : public AbstractBaseProjectile
	{
	public:
#pragma region Ctor/Dtors

		/* Weapon_GrowingShot constructor accepting RenderTarget, and Position input parameters */
		Weapon_GrowingShot(const sf::Vector2f& _pos);
		/* Weapon_GrowingShot copy constructor */
		Weapon_GrowingShot(const Weapon_GrowingShot& _ref) {}
		/* Weapon_GrowingShot destructor */
		~Weapon_GrowingShot() {}

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