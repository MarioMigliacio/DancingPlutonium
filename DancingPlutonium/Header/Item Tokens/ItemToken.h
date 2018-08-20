#pragma once

#include <SFML/Graphics.hpp>

namespace DancingPlutonium
{
	/* ItemToken object represents items that can be left behind by killing enemy units or perhaps spawning randomly with time in the world.
	They have beneficial effects for the player when picked up. */
	class ItemToken
	{
	public:
		#pragma region Ctor/Dtor

		/* The Ctor for the ItemToken object, which accepts a position to spawn at. */
		ItemToken(const sf::Vector2f& _pos);
		/* The copy Ctor for the ItemToken object. */
		ItemToken(const ItemToken& _ref) {}
		/* The Dtor for the ItemToken object. */
		~ItemToken() {}

		#pragma endregion

	public:
		#pragma region Update/Draw

		/* Update the qualities of the render token (plan to make them move after a set time period. */
		void Update(const float& _dt);
		/* Draw this ItemToken into the world. */
		void Draw(const sf::RenderTarget& _rt);
		/* Returns whether or not this ItemToken is actively available. */
		bool IsActive() const;
		/* Changes the isActive member variable for this ItemToken. */
		void ToggleActiveState();
		/* Returns the sprite for this ItemToken object. */
		sf::Sprite& GetSprite();
		/* Sets the sprite for this ItemToken object. */
		void SetSprite(const sf::Vector2f& _origin);

		#pragma endregion

	private:
		#pragma region Members

		bool isActive;										/* Represents a boolean value that can be used to tell the outside world if its active. */
		float accumulator;									/* Represents an accumulator value to perform behavior after time passes. */
		sf::Sprite sprite;									/* Represents the sprite for this unit. */
		sf::Texture texture;								/* Represents the texture for this unit. */
		sf::Vector2f position;								/* Represents the position for this unit. */

		#pragma endregion
	};
}