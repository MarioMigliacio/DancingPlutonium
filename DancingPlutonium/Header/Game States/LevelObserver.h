#pragma once

#include <SFML\Graphics.hpp>
#include "AbstractBaseUnit.h"
#include "Collision.h"
#include "PlutoniumShip.h"

namespace DancingPlutonium
{
	/* The level object represents an observer that takes in units and players positions and projectiles and manages important game states. */
	class LevelObserver
	{
	private:
		LevelObserver();

	public:
		~LevelObserver();

		static bool CheckForUnitToUnitCollision(AbstractBaseUnit& _player, std::vector<AbstractBaseUnit*>& _from);
		static bool CheckForPlayerShotHit(std::vector<AbstractBaseUnit*>& _enemy, std::vector<AbstractBaseProjectile*>& _playerBullet);
		static bool CheckForEnemyShotHit(std::vector<AbstractBaseUnit*>& _enemy, AbstractBaseUnit& _player);
		static void DoProjectileCollisionDamage(AbstractBaseUnit& _unit, AbstractBaseProjectile& _object2);
		static void EnemyUnitDeath(AbstractBaseUnit& _unit, PlutoniumShip& _player);
		static void UpgradeUnitWeaponry(AbstractBaseUnit& _unit);
		static void UpdateEnemyShipContainer(std::vector<AbstractBaseUnit*>& _from);
		static void UpdateEnemyProjectileContainer(std::vector<AbstractBaseProjectile*>& _from);
		static void UpdatePlayerProjectileContainer(std::vector<AbstractBaseProjectile*>& _from);

	private:
		static void ClearEnemyShipContainer();
		static void ClearEnemyProjectileContainer();
		static void ClearPlayerProjectileContainer();

	private:
		static std::vector<AbstractBaseUnit*> enemyShipContainer;
		static std::vector<AbstractBaseProjectile*> enemyProjectileContainer;
		static std::vector<AbstractBaseProjectile*> playerProjectileContainer;
	};
}