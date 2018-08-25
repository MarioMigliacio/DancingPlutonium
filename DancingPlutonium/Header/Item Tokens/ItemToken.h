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
		#pragma region Enum Type

		/* An enumeration particular to the item type tokens. */
		enum ItemType
		{
			BombToken,
			DamageToken,
			FireRateToken,
			FreeScoreToken,
			LifeToken,
			PatternToken
		};

		#pragma endregion
	public:
		#pragma region Ctor/Dtor

		/* The defualt Ctor for the ItemToken object. */
		ItemToken() : 
			isActive(false),
			accumulator(0.0f),
			speed(0.0f),
			sprite(),
			texture(),
			position(),
			itemType(0)
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
		/* Returns the position of this ItemToken. */
		virtual sf::Vector2f GetPosition() const;
		/* Sets the position and sprite of this ItemToken to the value of _pos. */
		virtual void SetPosition(const sf::Vector2f& _pos);
		/* Returns the Enumeration type of Item that belongs to this ItemToken. */
		virtual sf::Uint32 GetType();
		/* Sets the position of this ItemToken to random area. */
		virtual void SpawnRandomly(const sf::RenderTarget& _rt);
		/* Returns the state of whether or not this ItemToken is within the game screen bounds. */
		virtual bool IsWithinBounds(const sf::RenderTarget& _rt);
		/* Update the qualities of the render token. */
		virtual void Update(const float& _dt, const sf::RenderTarget& _rt);
		/* Sets the sprite for this ItemToken object. */
		virtual void SetSprite() = 0;

		#pragma endregion

	protected:
		#pragma region Members

		bool isActive;										/* Represents a boolean value that can be used to tell the outside world if this ItemToken is active. */
		float accumulator;									/* Represents an accumulator value to perform behavior after time passes. */
		float speed;										/* Represents the speed for this ItemToken. */
		sf::Sprite sprite;									/* Represents the sprite for this ItemToken. */
		sf::Texture texture;								/* Represents the texture for this ItemToken. */
		sf::Vector2f position;								/* Represents the position for this ItemToken. */
		sf::Uint32 itemType;								/* Represents this ItemTokens ItemType enum. */

		#pragma endregion
	};
}