#pragma once

#include <SFML\Graphics.hpp>
#include "AbstractBaseUnit.h"
#include "Collision.h"
#include "PlutoniumShip.h"
#include <iostream>

namespace DancingPlutonium
{
	/* The LevelObserver object represents an observer that takes in units and players positions and projectiles and manages important game states. */
	class LevelObserver
	{
	public:
		#pragma region Ctor/Dtors

		/* LevelObserver default constructor */
		LevelObserver();
		/* LevelObserver copy constructor */
		LevelObserver(const LevelObserver& _ref) {}
		/* LevelObserver destructor */
		~LevelObserver();

		#pragma endregion

	public:
		#pragma region Basic Level Functionality

		
		/* Returns true if a collision occurs between any units contained in the EnemyShipContainer container and the _playerBullets container, false otherwise. */
		void CheckForPlayerShotHit(PlutoniumShip& _player);
		/* Returns true if a collision occurs between any projectiles within the EnemyShipContainer container and the _player, false otherwise. */
		void CheckForEnemyShotHit(PlutoniumShip& _player);
		/* Once a collision has occured, Object2 deals damage to Unit1. */
		void DoProjectileCollisionDamage(AbstractBaseUnit& _unit1, AbstractBaseProjectile& _object2);
		/* Once an enemy unit has been destroyed by combat, add the score of the _unit to the player. */
		void EnemyUnitDeath(AbstractBaseUnit& _unit, PlutoniumShip& _player);
		/* Perform a weapon upgrade on the _unit in question. */
		void UpgradeUnitWeaponry(AbstractBaseUnit& _unit);
		/* Call for an update on our LevelObserver object. */
		void Update(sf::RenderTarget& _rt, float _dt, PlutoniumShip& _player);
		/* Call to Draw our LevelObserver components to the render target. */
		void Draw(sf::RenderTarget& _rt);
		/* Clean up enemy ships which have become Inactive */
		void CleanEnemyShips();
		/* Clean up projectiles which have become Inactive */
		void CleanAmmunition(sf::RenderTarget& _rt);
		/* Clean up projectiles which have become Inactive */
		void CleanPlayerAmmunition(sf::RenderTarget& _rt);

		#pragma endregion

	public:
		#pragma region Container Member Variables

		/* A container which holds pointers to observable enemy units. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseUnit*> EnemyShipContainer;
		/* A container which holds pointers to the projectiles of enemy units. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseProjectile*> EnemyProjectileContainer;
		/* A container which holds pointers to the projectiles of the player. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseProjectile*> PlayerProjectileContainer;

		#pragma endregion

	private:
		#pragma region Private Functionality

		/* Returns true if a collision occurs between _player and any units contained in the _enemyUnits container, false otherwise. */
		void CheckForUnitToUnitCollision(PlutoniumShip& _player);
		/* Disposes of memory within the EnemyShipContainer vector. */
		void ClearEnemyShipContainer();
		/* Disposes of memory within the EnemyProjectileContainer vector. */
		void ClearEnemyProjectileContainer();

		#pragma endregion
	};
}