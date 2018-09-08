#include "LevelObserver.h"

DancingPlutonium::LevelObserver::LevelObserver(PlutoniumShip& _player) : _playerRef(_player)
{
	EnemyShipContainer = std::vector<AbstractBaseUnit*>();
	EnemyProjectileContainer = std::vector<AbstractBaseProjectile*>();
	PlayerProjectileContainer = std::vector<AbstractBaseProjectile*>();
	ItemTokens = std::vector<ItemToken*>();
	BombContainer = std::vector<Bomb*>();
}

DancingPlutonium::LevelObserver::~LevelObserver()
{
	ClearEnemyShipContainer();
	ClearEnemyProjectileContainer();
	ClearPlayerProjectileContainer();
	ClearItemTokens();
	ClearBombs();
}

void DancingPlutonium::LevelObserver::CheckForBombCollision()
{
	if (BombContainer.size() > 0)
	{
		for (int i = static_cast<int>(BombContainer.size() - 1); i >= 0; i--)
		{
			if (BombContainer[i]->IsExploding())
			{
				if (EnemyShipContainer.size() > 0)
				{
					for (int j = static_cast<int>(EnemyShipContainer.size() - 1); j >= 0; j--)
					{
						if (Collision::BoundingBoxTest(EnemyShipContainer[j]->GetSprite(), BombContainer[i]->GetSprite()))
						{
							// GetHealth returns the players current life, which is then dealt to him
							EnemyShipContainer[j]->TakeDamage(BombContainer[i]->GetDamagePerFrame());

							// DEBUG purposes
							std::cout << "ENEMY IN BLAST RADIUS! taking " << BombContainer[i]->GetDamagePerFrame() << " Damage per tick!" << std::endl;
						}
					}
				}
			}
		}
	}
}

void DancingPlutonium::LevelObserver::CheckForUnitToUnitCollision()
{
	if (EnemyShipContainer.size() > 0)
	{
		for (int i = static_cast<int>(EnemyShipContainer.size() - 1); i >= 0; i--)
		{
			if (Collision::BoundingBoxTest(_playerRef.GetSprite(), EnemyShipContainer[i]->GetSprite()))
			{
				// issue here: player has 0 lives but is not disposed, so it is allowed to continue going invulnerable but isActive = false, so spam the life loss msg.
				// fix: need to have player getActive state, but is this really necessary? if player isActive = false it SHOULD be game over anyway.
				// do this logic some time
				if (!_playerRef.IsInvulnerable())
				{
					// GetHealth returns the players current life, which is then dealt to him
					_playerRef.TakeDamage(_playerRef.GetHealth());

					// DEBUG purposes
					std::cout << "You have lost One Life! You had " << _playerRef.LivesRemaining() << " lives." << std::endl;

					_playerRef.RemoveLife();
				}
			}
		}
	}
}

// will need to incorporate allegiance checks on projectiles, if we are going to just use the one container for all bullets, player and enemies
void DancingPlutonium::LevelObserver::CheckForPlayerShotHit()
{
	if (PlayerProjectileContainer.size() > 0)
	{
		std::vector<AbstractBaseProjectile*> projectileComponents = std::vector<AbstractBaseProjectile*>();

		if (EnemyShipContainer.size() > 0)
		{
			for (int i = 0; i < static_cast<int>(EnemyShipContainer.size()); i++)
			{
				for (int j = 0; j < static_cast<int>(PlayerProjectileContainer.size()); j++)
				{
					projectileComponents = PlayerProjectileContainer[j]->GetAllComponentBullets();

					if (projectileComponents.size() > 0)
					{
						for (int k = 0; k < static_cast<int>(projectileComponents.size()); k++)
						{
							// Check projectiles to enemies
							if (Collision::BoundingBoxTest(EnemyShipContainer[i]->GetSprite(), projectileComponents[k]->GetSprite()) && !projectileComponents[k]->IsInnert() &&
								projectileComponents[k]->GetAllegiance() != EnemyShipContainer[i]->GetAllegiance())
							{
								if (!EnemyShipContainer[i]->IsInvulnerable())
								{
									// a bullet hit an enemy, so we need to disable it's damage in the many frames that it is colliding.
									projectileComponents[k]->RenderInnert();

									// if an enemy unit dies, before rendering it as Inactive, add its score to our player!
									if (EnemyShipContainer[i]->GetHealth() <= projectileComponents[k]->GetDamage())
									{
										EnemyUnitDeath(*EnemyShipContainer[i]);
										// DEBUG purposes
										std::cout << "KILLSHOT: player score is currently: " << _playerRef.GetScore() << "!" << std::endl;
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

void DancingPlutonium::LevelObserver::CheckForEnemyShotHit()
{
	if (EnemyProjectileContainer.size() > 0)
	{
		std::vector<AbstractBaseProjectile*> projectileComponents = std::vector<AbstractBaseProjectile*>();

		for (int j = 0; j < static_cast<int>(EnemyProjectileContainer.size()); j++)
		{
			// we need to use sprites for the collision logic, it is the most efficient way outside of something magical
			projectileComponents = EnemyProjectileContainer[j]->GetAllComponentBullets();

			for (int k = 0; k < static_cast<int>(projectileComponents.size()); k++)
			{
				// Check projectiles to player
				if (Collision::BoundingBoxTest(_playerRef.GetSprite(), projectileComponents[k]->GetSprite()) && !projectileComponents[k]->IsInnert() &&
					projectileComponents[k]->GetAllegiance() != _playerRef.GetAllegiance())
				{
					if (!_playerRef.IsInvulnerable())
					{
						// a bullet hit us, so we need to disable it's damage in the many frames that it is colliding.
						projectileComponents[k]->RenderInnert();

						// if an we die remove a life to our player!
						if (_playerRef.GetHealth() <= projectileComponents[k]->GetDamage())
						{
							_playerRef.RemoveLife();
							// DEBUG purposes
							std::cout << "YOU DIED! YOU HAVE " << _playerRef.LivesRemaining() << " LIVES REMAINING" << std::endl;
						}

						// otherwise take some damage
						_playerRef.TakeDamage(projectileComponents[k]->GetDamage());

						// DEBUG purposes
						std::cout << "You took " << projectileComponents[k]->GetDamage() <<
							" damage! You now have " << _playerRef.GetHealth() << " health!" << std::endl;
					}

					return;
				}
			}
		}			
		
	}
}

void DancingPlutonium::LevelObserver::CheckForItemCollision()
{
	if (ItemTokens.size() > 0)
	{
		for (int i = static_cast<int>(ItemTokens.size() - 1); i >= 0; i--)
		{
			if (Collision::BoundingBoxTest(_playerRef.GetSprite(), ItemTokens[i]->GetSprite()))
			{
				// we need to check what type of upgrade to perform!
				if (ItemTokens[i]->GetType() == ItemToken::ItemType::PatternToken)
				{
					_playerRef.GetWeaponEquipped()->UpgradeWeaponPattern();
					std::cout << "You ran into a pattern upgrade token!" << std::endl;
				}
				else if (ItemTokens[i]->GetType() == ItemToken::ItemType::BombToken)
				{
					_playerRef.AddBomb();
					std::cout << "You ran into a bomb token! You are carrying " << _playerRef.BombsRemaining() << " bombs." << std::endl;
				}
				else if (ItemTokens[i]->GetType() == ItemToken::ItemType::DamageToken)
				{
					_playerRef.GetWeaponEquipped()->UpgradeWeaponDamage();
					std::cout << "You ran into a weapon damage upgrade token!" << std::endl;
				}
				else if (ItemTokens[i]->GetType() == ItemToken::ItemType::FireRateToken)
				{
					_playerRef.GetWeaponEquipped()->UpgradeWeaponFireRate();
					std::cout << "You ran into a fire rate upgrade token!" << std::endl;
				}
				else if (ItemTokens[i]->GetType() == ItemToken::ItemType::FreeScoreToken)
				{
					_playerRef.AddScore(100);
					std::cout << "You ran into a Free Score token! Your score is now " << _playerRef.GetScore() << std::endl;
				}
				else if (ItemTokens[i]->GetType() == ItemToken::ItemType::LifeToken)
				{
					_playerRef.AddLife();
					std::cout << "You ran into a extra life token! You have " << _playerRef.LivesRemaining() << " lives remaining." << std::endl;
				}

				ItemTokens[i]->ToggleActiveState();
			}
		}
	}	
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

// CHEAT CODES - remove this later
void DancingPlutonium::LevelObserver::SpawnItemToken(const sf::Vector2f& _pos)
{
	ItemToken* item = TokenFactory::GetToken();
	
	if (item != nullptr)
	{
		item->SetPosition(_pos);
		ItemTokens.push_back(item);
	}
}

void DancingPlutonium::LevelObserver::KillCommand()
{
	for (int i = 0; i < static_cast<int>(EnemyShipContainer.size()); i++)
	{
		EnemyUnitDeath(*EnemyShipContainer[i]);

		EnemyShipContainer[i]->TakeDamage(300.f);
	}
}

void DancingPlutonium::LevelObserver::EnemyUnitDeath(AbstractBaseUnit& _unit)
{
	_playerRef.AddScore(_unit.GetValue());

	SpawnItemToken(_unit.GetPosition());
}

void DancingPlutonium::LevelObserver::UpgradeUnitWeaponry(AbstractBaseUnit& _unit)
{
	_unit.GetWeaponEquipped()->UpgradeWeaponPattern();
}

void DancingPlutonium::LevelObserver::Update(sf::RenderTarget& _rt, float _dt)
{
	// push back bullets fired by us if we are allowed to do so
	if (_playerRef.IsFiringBullet())
	{
		_playerRef.ToggleFiring();
		auto b = _playerRef.Shoot();
		PlayerProjectileContainer.push_back(b);
	}

	// fire a bomb if we are allowed to do so
	if (_playerRef.IsShootingBomb())
	{
		_playerRef.ToggleShootingBomb();
		auto b = _playerRef.GetBomb();
		BombContainer.push_back(b);
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

	CleanItemTokens(_rt);

	// Update the ItemTokens container
	if (ItemTokens.size() != 0)
	{
		for (int i = 0; i < static_cast<int>(ItemTokens.size()); i++)
		{
			if (ItemTokens[i]->IsActive())
			{
				ItemTokens[i]->Update(_dt, _rt);
			}
		}
	}

	CleanBombs(_rt);

	// Update the Bombs container
	if (BombContainer.size() != 0)
	{
		for (int i = 0; i < static_cast<int>(BombContainer.size()); i++)
		{
			if (BombContainer[i]->GetActiveState())
			{
				BombContainer[i]->Update(_dt);
			}
		}
	}

	// Perform collision detection
	CheckForUnitToUnitCollision();
	CheckForPlayerShotHit();
	CheckForEnemyShotHit();
	CheckForItemCollision();
	CheckForBombCollision();
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

	// Draw the Item Tokens
	for (int i = 0; i < static_cast<int>(ItemTokens.size()); i++)
	{
		ItemTokens[i]->Draw(_rt);
	}

	// Draw the Bombs
	for (int i = 0; i < static_cast<int>(BombContainer.size()); i++)
	{
		BombContainer[i]->Draw(_rt);
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

void DancingPlutonium::LevelObserver::CleanItemTokens(sf::RenderTarget& _rt)
{
	if (ItemTokens.size() > 0)
	{
		for (int i = static_cast<int>(ItemTokens.size() - 1); i >= 0; i--)
		{
			if (ItemTokens[i]->IsActive() == false)
			{
				delete ItemTokens[i];
				ItemTokens.erase(ItemTokens.begin() + i);
			}
		}
	}
}

void DancingPlutonium::LevelObserver::CleanBombs(sf::RenderTarget& _rt)
{
	if (BombContainer.size() > 0)
	{
		for (int i = static_cast<int>(BombContainer.size() - 1); i >= 0; i--)
		{
			if (BombContainer[i]->GetActiveState() == false)
			{
				delete BombContainer[i];
				BombContainer.erase(BombContainer.begin() + i);
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

void DancingPlutonium::LevelObserver::ClearPlayerProjectileContainer()
{
	if (PlayerProjectileContainer.size() > 0)
	{
		for (int i = static_cast<int>(PlayerProjectileContainer.size() - 1); i >= 0; i--)
		{
			delete PlayerProjectileContainer[i];
			PlayerProjectileContainer.erase(PlayerProjectileContainer.begin() + i);
		}
	}
}

void DancingPlutonium::LevelObserver::ClearItemTokens()
{
	if (ItemTokens.size() > 0)
	{
		for (int i = static_cast<int>(ItemTokens.size() - 1); i >= 0; i--)
		{
			delete ItemTokens[i];
			ItemTokens.erase(ItemTokens.begin() + i);
		}
	}
}

void DancingPlutonium::LevelObserver::ClearBombs()
{
	if (BombContainer.size() > 0)
	{
		for (int i = static_cast<int>(BombContainer.size() - 1); i >= 0; i--)
		{
			delete BombContainer[i];
			BombContainer.erase(BombContainer.begin() + i);
		}
	}
}