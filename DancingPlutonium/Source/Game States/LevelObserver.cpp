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
		auto npcUnit = sf::Sprite();
		auto player = _player.GetSprite();

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

bool DancingPlutonium::LevelObserver::CheckForPlayerShotHit(std::vector<AbstractBaseProjectile*>& _playerBullets, PlutoniumShip& _player)
{
	if (EnemyShipContainer.size() > 0)
	{
		auto npcUnit = sf::Sprite();
		auto playerBullets = std::vector<sf::Sprite>();
		auto projectileComponents = std::vector<AbstractBaseProjectile*>();

		for (int i = 0; i < static_cast<int>(EnemyShipContainer.size()); i++)
		{
			npcUnit = EnemyShipContainer[i]->GetSprite();

			if (_playerBullets.size() > 0)
			{
				for (int j = 0; j < static_cast<int>(_playerBullets.size()); j++)
				{
					playerBullets = _playerBullets[j]->GetAllSprites();
					projectileComponents = _playerBullets[j]->GetAllComponentBullets();

					//if (playerBullets.size() > 0)
					if (projectileComponents.size() > 0)
					{
						//for (int k = 0; k < static_cast<int>(playerBullets.size()); k++)
						for (int k = 0; k < static_cast<int>(projectileComponents.size()); k++)
						{
							//if (Collision::BoundingBoxTest(npcUnit, playerBullets[k]) && !_playerBullets[j]->IsInnert())
							if (Collision::BoundingBoxTest(npcUnit, projectileComponents[k]->GetSprite()) && !_playerBullets[j]->IsInnert())
							{
								if (!EnemyShipContainer[i]->IsInvulnerable())
								{
									// a bullet hit an enemy, so we need to disable it's damage in the many frames that it is colliding.
									projectileComponents[k]->RenderInnert();

									// if an enemy unit dies, before rendering it as Inactive, add its score to our player!
									if (EnemyShipContainer[i]->GetHealth() <= projectileComponents[k]->GetDamage())
									{
										EnemyUnitDeath(*EnemyShipContainer[i], _player);
										std::cout << "player score is currently: " << _player.GetScore() << "!" << std::endl;
									}

									EnemyShipContainer[i]->TakeDamage(projectileComponents[k]->GetDamage());

									std::cout << "An enemy unit took " << projectileComponents[k]->GetDamage() << " damage!" << std::endl;
								}

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
	//if (EnemyShipContainer.size() > 0)
	//{
	//	std::vector<sf::Sprite> enemyBullets = std::vector<sf::Sprite>();
	//	sf::Sprite player = _player.GetSprite();

	//	for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
	//	{
	//		if (EnemyShipContainer[i]->GetActiveState())
	//		{
	//			auto allademeEnemybulletsMmHmm = EnemyShipContainer[i]->GetWeaponEquipped()->GetAmmunitionContainer();

	//			if (allademeEnemybulletsMmHmm.size() > 0)
	//			{
	//				// for every projectile in the enemy container.. 
	//				for (int j = static_cast<int>(allademeEnemybulletsMmHmm.size()) - 1; j >= 0; j--)
	//				{
	//					// get its component projectiles
	//					enemyBullets = allademeEnemybulletsMmHmm[j]->GetAllSprites();

	//					if (enemyBullets.size() > 0)
	//					{
	//						// for every component projectile, check if it intersects with US!
	//						for (int k = static_cast<int>(enemyBullets.size()) - 1; k >= 0; k--)
	//						{
	//							if (Collision::BoundingBoxTest(enemyBullets[k], player))
	//							{
	//								return true;
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

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

/// This is where a lot of testing is going to be needed.
void DancingPlutonium::LevelObserver::Update(sf::RenderTarget& _rt, float _dt, PlutoniumShip& _player)
{
	// push back bullets fired by us if we are allowed to do so
	if (_player.IsFiringBullet())
	{
		_player.ToggleFiring();
		auto b = _player.Shoot();
		EnemyProjectileContainer.push_back(b);
	}

	// Update the EnemyShipContainer
	for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
	{
		EnemyShipContainer[i]->Update(_dt, _rt);

		if (EnemyShipContainer[i]->GetActiveState() == false)
		{
			delete EnemyShipContainer[i];
			EnemyShipContainer.erase(EnemyShipContainer.begin() + i);
		}

		// push back bullets fired by an enemy unit that is allowed to do so
		if (EnemyShipContainer[i]->IsFiringBullet())
		{
			EnemyShipContainer[i]->ToggleFiring();
			auto b = EnemyShipContainer[i]->Shoot();
			EnemyProjectileContainer.push_back(b);
		}
	}

	// Update the ProjectileContainer
	if (EnemyProjectileContainer.size() != 0)
	{
		CleanAmmunition(_rt);
		
		for (int i = 0; i < static_cast<int>(EnemyProjectileContainer.size()); i++)
		{
			// represents the bullet collection that a single bullet object may be responsible for (multi shot, etc..)
			auto tempStorage = std::vector<AbstractBaseProjectile*>();
					
			for (int j = 0; j < static_cast<int>(EnemyProjectileContainer[i]->GetAllComponentBullets().size()); j++)
			{
				tempStorage = EnemyProjectileContainer[i]->GetAllComponentBullets();
		
				if (tempStorage[j]->IsInnert() == false)
				{
					EnemyProjectileContainer[i]->Update(_dt);
				}
			}			
		}
	}
}

void DancingPlutonium::LevelObserver::Draw(sf::RenderTarget & _rt)
{
	// Draw the EnemyShipContainer
	for (int i = 0; i <= static_cast<int>(EnemyShipContainer.size() - 1); i++)
	{
		EnemyShipContainer[i]->Draw(_rt);
	}

	// represents the bullet collection that a single bullet object may be responsible for
	auto tempStorage = std::vector<AbstractBaseProjectile*>();
	
	for (int i = 0; i < static_cast<int>(EnemyProjectileContainer.size()); i++)
	{
		tempStorage = EnemyProjectileContainer[i]->GetAllComponentBullets();
			
		for (int j = 0; j < static_cast<int>(EnemyProjectileContainer[i]->GetAllComponentBullets().size()); j++)
		{
			if (tempStorage[j]->IsInnert() == false)
			{
				tempStorage[j]->Draw(_rt);
			}
		}
	}
}

void DancingPlutonium::LevelObserver::CleanAmmunition(sf::RenderTarget& _rt)
{
	if (EnemyProjectileContainer.size() > 0)
	{
		// backwards iterators for vectors more efficient
		for (int i = static_cast<int>(EnemyProjectileContainer.size() - 1); i >= 0; i--)
		{
			if (EnemyProjectileContainer[i]->GetActiveState(_rt) == false)
			{
				delete EnemyProjectileContainer[i];
				EnemyProjectileContainer.erase(EnemyProjectileContainer.begin() + i);
			}
		}
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
