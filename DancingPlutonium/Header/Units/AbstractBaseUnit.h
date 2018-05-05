#pragma once

#include<SFML/Graphics.hpp>
#include "IRng.h"
#include "AbstractBaseProjectile.h"
#include "Weapon.h"

namespace DancingPlutonium
{
	/* AbstractBaseUnit class represents an abstract base unit for which to inherit from */
	class AbstractBaseUnit
	{
	protected:
		#pragma region Members

		int value;											/* Represents the point value for the player upon killing this unit */
		float health;										/* Represents the health points this unit has */
		float damageMultiplier;								/* Represents the additional damage multiplier this unit can deal */
		float fireRate;										/* Represents the rate of fire this unit is allowed to shoot projectiles */
		float speed;										/* Represents the speed that this unit may move at */
		float accumulator;									/* Represents the accumulation of clock time, for special use with fireRate */
		bool isActive;										/* Represents the state of whether this unit is active or dead */
		short allegiance;									/* Represents the friendly/foe status for this unit */
		sf::Sprite sprite;									/* Represents the sprite for this unit */
		sf::Texture texture;								/* Represents the texture for this unit */
		sf::Vector2f position;								/* Represents the position for this unit */
		Weapon* weapon;										/* Represents the weapon for this unit */

		#pragma endregion
	public:

		#pragma region Virtual Dtor

		/* The virtual AbstractBaseUnit destructor */
		virtual ~AbstractBaseUnit() {}

		#pragma endregion

		#pragma region Methods

		/* Returns the value of this unit */
		virtual int GetValue() const;
		/* Returns the health of this unit */
		virtual float GetHealth() const;
		/* Returns the damageMultiplier of this unit */
		virtual float GetDamageMultiplier() const;
		/* Returns the fireRate of this unit */
		virtual float GetFireRate() const;
		/* Returns the speed of this unit */
		virtual float GetSpeed() const;
		/* Returns true if this unit is active, false otherwise */
		virtual bool GetActiveState(const sf::RenderTarget& _rt);
		/* Allows access to this PlutoniumShip objects weapon pointer */
		virtual Weapon* GetWeaponEquipped() const;
		/* Returns the sprite of this unit */
		virtual sf::Sprite& GetSprite();
		/* Returns the texture of this unit */
		virtual sf::Texture GetTexture() const;
		/* Returns the position of this unit */
		virtual sf::Vector2f GetPosition() const;
		/* Returns the rectangle representing the bounds of this unit */
		virtual sf::FloatRect GetBounds() const;
		/* Sets the position and sprite of this projectile to the value of _pos */
		virtual void SetPosition(const sf::Vector2f& _pos);
		/* Sets the health of this unit to the value of _val */
		virtual void SetHealth(const int _val);
		/* Sets the position of this unit to random area */
		virtual void SpawnRandomly(const sf::RenderTarget& _rt);
		/* Draw this unit onto the world */
		virtual void Draw(sf::RenderTarget& _rt);
		/* Sets the Weaponry state for this unit to a safe default state */
		virtual void InitializeWeaponry() = 0;
		/* Update this unit in the world based on the clock */
		virtual void Update(float _dt, sf::RenderTarget& _rt) = 0;
		/* Abstract method SetSprite must be implemented by inheriting children */
		virtual void SetSprite(const sf::RenderTarget& _rt) = 0;
		/* Abstract method ShootBullet must be implemented by inheriting children */
		virtual void ShootBullet(const float _dt) = 0;

		#pragma endregion
	};
}