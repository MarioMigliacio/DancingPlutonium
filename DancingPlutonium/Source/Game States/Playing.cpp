#include "Playing.h"
#include <iostream>

// Static variable declarations:
sf::Uint32 DancingPlutonium::Playing::m_state = s_uninitialized;

//Playgrounds for testing
void DancingPlutonium::Playing::Show(sf::RenderWindow& _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != PlayState::s_uninitialized)
	{
		return;
	}

	std::cout << "YOU ARE PLAYING IN THE SANDBOX!" << std::endl;

	// Set the State:
	m_state = PlayState::s_sandbox;
	BasicShip* m_ship;
	m_ship = new BasicShip(_window);
	PlutoniumShip* me;
	me = new PlutoniumShip(_window);

	Level1 l1 = Level1();

	std::vector<AbstractBaseUnit*> enemyShips;
	std::vector<AbstractBaseProjectile*> alladembulletsMmHmm;
	std::vector<AbstractBaseProjectile*> allademeEnemybulletsMmHmm;
	enemyShips.push_back(m_ship);


	// Scale screens with different computer screen resolutions: (the standard resolution in place is 720p: 1280wide x 720high, 60 fps)
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	// Set up the background:
	sf::Texture bgTexture;
	bgTexture.loadFromFile("Content/Images/Space1.png");

	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);
	bgSprite.setPosition(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);

	// Set up the Timers.
	sf::Clock clock;
	sf::Time dt;

	while (m_state == PlayState::s_sandbox)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_state = PlayState::s_quit;
				return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{	
				auto tempShip = new BasicShip(_window);
				tempShip->SpawnRandomly(_window);
				enemyShips.push_back(tempShip);
				//enemyShips[0]->SpawnRandomly(_window);
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LControl ||
				event.key.code == sf::Keyboard::RControl))
			{
				me->GetWeaponEquipped()->UpgradeWeaponPattern();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LAlt ||
				event.key.code == sf::Keyboard::RAlt))
			{
				me->GetWeaponEquipped()->UpgradeWeaponFireRate();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up))
			{
				me->GetWeaponEquipped()->UpgradeWeaponVelocityRate();
			}

			// activate the level testing:
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Num0))
			{
				m_state = PlayState::s_level1;
			}
		}
		
		bool isPlayerMoving = InputManager::IsMoving();
		me->SetMovingState(isPlayerMoving);
		
		if (isPlayerMoving)
		{
			sf::Uint32 whichDirection = InputManager::GetDirection();
			me->SetMoveState(whichDirection);

			// this proves level has access to the coords of player and able to get bounding rectangle
			//auto playerRect = me->GetRect();
			//std::cout << " our rect bounds are at (L: " << playerRect.left << ", T: " << playerRect.top <<
			//	", W: " << playerRect.width << ", H: " << playerRect.height << std::endl;
		}
		
		dt = clock.restart();
		_window.clear();
		_window.draw(bgSprite);
		me->Update(dt.asSeconds(), _window);
		me->Draw(_window);
		
		// EXPERIMENT REGION BE WARNED


		// This is how collision for unit - unit should be. Using the BoundingBoxTest() function.
		// TODO write this into a function that the level class maintains.
		if (enemyShips.size() > 0)
		{
			sf::Sprite npcUnit = sf::Sprite();
			sf::Sprite dp = me->GetSprite();

			for (int i = static_cast<int>(enemyShips.size() - 1); i >= 0; i--)
			{
				enemyShips[i]->Update(dt.asSeconds(), _window);
				enemyShips[i]->Draw(_window);
				npcUnit = enemyShips[i]->GetSprite();

				// FIXED! the abstract base unit's GetSprite() was not good enough! Had to have override capability to return the 'right' sprite object.
				
				if (Collision::BoundingBoxTest(dp, npcUnit))
				{
					std::cout << " You have crashed into an enemy ship! " << std::endl;
				}
			}
		}

		// This is how collision for player bullets - enemy units should be. Using the BoundingBoxTest() function.
		// TODO write this into a function that the level class maintains.
		if (enemyShips.size() > 0)
		{
			sf::Sprite npcUnit = sf::Sprite();
			std::vector<sf::Sprite> playerBullets = std::vector<sf::Sprite>();
			alladembulletsMmHmm = me->GetWeaponEquipped()->GetAmmunitionContainer();

			for (int i = 0; i < static_cast<int>(enemyShips.size()); i++)
			{
				npcUnit = enemyShips[i]->GetSprite();

				if (alladembulletsMmHmm.size() > 0)
				{
					for (int j = 0; j < static_cast<int>(alladembulletsMmHmm.size()); j++)
					{
						playerBullets = alladembulletsMmHmm[j]->GetAllSprites();

						if (playerBullets.size() > 0)
						{
							for (int k = 0; k < static_cast<int>(playerBullets.size()); k++)
							{
								if (Collision::BoundingBoxTest(npcUnit, playerBullets[k]))
								{
									std::cout << " You have SHOT an enemy ship! " << std::endl;
								}
							}
						}
					}
				}
			}
		}

		// This is how collision for player - enemy bullets should be. Using the BoundingBoxTest() function.
		// TODO write this into a function that the level class maintains.
		if (enemyShips.size() > 0)
		{
			std::vector<sf::Sprite> enemyBullets = std::vector<sf::Sprite>();
			sf::Sprite dp = me->GetSprite();

			for (int i = static_cast<int>(enemyShips.size() - 1); i >= 0; i--)
			{
				if (enemyShips[i]->GetActiveState())
				{
					// get that ships weapon container
					allademeEnemybulletsMmHmm = enemyShips[i]->GetWeaponEquipped()->GetAmmunitionContainer();

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
									if (Collision::BoundingBoxTest(enemyBullets[k], dp))
									{
										std::cout << " You have been fired upon! " << std::endl;
									}
								}
							}
						}
					}
				}
			}
		}

		_window.display();
	}

	if (m_state == PlayState::s_level1)
	{
		l1.Show(_window, me);
	}
}
