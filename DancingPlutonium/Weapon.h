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
		/* Allow access to the pattern type this weapon wwill fire*/
		sf::Uint32 GetPattern();
		/* Upgrade this weapon objects Projectile Pattern to the next logical stage */
		void UpgradeWeaponry();
		/* Adds a projectile to the ammunition container for this weapon, spawning a projectile from the _pos input parameter */
		void AddMunition(sf::Vector2f& _pos);
		/* Calls for an update on every projectile object within the ammunition container of this weapon */
		void Update(sf::RenderTarget& _rt, float _dt);
		/* Calls for a draw on every projectile object within the ammunition container of this weapon */
		void Draw(sf::RenderTarget& _rt);

		void InitializeWeaponry();
		
		#pragma endregion
	private:
		#pragma region Cleanup

		/* Deletes newly created projectile objects from the ammunition vector, based on active states of each projectile */
		void CleanAmmunition(sf::RenderTarget& _rt);

		#pragma endregion

		#pragma region Member Variables

		std::vector<Projectile*> ammunition;	/* Represents the container for the projectiles that this weapon object maintains */
		float accumulator;						/* Something used to calculate time distances */
		static sf::Uint32 weaponPattern;		/* This weapons current pattern */

		#pragma endregion
	};
}