#pragma once

#include <SFML\Graphics.hpp>
#include "BulletFactory.h"
#include "AbstractBaseProjectile.h"

namespace DancingPlutonium
{
	class Weapon
	{
	public:
		#pragma region Ctor / Dtor

		/* The Weapon default Ctor */
		Weapon() {}
		/* The Weapon constructor which uses _fireRate and _allegiance input parameters */
		Weapon(const float _fireRate, short _allegiance);
		/* The Weapon copy Ctor */
		Weapon(const Weapon& _ref) {}
		/* The Weapon default Dtor */
		~Weapon();

		#pragma endregion

	public:
		#pragma region Methods

		/* Upgrade this weapon objects Projectile Pattern to the next logical stage */
		void UpgradeWeaponPattern();
		/* Takes projectile damage to an increased logical state */
		void UpgradeWeaponDamage();
		/* Allows for the weapon to alter the fire rate of ammunition */
		void UpgradeWeaponFireRate();
		/* Takes projectile velocity to an increased logical state */
		void UpgradeWeaponVelocityRate();
		/* Allows for the weapons pattern to be set to a particular state (ex: AbstractBaseProjectile::ProjectilePattern::BasicShot) */
		void SetWeaponPattern(const sf::Uint32 _pat);
		/* Allows for the weapons damage to be set to a particular state (ex: AbstractBaseProjectile::projectileDamageState::d_Normal) */
		void SetWeaponDamageState(const sf::Uint32 _dmg);
		/* Allows for the weapons fire rate to be set to a particular state (ex: AbstractBaseProjectile::projectileFireRateState::r_Normal) */
		void SetWeaponFireRateState(const sf::Uint32 _rate);
		/* Allows for the weapons velocity rate to be set to a particular state (ex: AbstractBaseProjectile::projectileVelocityState::v_Normal) */
		void SetWeaponVelocityState(const sf::Uint32 _veloc);
		/* Ask our weapon whether or not it is allowed to shoot a projectile at this time */
		bool CanShoot(const float _dt);
		/* Ask our weapon to call the BulletFactory to grant us a pointer to a new bullet object */
		AbstractBaseProjectile* SpawnBullet(sf::Vector2f& _pos);

		#pragma endregion

	private:
		#pragma region Member Variables

		short allegiance;										/* Represents the friendly or hostile state of the projectiles that this weapon fires */
		float baseDamage;										/* Represents the base damage bonus for a projectile */
		float baseFireRate;										/* Represents the base fire rate this weapon is allowed to add projectiles to the munition container */
		float baseVelocity;										/* Represents the base velocity a projectile may travel at */
		sf::Uint32 weaponPattern;								/* This weapons current pattern */
		sf::Uint32 weaponDamageState;							/* A state which determines bonus damage of projectile shots */
		sf::Uint32 weaponFireRateState;							/* A state which determines bonus fire rate of projectile shots */
		sf::Uint32 weaponVelocityRateState;						/* A state which determines bonus velocity rate of projectile shots */

		#pragma endregion
	};
}