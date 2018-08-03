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

		/* Returns true if a collision occurs between _player and any units contained in the _enemyUnits container, false otherwise. */
		bool CheckForUnitToUnitCollision(PlutoniumShip& _player);
		/* Returns true if a collision occurs between any units contained in the EnemyShipContainer container and the _playerBullets container, false otherwise. */
		bool CheckForPlayerShotHit(std::vector<AbstractBaseProjectile*>& _playerBullet);
		/* Returns true if a collision occurs between any projectiles within the EnemyShipContainer container and the _player, false otherwise. */
		bool CheckForEnemyShotHit(PlutoniumShip& _player);
		/* Once a collision has occured, Object2 deals damage to Unit1. */
		void DoProjectileCollisionDamage(AbstractBaseUnit& _unit1, AbstractBaseProjectile& _object2);
		/* Once an enemy unit has been destroyed by combat, add the score of the _unit to the player. */
		void EnemyUnitDeath(AbstractBaseUnit& _unit, PlutoniumShip& _player);
		/* Perform a weapon upgrade on the _unit in question. */
		void UpgradeUnitWeaponry(AbstractBaseUnit& _unit);
		/* Call for an update on the units contained within the EnemyShipContainer. */
		void UpdateEnemyShipContainer(float dt, sf::RenderTarget& _rt);
		/* Call for a draw on the units contained within the EnemyShipContainer. */
		void DrawEnemyShipContainer(sf::RenderTarget& _rt);

		#pragma endregion

	public:
		#pragma region Container Member Variables

		/* A container which holds pointers to observable enemy units. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseUnit*> EnemyShipContainer;
		/* A container which holds pointers to the projectiles of enemy units. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseProjectile*> EnemyProjectileContainer;

		#pragma endregion

	private:
		#pragma region Container Functionality

		/* Disposes of memory within the EnemyShipContainer vector. */
		void ClearEnemyShipContainer();
		/* Disposes of memory within the EnemyProjectileContainer vector. */
		void ClearEnemyProjectileContainer();

		#pragma endregion
	};
}