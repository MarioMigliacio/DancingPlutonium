#pragma once

#include <SFML\Graphics.hpp>
#include "BulletFactory.h"
#include "Projectile.h"
#include "Enums.h"

namespace DancingPlutonium
{
	class Weapon
	{
	public:
		#pragma region Ctor / Dtor

		/* The Weapon default constructor */
		Weapon();
		/* The Weapon default destructor */
		~Weapon();

		#pragma endregion
	public:
		#pragma region Ammunition Access

		/* Returns the projectile object at the index input parameter */
		Projectile* GetIndexOfAmmunition(int _index);
		/* Returns the size of the projectile container for the units' Weapon */
		int GetSizeOfAmmunition();

		#pragma endregion
	public:
		#pragma region Methods

		/* Sets the Projectile Pattern based on the _wepPattern input parameter for this weapon */
		void SetPattern(ProjectilePattern _wepPattern);
		/* Allow access to the pattern type this weapon will fire*/
		sf::Uint32 GetPattern();
		/* Upgrade this weapon objects Projectile Pattern to the next logical stage */
		void UpgradeWeaponPattern();
		/* Takes projectile damage to an increased logical state */
		void UpgradeWeaponDamage();
		/* If time allows for a projectile to be fired, adds a projectile to the ammunition container for this weapon, 
		spawning a projectile from the _pos input parameter. Returns 0.0f if a projectile was able to be fired. */
		float AddMunition(sf::Vector2f& _pos, float _dt);
		/* Calls for an update on every projectile object within the ammunition container of this weapon */
		void Update(sf::RenderTarget& _rt, float _dt);
		/* Calls for a draw on every projectile object within the ammunition container of this weapon */
		void Draw(sf::RenderTarget& _rt);
		
		
		#pragma endregion
	private:
		#pragma region
		
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

		#pragma endregion
	private:
		#pragma region Cleanup

		/* Deletes newly created projectile objects from the ammunition vector, based on active states of each projectile */
		void CleanAmmunition(sf::RenderTarget& _rt);
		/* Initializes the projectile pattern, damage, firerate, accumulator, and the ammunition container for this weapon */
		void InitializeWeaponSystem();
		/* Allows for the weapon to alter the projectile shot damage */
		void SetWeaponDamageState(Projectile* _shot);
		/* Allows for the weapon to alter the fire rate of ammunition */
		void SetWeaponFireRate();

		#pragma endregion

		#pragma region Member Variables

		std::vector<Projectile*> ammunition;	/* Represents the container for the projectiles that this weapon object maintains */
		float accumulator;						/* Something used to calculate time distances */
		float fireRate;							/* Something used to space time between valid projectile shots */
		static sf::Uint32 weaponPattern;		/* This weapons current pattern */
		static sf::Uint32 weaponDamageState;	/* A state which determines bonus damage of projectile shots */
		static sf::Uint32 weaponFireRateState;	/* A state which determines bonus fire rate of projectile shots */

		#pragma endregion
	};
}