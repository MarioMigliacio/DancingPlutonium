#pragma once

#include <SFML/Graphics.hpp>
#include "IRng.h"

namespace DancingPlutonium
{
	/* ItemToken object represents items that can be left behind by killing enemy units or perhaps spawning randomly with time in the world.
	They have beneficial effects for the player when picked up. */
	class ItemToken
	{
	public:
		#pragma region Ctor/Dtor

		/* The defualt Ctor for the ItemToken object. */
		ItemToken() : 
			isActive(false),
			accumulator(0.0f),
			speed(0.0f),
			sprite(),
			texture(),
			position()
		{}

		/* The Dtor for the ItemToken object. */
		virtual ~ItemToken() {}

		#pragma endregion

	public:
		#pragma region Update/Draw

		/* Draw this ItemToken into the world. */
		virtual void Draw(sf::RenderTarget& _rt);
		/* Returns whether or not this ItemToken is actively available. */
		virtual bool IsActive() const;
		/* Changes the isActive member variable for this ItemToken. */
		virtual void ToggleActiveState();
		/* Returns the sprite for this ItemToken object. */
		virtual sf::Sprite& GetSprite();
		/* Returns the position of this ItemToken */
		virtual sf::Vector2f GetPosition() const;
		/* Sets the position and sprite of this ItemToken to the value of _pos */
		virtual void SetPosition(const sf::Vector2f& _pos);
		/* Sets the position of this ItemToken to random area */
		virtual void SpawnRandomly(const sf::RenderTarget& _rt);
		/* Returns the state of whether or not this ItemToken is within the game screen bounds. */
		virtual bool IsWithinBounds(const sf::RenderTarget& _rt);
		/* Sets the sprite for this ItemToken object. */
		virtual void SetSprite() = 0;
		/* Update the qualities of the render token. */
		virtual void Update(const float& _dt, const sf::RenderTarget& _rt) = 0;

		#pragma endregion

	protected:
		#pragma region Members

		bool isActive;										/* Represents a boolean value that can be used to tell the outside world if this ItemToken is active. */
		float accumulator;									/* Represents an accumulator value to perform behavior after time passes. */
		float speed;										/* Represents the speed for this ItemToken */
		sf::Sprite sprite;									/* Represents the sprite for this ItemToken. */
		sf::Texture texture;								/* Represents the texture for this ItemToken. */
		sf::Vector2f position;								/* Represents the position for this ItemToken. */

		#pragma endregion
	};
}