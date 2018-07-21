#pragma once

#include <SFML\Graphics.hpp>
#include "AbstractBaseUnit.h"
#include "PlutoniumShip.h"
#include "Collision.h"

namespace DancingPlutonium
{
	/* The level object represents an observer that takes in units and players positions and projectiles and manages important game states. */
	class Level
	{
	private:
		Level() {}

	public:
		~Level() {}

		bool CheckForCollision(const sf::Sprite& _object1, const sf::Sprite& _object2);
		void DoUnitCollisionDamage(AbstractBaseUnit& _unit1, AbstractBaseUnit& _unit2);
		void DoProjectileCollisionDamage(AbstractBaseUnit& _unit, AbstractBaseProjectile& _object2);
		void EnemyUnitDeath(AbstractBaseUnit& _unit, AbstractBaseUnit& _player);
		void PlayerLoseLife(PlutoniumShip& _unit);
		void PlayerGainLife(PlutoniumShip& _unit);
		void UpdateEnemyShipContainer(std::vector<AbstractBaseUnit*>& _from);
		void UpdatePlayerShipContainer(std::vector<AbstractBaseUnit*>& _from);
		void UpdateEnemyProjectileContainer(std::vector<AbstractBaseProjectile*>& _from);
		void UpdatePlayerProjectileContainer(std::vector<AbstractBaseProjectile*>& _from);

		void Update(float _dt, sf::RenderTarget& _rt);
		void Draw(sf::RenderTarget& _rt);
	private:
		std::vector<AbstractBaseUnit*> enemyShipContainer;
		std::vector<AbstractBaseUnit*> playerShipContainer;
		std::vector<AbstractBaseProjectile*> enemyProjectileContainer;
		std::vector<AbstractBaseProjectile*> playerProjectileContainer;
	};
}