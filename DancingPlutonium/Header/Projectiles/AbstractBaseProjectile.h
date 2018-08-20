#pragma once

#include <SFML/Graphics.hpp>

namespace DancingPlutonium
{
	/* AbstractBaseProjectile class represents an abstract base projectile for which to inherit from */
	class AbstractBaseProjectile
	{
	public:
		#pragma region Virtual Dtor

		/* The virtual Projectile Destructor */
		virtual ~AbstractBaseProjectile() {}

		#pragma endregion

	public:
		#pragma region State Enumerations

		/* An enumeration particular to the projectile damage state */
		enum projectileDamageState
		{
			d_Uninitialized,
			d_Normal,
			d_One,
			d_Two,
			d_Three,
			d_Four,
			d_Max
		};

		/* An enumeration particular to the projectile fire rate state */
		enum projectileFireRateState
		{
			r_Uninitialized,
			r_Normal,
			r_One,
			r_Two,
			r_Three,
			r_Four,
			r_Max
		};

		/* An enumeration particular to the projectile velocity rate state */
		enum projectileVelocityState
		{
			v_Uninitialized,
			v_Normal,
			v_One,
			v_Two,
			v_Three,
			v_Four,
			v_Max
		};

		#pragma endregion

	public:
		#pragma region Pattern Enumerations

		/* ProjectilePatterns enum encapsulates the types of projectile PATTERNS that can be found in DancingPlutonium */
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
		short allegiance;				/* Represents the allegiance of this projectile */
		bool innert;					/* Represents if this projectile can hurt or not */
		float speed;					/* Represents the speed that this projectile will travel at */
		float damage;					/* Represents the damage that this proctile will do upon impact */

		#pragma endregion

	public:
		#pragma region Methods

		/* Sets the allegiance state for this projectile */
		void SetAllegiance(short _allegiance);
		/* Returns the allegiance state for this projectile */
		short GetAllegiance() const;
		/* Returns the speed for this projectile */
		float GetSpeed() const;
		/* Sets the speed for this projectile */
		void SetSpeed(const float _speed);
		/* Returns true if this projectile has not yet hurt a unit, it is said to be active and not 'innert', false otherwise */
		bool IsInnert() const;
		/* If a bullet is not innert, turn it to innert so that it cant do damage, and it will stop updating */
		void RenderInnert();
		/* Returns the damage from this projectile */
		float GetDamage() const;
		/* Sets the damage for this projectile */
		void SetDamage(const float _damage);
		/* Returns a reference to this projectiles sprite */
		virtual sf::Sprite& GetSprite();
		/* Returns the position for this projectile */
		virtual sf::Vector2f GetPosition() const;
		/* Sets the position and sprite of this projectile to the value of _pos */
		virtual void SetPosition(const sf::Vector2f& _pos);
		/* Returns true if this projectile is active, false otherwise */
		virtual bool GetActiveState(const sf::RenderTarget& _rt) = 0;
		/* Returns the sprites representing the shots for this projectile */
		virtual std::vector<sf::Sprite> GetAllSprites() = 0;
		/* Returns the projectiles used to represent this type of bullet spray pattern */
		virtual std::vector<AbstractBaseProjectile*> GetAllComponentBullets() = 0;
		/* Draw this projectiles sprite onto the render window _rt */
		virtual void Draw(sf::RenderTarget& _rt) = 0;
		/* Abstract method Update must be implemented by inheriting children */
		virtual void Update(float _dt) = 0;
		/* Abstract method SetSprite must be implemented by inheriting children */
		virtual void SetSprite(const sf::Vector2f& _origin) = 0;

		#pragma endregion
	};
}