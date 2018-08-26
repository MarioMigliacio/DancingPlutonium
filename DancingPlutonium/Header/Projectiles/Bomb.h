#pragma once

#include<SFML/Graphics.hpp>
#include "AnimatedSprite.h"

namespace DancingPlutonium
{
	/* Bomb class is the bomb diggity. It acts like a projectile but does immense damage. */
	class Bomb
	{
	public:
		#pragma region Ctor/Dtors

		/* Bomb constructor accepting RenderTarget, and Position input parameters */
		Bomb(const sf::Vector2f& _pos);
		/* Bomb copy constructor */
		Bomb(const Bomb& _ref) {}
		/* BasicBullet destructor */
		~Bomb() {}

		#pragma endregion

		#pragma region Methods

		/* Sets this projectiles sprite, texture and default position */
		void SetSprite(const sf::Vector2f& _origin);
		/* Update this projectile in the world based on the clock */
		void Update(float _dt);
		// Draw this projectile in the world
		void Draw(sf::RenderTarget& _rt);
		/* Returns true if this projectile is active, false otherwise */
		bool GetActiveState(const sf::RenderTarget& _rt);
		/* Returns the sprites representing the shots for this projectile */
		sf::Sprite GetSprite();

		#pragma endregion

	private:
		#pragma region Internal Methods

		/* initialize the animation spreadsheet stuff */
		void InitializeAnimationSpriteSheet();

		#pragma endregion

	private:
		#pragma region Default values

		Animation* currentAnimation;
		sf::Texture texture;
		AnimatedSprite animatedSprite;

		float accumulator;

		const float defaultDamage = 200.f;			/* Represents a defaultDamage that is safe to use for this projectile */
		const float defaultSpeed = 200.f;			/* Represents a defaultSpeed that is safe to use for this projectile */

		#pragma endregion
	};
}