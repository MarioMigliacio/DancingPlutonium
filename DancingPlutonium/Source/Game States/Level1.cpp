#include "Level1.h"
#include <iostream>

// Static variable declarations:
sf::Uint32 DancingPlutonium::Level1::m_state = s_uninitialized;

void DancingPlutonium::Level1::Show(sf::RenderWindow& _window, PlutoniumShip* _player)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != Level1::s_uninitialized)
	{
		return;
	}

	// friendly message for me to know that we moved into the real level
	std::cout << "YOU ARE PLAYING IN THE REAL WORLD NOW!" << std::endl;

	// Set the State:
	m_state = Level1::s_intro;
	LevelObserver levelObserver = LevelObserver();

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
				levelObserver.EnemyShipContainer.push_back(tempShip);
			}
			/*else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LControl ||
				event.key.code == sf::Keyboard::RControl))
			{
				_player->GetWeaponEquipped()->UpgradeWeaponPattern();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LAlt ||
				event.key.code == sf::Keyboard::RAlt))
			{
				_player->GetWeaponEquipped()->UpgradeWeaponFireRate();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up))
			{
				_player->GetWeaponEquipped()->UpgradeWeaponVelocityRate();
			}*/
		}

		bool isPlayerMoving = InputManager::IsMoving();
		_player->SetMovingState(isPlayerMoving);

		if (isPlayerMoving)
		{
			sf::Uint32 whichDirection = InputManager::GetDirection();
			_player->SetMoveState(whichDirection);
		}

		dt = clock.restart();
		_window.clear();
		_window.draw(bgSprite);
		_player->Update(dt.asSeconds(), _window);
		_player->Draw(_window);
		levelObserver.UpdateEnemyShipContainer(dt.asSeconds(), _window);
		levelObserver.DrawEnemyShipContainer(_window);

		// This works! woot woot.
		if (levelObserver.CheckForUnitToUnitCollision(*_player))
		{
			std::cout << "Bumped into an enemy unit." << std::endl;
		}

		if (levelObserver.CheckForEnemyShotHit(*_player))
		{
			std::cout << "Ran into that enemy bullet." << std::endl;
		}

		if (levelObserver.CheckForPlayerShotHit(_player->GetWeaponEquipped()->GetAmmunitionContainer()))
		{
			std::cout << " You shot that enemy unit! " << std::endl;
		}

		_window.display();
	}
}