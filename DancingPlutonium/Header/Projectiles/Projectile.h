#pragma once

#include<SFML/Graphics.hpp>

namespace DancingPlutonium
{
	/* Projectile class represents an abstract base projectile for which to inherit from */
	class Projectile
	{
	public:
		#pragma region Patterns enum

		/* ProjectilePatterns enum encapsulates the types of projectile PATTERNS that can be found in DancingPlutonium (the advanced bullet patterns) */
		enum ProjectilePattern
		{
			NoBullet,
			BasicShot,
			DoubleShot,
			TripleShot,
			QuadShot,
			AimedShot,
			GrowingShot,
			HomingShot,
			IncendiaryShot,
			PhotonPacket,
			PhotonStream,
			PhotonTriplet,
			PhotonQuartet,
			StandardLazer,
			JoesLazer,
			IMMAFIRINMAHLAZOR,
		};
		#pragma endregion

	protected:
		#pragma region Members

		sf::Sprite sprite;				/* Represents the sprite for this projectile */
		sf::Texture texture;			/* Represents the texture for this projectile */
		sf::Vector2f position;			/* Represents the position for this projectile */
		bool friendly;					/* Represents the allegiance of this projectile */
		bool innert;					/* Represents if this projectile can hurt or not */
		float speed;					/* Represents the speed that this projectile will travel at */
		float damage;					/* Represents the damage that this proctile will do upon impact */

		#pragma endregion
	public:
		#pragma region Virtual Dtor

		/* The virtual Bullet Destructor */
		virtual ~Projectile() {}

		#pragma endregion

		#pragma region Methods

		/* Returns the speed for this projectile */
		float GetSpeed() const;
		/* Sets the speed for this projectile */
		void SetSpeed(const float _speed);
		/* Returns true if this projectile is fired by the player, false otherwise */
		bool IsFriendly() const;
		/* Returns true if this projectile has not yet hurt a unit, it is said to be active or 'innert', false otherwise */
		bool IsInnert() const;
		/* Returns the damage from this projectile */
		float GetDamage() const;
		/* Sets the damage for this projectile */
		void SetDamage(const float _damage);
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