#include "LevelObserver.h"

DancingPlutonium::LevelObserver::LevelObserver()
{
	EnemyShipContainer = std::vector<AbstractBaseUnit*>();
	EnemyProjectileContainer = std::vector<AbstractBaseProjectile*>();
	PlayerProjectileContainer = std::vector<AbstractBaseProjectile*>();
}

DancingPlutonium::LevelObserver::~LevelObserver()
{
	ClearEnemyShipContainer();
	ClearEnemyProjectileContainer();
}

void DancingPlutonium::LevelObserver::CheckForUnitToUnitCollision(PlutoniumShip& _player)
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

					// DEBUG purposes
					std::cout << "You have lost One Life! You had " << _player.LivesRemaining() << " lives." << std::endl;

					_player.RemoveLife();
				}
			}
		}
	}
}

// will need to incorporate allegiance checks on projectiles, if we are going to just use the one container for all bullets, player and enemies
void DancingPlutonium::LevelObserver::CheckForPlayerShotHit(PlutoniumShip& _player)
{
	if (PlayerProjectileContainer.size() > 0)
	{
		sf::Sprite npcUnit = sf::Sprite();
		std::vector<AbstractBaseProjectile*> projectileComponents = std::vector<AbstractBaseProjectile*>();

		if (EnemyShipContainer.size() > 0)
		{
			for (int i = 0; i < static_cast<int>(EnemyShipContainer.size()); i++)
			{
				// we need to use sprites for the collision logic, it is the most efficient way outside of something magical
				npcUnit = EnemyShipContainer[i]->GetSprite();

				for (int j = 0; j < static_cast<int>(PlayerProjectileContainer.size()); j++)
				{
					// we need to use sprites for the collision logic, it is the most efficient way outside of something magical
					projectileComponents = PlayerProjectileContainer[j]->GetAllComponentBullets();

					if (projectileComponents.size() > 0)
					{
						for (int k = 0; k < static_cast<int>(projectileComponents.size()); k++)
						{
							// Check projectiles to enemies
							if (Collision::BoundingBoxTest(npcUnit, projectileComponents[k]->GetSprite()) && !projectileComponents[k]->IsInnert() &&
								projectileComponents[k]->GetAllegiance() != EnemyShipContainer[i]->GetAllegiance())
							{
								if (!EnemyShipContainer[i]->IsInvulnerable())
								{
									// a bullet hit an enemy, so we need to disable it's damage in the many frames that it is colliding.
									projectileComponents[k]->RenderInnert();

									// if an enemy unit dies, before rendering it as Inactive, add its score to our player!
									if (EnemyShipContainer[i]->GetHealth() <= projectileComponents[k]->GetDamage())
									{
										EnemyUnitDeath(*EnemyShipContainer[i], _player);
										// DEBUG purposes
										std::cout << "KILLSHOT: player score is currently: " << _player.GetScore() << "!" << std::endl;
									}

									// otherwise, hurt the enemy unit
									EnemyShipContainer[i]->TakeDamage(projectileComponents[k]->GetDamage());

									// DEBUG purposes
									std::cout << "An enemy unit took " << projectileComponents[k]->GetDamage() << " damage!" << std::endl;
								}

								return;
							}
						}
					}
				}
				
			}
		}
	}
}

void DancingPlutonium::LevelObserver::CheckForEnemyShotHit(PlutoniumShip& _player)
{
	if (EnemyProjectileContainer.size() > 0)
	{
		sf::Sprite player = _player.GetSprite();
		std::vector<AbstractBaseProjectile*> projectileComponents = std::vector<AbstractBaseProjectile*>();

		for (int j = 0; j < static_cast<int>(EnemyProjectileContainer.size()); j++)
		{
			// we need to use sprites for the collision logic, it is the most efficient way outside of something magical
			projectileComponents = EnemyProjectileContainer[j]->GetAllComponentBullets();

			for (int k = 0; k < static_cast<int>(projectileComponents.size()); k++)
			{
				// Check projectiles to player
				if (Collision::BoundingBoxTest(player, projectileComponents[k]->GetSprite()) && !projectileComponents[k]->IsInnert() &&
					projectileComponents[k]->GetAllegiance() != _player.GetAllegiance())
				{
					if (!_player.IsInvulnerable())
					{
						// a bullet hit us, so we need to disable it's damage in the many frames that it is colliding.
						projectileComponents[k]->RenderInnert();

						// if an we die remove a life to our player!
						if (_player.GetHealth() <= projectileComponents[k]->GetDamage())
						{
							_player.RemoveLife();
							// DEBUG purposes
							std::cout << "YOU DIED! YOU HAVE " << _player.LivesRemaining() << " LIVES REMAINING" << std::endl;
						}

						// otherwise take some damage
						_player.TakeDamage(projectileComponents[k]->GetDamage());

						// DEBUG purposes
						std::cout << "You took " << projectileComponents[k]->GetDamage() <<
							" damage! You now have " << _player.GetHealth() << " health!" << std::endl;
					}

					return;
				}
			}
		}			
		
	}
}

void DancingPlutonium::LevelObserver::DoProjectileCollisionDamage(AbstractBaseUnit& _unit1, AbstractBaseProjectile& _unit2)
{
	_unit1.TakeDamage(_unit2.GetDamage());
}

void DancingPlutonium::LevelObserver::SpawnEnemyUnit(sf::RenderTarget& _rt)
{
	auto u = new BasicShip(_rt);
	u->SpawnRandomly(_rt);
	EnemyShipContainer.push_back(u);
}

void DancingPlutonium::LevelObserver::SpawnEnemyWave(sf::RenderTarget& _rt)
{
}

void DancingPlutonium::LevelObserver::EnemyUnitDeath(AbstractBaseUnit& _unit, PlutoniumShip& _player)
{
	_player.AddScore(_unit.GetValue());
}

void DancingPlutonium::LevelObserver::UpgradeUnitWeaponry(AbstractBaseUnit& _unit)
{
	_unit.GetWeaponEquipped()->UpgradeWeaponPattern();
}

void DancingPlutonium::LevelObserver::Update(sf::RenderTarget& _rt, float _dt, PlutoniumShip& _player)
{
	// push back bullets fired by us if we are allowed to do so
	if (_player.IsFiringBullet())
	{
		_player.ToggleFiring();
		auto b = _player.Shoot();
		PlayerProjectileContainer.push_back(b);
	}

	CleanEnemyShips();

	// Update the EnemyShipContainer
	if (EnemyShipContainer.size() > 0)
	{
		for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
		{
			EnemyShipContainer[i]->Update(_dt, _rt);
			
			// push back bullets fired by an enemy unit that is allowed to do so
			if (EnemyShipContainer[i]->IsFiringBullet())
			{
				EnemyShipContainer[i]->ToggleFiring();
				auto b = EnemyShipContainer[i]->Shoot();
				EnemyProjectileContainer.push_back(b);
			}
		}
	}

	CleanAmmunition(_rt);

	// Update the EnemyProjectileContainer
	if (EnemyProjectileContainer.size() != 0)
	{		
		for (int i = 0; i < static_cast<int>(EnemyProjectileContainer.size()); i++)
		{	
			if (EnemyProjectileContainer[i]->IsInnert() == false)
			{
				EnemyProjectileContainer[i]->Update(_dt);
			}
						
		}
	}

	CleanPlayerAmmunition(_rt);

	// Update the PlayerProjectileContainer
	if (PlayerProjectileContainer.size() != 0)
	{
		for (int i = 0; i < static_cast<int>(PlayerProjectileContainer.size()); i++)
		{
			if (PlayerProjectileContainer[i]->IsInnert() == false)
			{
				PlayerProjectileContainer[i]->Update(_dt);
			}			
		}
	}

	// Perform collision detection
	CheckForUnitToUnitCollision(_player);
	CheckForPlayerShotHit(_player);
	CheckForEnemyShotHit(_player);
}

void DancingPlutonium::LevelObserver::Draw(sf::RenderTarget& _rt)
{
	// Draw the EnemyShipContainer
	for (int i = 0; i <= static_cast<int>(EnemyShipContainer.size() - 1); i++)
	{
		EnemyShipContainer[i]->Draw(_rt);
	}

	// Draw the Player Projectiles
	for (int i = 0; i < static_cast<int>(PlayerProjectileContainer.size()); i++)
	{
		PlayerProjectileContainer[i]->Draw(_rt);
	}
	
	// Draw the Enemy Projectiles
	for (int i = 0; i < static_cast<int>(EnemyProjectileContainer.size()); i++)
	{
		EnemyProjectileContainer[i]->Draw(_rt);
	}
}

void DancingPlutonium::LevelObserver::CleanEnemyShips()
{
	if (EnemyShipContainer.size() > 0)
	{
		for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
		{
			if (EnemyShipContainer[i]->GetActiveState() == false)
			{
				delete EnemyShipContainer[i];
				EnemyShipContainer.erase(EnemyShipContainer.begin() + i);
			}
		}
	}
}

void DancingPlutonium::LevelObserver::CleanAmmunition(sf::RenderTarget& _rt)
{
	if (EnemyProjectileContainer.size() > 0)
	{
		for (int i = static_cast<int>(EnemyProjectileContainer.size() - 1); i >= 0; i--)
		{
			if (EnemyProjectileContainer[i]->GetActiveState(_rt) == false ||
				EnemyProjectileContainer[i]->IsInnert())
			{
				delete EnemyProjectileContainer[i];
				EnemyProjectileContainer.erase(EnemyProjectileContainer.begin() + i);
			}
		}
	}
}

void DancingPlutonium::LevelObserver::CleanPlayerAmmunition(sf::RenderTarget& _rt)
{
	if (PlayerProjectileContainer.size() > 0)
	{
		for (int i = static_cast<int>(PlayerProjectileContainer.size() - 1); i >= 0; i--)
		{
			if (PlayerProjectileContainer[i]->GetActiveState(_rt) == false ||
				PlayerProjectileContainer[i]->IsInnert())
			{
				delete PlayerProjectileContainer[i];
				PlayerProjectileContainer.erase(PlayerProjectileContainer.begin() + i);
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
