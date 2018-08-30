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

		/* Bomb constructor accepting RenderTarget, and Position input parameters. */
		Bomb(const sf::Vector2f& _pos);
		/* Bomb copy constructor. */
		Bomb(const Bomb& _ref) {}
		/* BasicBullet destructor. */
		~Bomb();

		#pragma endregion

		#pragma region Methods
		
		/* Returns the damage that a bomb deals every frame. */
		float GetDamagePerFrame();
		/* Sets the position of this bomb. */
		void SetPosition(const sf::Vector2f& _pos);
		/* Sets this bomb sprite, texture and default position. */
		void SetSprite(const sf::Vector2f& _origin);
		/* Update this bomb in the world based on the clock. */
		void Update(float _dt);
		/* Draw this bomb in the world. */
		void Draw(sf::RenderTarget& _rt);
		/* Returns true if this bomb is active, false otherwise. */
		bool GetActiveState();
		/* Returns true if this bomb is in an exploding state, false otherwise. */
		bool IsExploding();
		/* Returns the sprite representing the projectile portion of this bomb. */
		sf::Sprite GetSprite();
		/* Returns  the sprite representing the explosion portion of this bomb. */
		sf::Sprite GetExplosionSprite();
		
		#pragma endregion

	private:
		#pragma region Internal Methods

		/* initialize the animation spreadsheet stuff. */
		void InitializeAnimationSpriteSheet();

		#pragma endregion

	private:
		#pragma region Private members variables

		Animation bombAnimation;					/* Represents this bombs Animation object. */
		Animation* currentAnimation;				/* Represents the current animation that is going to play. */
		AnimatedSprite animatedSprite;				/* Represents this bombs animatedSprite. */
		sf::Texture texture;						/* Represents this bombs default traveling texture. */
		sf::Texture explodingTexture;				/* Represents this bombs exploding animation texture. */
		sf::Vector2f position;						/* Represents this bombs position in space. */
		sf::Sprite sprite;							/* Represents the sprite for the projectile portion of this bomb.. */
		sf::Sprite explosionSprite;					/* Represents the sprite for the explosion portion of this bomb. */

		bool isActive;								/* Represents the active state for this bomb object. */
		bool isExploding;							/* Represents a boolean to keep track of if it is time to explode. */
		float accumulator;							/* Represents a timer based object to perform logic based off of. */
		const float defaultDamage = 100.f;			/* Represents a defaultDamage that is safe to use for this projectile (per frame basis). */
		const float defaultSpeed = 150.f;			/* Represents a defaultSpeed that is safe to use for this projectile. */
		const int imgwidth = 128;					/* Represents this sprite images width dimension in pixels. */
		const float scale = 3.f;					/* Represents this sprite images scale factor. */

		#pragma endregion
	};
}