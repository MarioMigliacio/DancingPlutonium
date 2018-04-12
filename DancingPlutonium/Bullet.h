#pragma once

#include<SFML/Graphics.hpp>

namespace DancingPlutonium
{
	/* Bullet class represents an abstract base projectile for which to inherit from */
	class Bullet
	{
	protected:
		#pragma region Members

		float speed;					/* Represents the speed that the projectile will travel at */
		sf::Sprite sprite;				/* Represents the sprite for this projectile */
		sf::Texture texture;			/* Represents the texture for this projectile */
		sf::Vector2f position;			/* Represents the position for this projectile */

		#pragma endregion
	public:
		/* The virtual Bullet Destructor */
		virtual ~Bullet() {}

		#pragma region Methods

		/* Returns the speed for this projectile */
		float GetSpeed() const;
		/* Returns true if this projectile is active, false otherwise */
		bool GetActiveState(const sf::RenderTarget& _rt) const;
		/* Returns a reference to this projectiles sprite */
		virtual sf::Sprite& GetSprite();
		/* Returns the rectangle representing the bounds of this projectile */
		virtual sf::FloatRect GetBounds() const;
		/* Returns the position for this projectile */
		virtual sf::Vector2f GetPosition() const;
		/* Sets the position and sprite of this projectile to the value of _pos */
		virtual void SetPosition(const sf::Vector2f& _pos);
		/* Draw this projectiles sprite onto the render window _rt */
		virtual void Draw(sf::RenderTarget& _rt) = 0;
		/* Abstract method Update must be implemented by inheriting children */
		virtual void Update(float _dt) = 0;
		/* Abstract method SetSprite must be implemented by inheriting children */
		virtual void SetSprite(const sf::Vector2f& _origin) = 0;

		#pragma endregion
	};
}