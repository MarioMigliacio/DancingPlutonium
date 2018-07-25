#pragma once

#include <SFML\Graphics.hpp>
#include "AbstractBaseUnit.h"
#include "Collision.h"
#include "PlutoniumShip.h"

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

		bool CheckForUnitToUnitCollision(AbstractBaseUnit& _player, std::vector<AbstractBaseUnit*>& _from);
		bool CheckForPlayerShotHit(std::vector<AbstractBaseUnit*>& _enemy, std::vector<AbstractBaseProjectile*>& _playerBullet);
		bool CheckForEnemyShotHit(std::vector<AbstractBaseUnit*>& _enemy, AbstractBaseUnit& _player);
		void DoProjectileCollisionDamage(AbstractBaseUnit& _unit, AbstractBaseProjectile& _object2);
		void EnemyUnitDeath(AbstractBaseUnit& _unit, PlutoniumShip& _player);
		void UpgradeUnitWeaponry(AbstractBaseUnit& _unit);
		void UpdateEnemyShipContainer(float dt, sf::RenderTarget& _rt);

		#pragma endregion

	public:
		#pragma region Container Member Variables

		std::vector<AbstractBaseUnit*> EnemyShipContainer;
		std::vector<AbstractBaseProjectile*> EnemyProjectileContainer;

		#pragma endregion

	private:
		#pragma region Container Functionality

		void ClearEnemyShipContainer();
		void ClearEnemyProjectileContainer();

		#pragma endregion
	};
}