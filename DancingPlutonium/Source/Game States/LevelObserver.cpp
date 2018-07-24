#include "LevelObserver.h"
#include <iostream>

/* Static member variable for the observer to view enemy ship units */
std::vector<DancingPlutonium::AbstractBaseUnit*> DancingPlutonium::LevelObserver::enemyShipContainer;

/* Static member variable for the observer to view enemy ship projectiles */
std::vector<DancingPlutonium::AbstractBaseProjectile*> DancingPlutonium::LevelObserver::enemyProjectileContainer;

/* Static member variable for the observer to view player ship projectiles */
std::vector<DancingPlutonium::AbstractBaseProjectile*> DancingPlutonium::LevelObserver::playerProjectileContainer;

DancingPlutonium::LevelObserver::LevelObserver()
{
	enemyShipContainer = std::vector<AbstractBaseUnit*>();
	enemyProjectileContainer = std::vector<AbstractBaseProjectile*>();
	playerProjectileContainer = std::vector<AbstractBaseProjectile*>();
}

DancingPlutonium::LevelObserver::~LevelObserver()
{
	ClearEnemyShipContainer();
	ClearEnemyProjectileContainer();
	ClearPlayerProjectileContainer();
}

bool DancingPlutonium::LevelObserver::CheckForUnitToUnitCollision(AbstractBaseUnit& _player, std::vector<AbstractBaseUnit*>& _from)
{
	UpdateEnemyShipContainer(_from);

	if (enemyShipContainer.size() > 0)
	{
		sf::Sprite npcUnit = sf::Sprite();
		sf::Sprite player = _player.GetSprite();

		for (int i = static_cast<int>(enemyShipContainer.size() - 1); i >= 0; i--)
		{
			npcUnit = enemyShipContainer[i]->GetSprite();

			// FIXED! the abstract base unit's GetSprite() was not good enough! Had to have override capability to return the 'right' sprite object.

			if (Collision::BoundingBoxTest(player, npcUnit))
			{
				return true;
			}
		}
	}

	return false;
}

bool DancingPlutonium::LevelObserver::CheckForPlayerShotHit(std::vector<AbstractBaseUnit*>& _enemyUnit, std::vector<AbstractBaseProjectile*>& _playerBullets)
{
	UpdatePlayerProjectileContainer(_playerBullets);
	UpdateEnemyShipContainer(_enemyUnit);

	if (enemyShipContainer.size() > 0)
	{
		sf::Sprite npcUnit = sf::Sprite();
		std::vector<sf::Sprite> playerBullets = std::vector<sf::Sprite>();

		for (int i = 0; i < static_cast<int>(enemyShipContainer.size()); i++)
		{
			npcUnit = enemyShipContainer[i]->GetSprite();

			if (playerProjectileContainer.size() > 0)
			{
				for (int j = 0; j < static_cast<int>(playerProjectileContainer.size()); j++)
				{
					playerBullets = playerProjectileContainer[j]->GetAllSprites();

					if (playerBullets.size() > 0)
					{
						for (int k = 0; k < static_cast<int>(playerBullets.size()); k++)
						{
							if (Collision::BoundingBoxTest(npcUnit, playerBullets[k]))
							{
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool DancingPlutonium::LevelObserver::CheckForEnemyShotHit(std::vector<AbstractBaseUnit*>& _enemy, AbstractBaseUnit& _player)
{
	UpdateEnemyShipContainer(_enemy);

	if (enemyShipContainer.size() > 0)
	{
		std::vector<sf::Sprite> enemyBullets = std::vector<sf::Sprite>();
		sf::Sprite player = _player.GetSprite();

		for (int i = static_cast<int>(enemyShipContainer.size() - 1); i >= 0; i--)
		{
			if (enemyShipContainer[i]->GetActiveState())
			{
				// get that ships weapon container				
				auto allademeEnemybulletsMmHmm = enemyShipContainer[i]->GetWeaponEquipped()->GetAmmunitionContainer();
				UpdateEnemyProjectileContainer(allademeEnemybulletsMmHmm);

				if (enemyProjectileContainer.size() > 0)
				{
					// for every projectile in the enemy container.. 
					for (int j = static_cast<int>(enemyProjectileContainer.size()) - 1; j >= 0; j--)
					{
						// get its component projectiles
						enemyBullets = enemyProjectileContainer[j]->GetAllSprites();

						if (enemyBullets.size() > 0)
						{
							// for every component projectile, check if it intersects with US!
							for (int k = static_cast<int>(enemyBullets.size()) - 1; k >= 0; k--)
							{
								if (Collision::BoundingBoxTest(enemyBullets[k], player))
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}

void DancingPlutonium::LevelObserver::DoProjectileCollisionDamage(AbstractBaseUnit& _unit1, AbstractBaseProjectile& _unit2)
{
	_unit1.SetHealth(_unit2.GetDamage());
}

void DancingPlutonium::LevelObserver::EnemyUnitDeath(AbstractBaseUnit& _unit, PlutoniumShip& _player)
{
	_player.AddScore(_unit.GetValue());
}

void DancingPlutonium::LevelObserver::UpgradeUnitWeaponry(AbstractBaseUnit& _unit)
{
	_unit.GetWeaponEquipped()->UpgradeWeaponPattern();
}

void DancingPlutonium::LevelObserver::UpdateEnemyShipContainer(std::vector<AbstractBaseUnit*>& _from)
{
	ClearEnemyShipContainer();
	enemyShipContainer = _from;
}

void DancingPlutonium::LevelObserver::UpdateEnemyProjectileContainer(std::vector<AbstractBaseProjectile*>& _from)
{
	ClearEnemyProjectileContainer();
	enemyProjectileContainer = _from;
}

void DancingPlutonium::LevelObserver::UpdatePlayerProjectileContainer(std::vector<AbstractBaseProjectile*>& _from)
{
	ClearPlayerProjectileContainer();
	playerProjectileContainer = _from;
}

void DancingPlutonium::LevelObserver::ClearEnemyShipContainer()
{
	if (enemyShipContainer.size() > 0)
	{
		for (int i = static_cast<int>(enemyShipContainer.size() - 1); i >= 0; i--)
		{
			delete enemyShipContainer[i];
			enemyShipContainer.erase(enemyShipContainer.begin() + i);
		}
	}
}

void DancingPlutonium::LevelObserver::ClearEnemyProjectileContainer()
{
	if (enemyProjectileContainer.size() > 0)
	{
		for (int i = static_cast<int>(enemyProjectileContainer.size() - 1); i >= 0; i--)
		{
			delete enemyProjectileContainer[i];
			enemyProjectileContainer.erase(enemyProjectileContainer.begin() + i);
		}
	}
}

void DancingPlutonium::LevelObserver::ClearPlayerProjectileContainer()
{
	if (playerProjectileContainer.size() > 0)
	{
		for (int i = static_cast<int>(playerProjectileContainer.size() - 1); i >= 0; i--)
		{
			delete playerProjectileContainer[i];
			playerProjectileContainer.erase(playerProjectileContainer.begin() + i);
		}
	}
}
