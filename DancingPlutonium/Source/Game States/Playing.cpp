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
	LevelObserver levelObserver = LevelObserver();
	BasicShip* m_ship;
	m_ship = new BasicShip(_window);
	PlutoniumShip* me;
	me = new PlutoniumShip(_window);	

	Level1 l1 = Level1();
	levelObserver.EnemyShipContainer.push_back(m_ship);

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
				// Extract this into a Spawn ship function owned by LevelObserver. This way we can Spawn waves of ships in sequences.
				auto tempShip = new BasicShip(_window);
				tempShip->SpawnRandomly(_window);
				levelObserver.EnemyShipContainer.push_back(tempShip);
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
		}
		
		dt = clock.restart();
		_window.clear();
		_window.draw(bgSprite);
		me->Update(dt.asSeconds(), _window);
		me->Draw(_window);

		// Update the LevelObserver object AFTER the player. (we have to check if player is trying to shoot, then toggle if true)
		levelObserver.Update(_window, dt.asSeconds(), *me);
		levelObserver.Draw(_window);
		

		levelObserver.CheckForEnemyShotHit(*me);

		levelObserver.CheckForPlayerShotHit(*me);

		_window.display();
	}

	if (m_state == PlayState::s_level1)
	{
		l1.Show(_window, me);
	}
}
