#pragma once

#include <SFML\Graphics.hpp>
#include "BulletFactory.h"
#include "AbstractBaseProjectile.h"
#include "Enums.h"

namespace DancingPlutonium
{
	class Weapon
	{
	public:
		#pragma region Ctor / Dtor

		/* The Weapon default constructor */
		Weapon(const float _fireRate, short _allegiance);
		/* The Weapon default destructor */
		~Weapon();

		#pragma endregion
	public:
		#pragma region Ammunition Access

		/* Returns the projectile object at the index input parameter */
		AbstractBaseProjectile* GetIndexOfAmmunition(int _index);
		/* Returns the size of the projectile container for the units' Weapon */
		int GetSizeOfAmmunition();

		#pragma endregion
	public:
		#pragma region Methods

		/* Allow access to the pattern type this weapon will fire*/
		sf::Uint32 GetPattern();
		/* Upgrade this weapon objects Projectile Pattern to the next logical stage */
		void UpgradeWeaponPattern();
		/* Takes projectile damage to an increased logical state */
		void UpgradeWeaponDamage();
		/* Allows for the weapon to alter the fire rate of ammunition */
		void UpgradeWeaponFireRate();
		/* Takes projectile velocity to an increased logical state */
		void UpgradeWeaponVelocityRate();
		/* If time allows for a projectile to be fired, adds a projectile to the ammunition container for this weapon, 
		spawning a projectile from the _pos input parameter. Returns true if a projectile was able to be fired. */
		bool AddMunition(sf::Vector2f& _pos, float _dt);
		/* Calls for an update on every projectile object within the ammunition container of this weapon */
		void Update(sf::RenderTarget& _rt, float _dt);
		/* Calls for a draw on every projectile object within the ammunition container of this weapon */
		void Draw(sf::RenderTarget& _rt);

		#pragma endregion
	private:
		#pragma region Enumerations
		
		/* An enumeration particular to the weapon damage state */
		enum WeaponDamageState
		{
			d_Uninitialized,
			d_Normal,
			d_One,
			d_Two,
			d_Three,
			d_Four,
			d_Max
		};

		/* An enumeration particular to the weapon fire rate state */
		enum WeaponFireRateState
		{
			r_Uninitialized,
			r_Normal,
			r_One,
			r_Two,
			r_Three,
			r_Four,
			r_Max
		};

		/* An enumeration particular to the weapon velocity rate state */
		enum WeaponVelocityState
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
	private:
		#pragma region Extra Functionality

		/* Deletes newly created projectile objects from the ammunition vector, based on active states of each projectile */
		void CleanAmmunition(sf::RenderTarget& _rt);
		/* Initializes the projectile pattern, damage, firerate, accumulator, and the ammunition container for this weapon */
		void InitializeWeaponSystem(const float _fireRate);
		/* Allows for the weapon to alter the projectile shot damage */
		void SetWeaponDamageState(AbstractBaseProjectile* _shot);
		/* Allows for the weapon to alter the projectile velocity rate */
		void SetWeaponVelocityState(AbstractBaseProjectile* _shot);
		/* Alters the logic for the allegiance state for the input parameter projectile */
		void SetProjectileAllegiance(AbstractBaseProjectile* _shot);

		#pragma endregion
	private:
		#pragma region Member Variables

		std::vector<AbstractBaseProjectile*> ammunition;		/* Represents the container for the projectiles that this weapon object maintains */
		float fireRate;											/* Something used to space time between valid projectile shots */
		short allegiance;										/* test */
		float baseDamage;										/* test */
		float baseFireRate;										/* test */
		float baseVelocity;										/* test */
		static sf::Uint32 weaponPattern;						/* This weapons current pattern */
		static sf::Uint32 weaponDamageState;					/* A state which determines bonus damage of projectile shots */
		static sf::Uint32 weaponFireRateState;					/* A state which determines bonus fire rate of projectile shots */
		static sf::Uint32 weaponVelocityRateState;				/* A state which determines bonus velocity rate of projectile shots */

		#pragma endregion
	};
}