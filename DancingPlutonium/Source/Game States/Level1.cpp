#include "Level1.h"
#include <iostream>

// Static variable declarations:
sf::Uint32 DancingPlutonium::Level1::m_state = s_uninitialized;

void DancingPlutonium::Level1::Show(sf::RenderWindow& _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != Level1::s_uninitialized)
	{
		return;
	}

	std::cout << "YOU ARE PLAYING IN THE REAL WORLD NOW!" << std::endl;

	// Set the State:
	m_state = Level1::s_intro;
	BasicShip* m_ship;
	m_ship = new BasicShip(_window);
	PlutoniumShip* me;
	me = new PlutoniumShip(_window);
	LevelObserver levelObserver = LevelObserver();

	std::vector<AbstractBaseUnit*> enemyShips;
	std::vector<AbstractBaseProjectile*> playerBullets;
	std::vector<AbstractBaseProjectile*> enemybulletsMmHmm;
	//enemyShips.push_back(m_ship);
	levelObserver.EnemyShipContainer.push_back(m_ship);

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

	while (m_state == Level1::s_intro)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_state = Level1::s_quit;
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
		}

		bool isPlayerMoving = InputManager::IsMoving();
		me->SetMovingState(isPlayerMoving);

		if (isPlayerMoving)
		{
			sf::Uint32 whichDirection = InputManager::GetDirection();
			me->SetMoveState(whichDirection);
		}

		dt = clock.restart();
		_window.clear();
		_window.draw(bgSprite);
		me->Update(dt.asSeconds(), _window);
		me->Draw(_window);

		/*if (enemyShips.size() > 0)
		{
			for (int i = static_cast<int>(enemyShips.size() - 1); i >= 0; i--)
			{
				enemyShips[i]->Update(dt.asSeconds(), _window);
				enemyShips[i]->Draw(_window);

				if (enemyShips[i]->GetActiveState() == false)
				{
					delete enemyShips[i];
					enemyShips.erase(enemyShips.begin() + i);
				}
			}
		}*/

		///
		levelObserver.CheckForUnitToUnitCollision(*me, enemyShips);

		_window.display();
	}
}
