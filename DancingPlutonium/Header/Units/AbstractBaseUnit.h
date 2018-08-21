#pragma once

#include <SFML/Graphics.hpp>
#include "IRng.h"
#include "AbstractBaseProjectile.h"
#include "Weapon.h"

namespace DancingPlutonium
{
	/* AbstractBaseUnit class represents an abstract base unit for which to inherit from */
	class AbstractBaseUnit
	{
	public:
		#pragma region Protected 

		/* AbstractBaseUnit default Ctor */
		AbstractBaseUnit() :
			value(0),
			health(0),
			isInvulnerable(false),
			isFiring(false),
			damageMultiplier(1),
			fireRate(0),
			speed(0),
			accumulator(0),
			isActive(false),
			allegiance(0),
			sprite(),
			texture(),
			position(),
			weapon()
		{}

		/* The virtual AbstractBaseUnit destructor */
		virtual ~AbstractBaseUnit() {}

		#pragma endregion

	protected:
		#pragma region Members

		int value;											/* Represents the point value for the player upon killing this unit */
		float health;										/* Represents the health points this unit has */
		bool isInvulnerable;								/* Represents the invulnerable state for this unit */
		bool isFiring;										/* Represents the firing state for this unit */
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
		#pragma region Methods

		/* Returns the value of this unit */
		virtual int GetValue() const;
		/* Returns the health of this unit */
		virtual float GetHealth() const;
		/* Returns the state of invulnerability for this unit */
		virtual bool IsInvulnerable() const;
		/* Changes the state of vulnerability for this unit */
		virtual void ToggleInvulnerability();
		/* Returns the state of firing projectiles for this unit */
		virtual bool IsFiringBullet() const;
		/* Changes the state of firing projectiles for this unit */
		virtual void ToggleFiring();
		/* Returns the damageMultiplier of this unit */
		virtual float GetDamageMultiplier() const;
		/* Returns the fireRate of this unit */
		virtual float GetFireRate() const;
		/* Returns the speed of this unit */
		virtual float GetSpeed() const;
		/* Returns true if this unit is within the bounds of screen, false otherwise */
		virtual bool IsWithinBounds(const sf::RenderTarget& _rt);
		/* Allows access to this PlutoniumShip objects weapon pointer */
		virtual Weapon* GetWeaponEquipped();
		/* Returns the activeState of this unit */
		virtual bool GetActiveState() const;
		/* Returns the allegiance value of this unit */
		virtual short GetAllegiance() const;
		/* Returns the position of this unit */
		virtual sf::Vector2f GetPosition() const;
		/* Sets the position and sprite of this projectile to the value of _pos */
		virtual void SetPosition(const sf::Vector2f& _pos);
		/* Sets the health of this unit by subtracting the value of _val */
		virtual void TakeDamage(const float _val);
		/* Sets the position of this unit to random area */
		virtual void SpawnRandomly(const sf::RenderTarget& _rt);
		/* Draw this unit onto the world */
		virtual void Draw(sf::RenderTarget& _rt);
		/* Get the information if this unit is allowed to shoot right now (query the weapon for fire rate logic) */
		virtual bool CanShoot(const float& _dt) = 0;
		/* Call upon this unit to perform shoot logic */
		virtual AbstractBaseProjectile* Shoot() = 0;
		/* Returns the sprite of this unit */
		virtual sf::Sprite& GetSprite() = 0;
		/* Update this unit in the world based on the clock */
		virtual void Update(float _dt, sf::RenderTarget& _rt) = 0;
		/* Abstract method SetSprite must be implemented by inheriting children */
		virtual void SetSprite(const sf::RenderTarget& _rt) = 0;

		#pragma endregion
	};
}