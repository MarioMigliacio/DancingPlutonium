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

	sf::Vector2f chatBoxTest = sf::Vector2f(static_cast<float>(_window.getSize().x) - 20, static_cast<float>(_window.getSize().y) / 5.f);

	// Now that chatboxes work, we can make the Level object itself have a dictionary of string values to create new chatboxes later on.
	// We should be able to add chatboxes into a vector similar to how we have done in TitleMenu with buttons. 
	// we'll need to dispose of chatboxes based on the CanDispose() method, and can space the timing of chatboxes by using negative time values on the clock timer
	ChatBox introChatBox = ChatBox("Press SpaceBar to shoot!, navigate using W A S D keys!", chatBoxTest);
	introChatBox.SetPosition(sf::Vector2f(10.f, _window.getSize().y - introChatBox.GetChatBoxOutline().getSize().y - 10));

	// Set up the background:
	sf::Texture bgTexture;
	bgTexture.loadFromFile("Content/Images/Space1.png");

	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);
	bgSprite.setPosition(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);

	// Set up the Timers.
	sf::Clock clock, box1Timer;
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
		// special: Draw chatboxes before other things so the alpha can really work.
		introChatBox.Update(dt.asSeconds(), box1Timer.getElapsedTime().asSeconds());
		introChatBox.Draw(_window);
		_player->Update(dt.asSeconds(), _window);
		_player->Draw(_window);
		levelObserver.Update(_window, dt.asSeconds(), *_player);
		levelObserver.Draw(_window);
		

		// This works! woot woot.
		if (levelObserver.CheckForUnitToUnitCollision(*_player))
		{
			std::cout << "Bumped into an enemy unit." << std::endl;
		}

		if (levelObserver.CheckForEnemyShotHit(*_player))
		{
			std::cout << "Ran into that enemy bullet." << std::endl;
		}

		/*if (levelObserver.CheckForPlayerShotHit(_player->GetWeaponEquipped()->GetAmmunitionContainer(), *_player))
		{
			std::cout << " You shot that enemy unit! " << std::endl;
		}*/

		_window.display();
	}
}