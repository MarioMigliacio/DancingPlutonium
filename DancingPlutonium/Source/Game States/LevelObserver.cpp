#include "LevelObserver.h"

DancingPlutonium::LevelObserver::LevelObserver()
{
	EnemyShipContainer = std::vector<AbstractBaseUnit*>();
	EnemyProjectileContainer = std::vector<AbstractBaseProjectile*>();
}

DancingPlutonium::LevelObserver::~LevelObserver()
{
	ClearEnemyShipContainer();
	ClearEnemyProjectileContainer();
}

bool DancingPlutonium::LevelObserver::CheckForUnitToUnitCollision(PlutoniumShip& _player)
{
	if (EnemyShipContainer.size() > 0)
	{
		sf::Sprite npcUnit = sf::Sprite();
		sf::Sprite player = _player.GetSprite();

		for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
		{
			npcUnit = EnemyShipContainer[i]->GetSprite();

			if (Collision::BoundingBoxTest(player, npcUnit))
			{
				// issue here: player has 0 lives but is not disposed, so it is allowed to continue going invulnerable but isActive = false, so spam the life loss msg.
				// fix: need to have player getActive state, but is this really necessary? if player isActive = false it SHOULD be game over anyway.
				// do this logic some time
				if (!_player.IsInvulnerable())
				{
					// GetHealth returns the players current life, which is then dealt to him
					_player.TakeDamage(_player.GetHealth());

					std::cout << "You have lost One Life! You had " << _player.LivesRemaining() << " lives." << std::endl;

					_player.RemoveLife();
				}
				return true;
			}
		}
	}

	return false;
}

bool DancingPlutonium::LevelObserver::CheckForPlayerShotHit(std::vector<AbstractBaseProjectile*>& _playerBullets)
{
	if (EnemyShipContainer.size() > 0)
	{
		sf::Sprite npcUnit = sf::Sprite();
		std::vector<sf::Sprite> playerBullets = std::vector<sf::Sprite>();

		for (int i = 0; i < static_cast<int>(EnemyShipContainer.size()); i++)
		{
			npcUnit = EnemyShipContainer[i]->GetSprite();

			if (_playerBullets.size() > 0)
			{
				for (int j = 0; j < static_cast<int>(_playerBullets.size()); j++)
				{
					playerBullets = _playerBullets[j]->GetAllSprites();

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

bool DancingPlutonium::LevelObserver::CheckForEnemyShotHit(PlutoniumShip& _player)
{
	if (EnemyShipContainer.size() > 0)
	{
		std::vector<sf::Sprite> enemyBullets = std::vector<sf::Sprite>();
		sf::Sprite player = _player.GetSprite();

		for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
		{
			if (EnemyShipContainer[i]->GetActiveState())
			{
				auto allademeEnemybulletsMmHmm = EnemyShipContainer[i]->GetWeaponEquipped()->GetAmmunitionContainer();

				if (allademeEnemybulletsMmHmm.size() > 0)
				{
					// for every projectile in the enemy container.. 
					for (int j = static_cast<int>(allademeEnemybulletsMmHmm.size()) - 1; j >= 0; j--)
					{
						// get its component projectiles
						enemyBullets = allademeEnemybulletsMmHmm[j]->GetAllSprites();

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
	_unit1.TakeDamage(_unit2.GetDamage());
}

void DancingPlutonium::LevelObserver::EnemyUnitDeath(AbstractBaseUnit& _unit, PlutoniumShip& _player)
{
	_player.AddScore(_unit.GetValue());
}

void DancingPlutonium::LevelObserver::UpgradeUnitWeaponry(AbstractBaseUnit& _unit)
{
	_unit.GetWeaponEquipped()->UpgradeWeaponPattern();
}

void DancingPlutonium::LevelObserver::UpdateEnemyShipContainer(float _dt, sf::RenderTarget& _rt)
{
	for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
	{
		EnemyShipContainer[i]->Update(_dt, _rt);

		if (EnemyShipContainer[i]->GetActiveState() == false)
		{
			delete EnemyShipContainer[i];
			EnemyShipContainer.erase(EnemyShipContainer.begin() + i);
		}
	}
}

void DancingPlutonium::LevelObserver::DrawEnemyShipContainer(sf::RenderTarget& _rt)
{
	for (int i = 0; i <= static_cast<int>(EnemyShipContainer.size() - 1); i++)
	{
		EnemyShipContainer[i]->Draw(_rt);
	}
}

void DancingPlutonium::LevelObserver::ClearEnemyShipContainer()
{
	if (EnemyShipContainer.size() > 0)
	{
		for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
		{
			delete EnemyShipContainer[i];
			EnemyShipContainer.erase(EnemyShipContainer.begin() + i);
		}
	}
}

void DancingPlutonium::LevelObserver::ClearEnemyProjectileContainer()
{
	if (EnemyProjectileContainer.size() > 0)
	{
		for (int i = static_cast<int>(EnemyProjectileContainer.size() - 1); i >= 0; i--)
		{
			delete EnemyProjectileContainer[i];
			EnemyProjectileContainer.erase(EnemyProjectileContainer.begin() + i);
		}
	}
}