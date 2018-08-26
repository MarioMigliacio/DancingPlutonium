#include "Playing.h"
#include <iostream>
#include "AnimatedSprite.h"

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
	PlutoniumShip* me;
	me = new PlutoniumShip(_window);	
	LevelObserver levelObserver = LevelObserver(*me);
	Level1 l1 = Level1();
	levelObserver.SpawnEnemyUnit(_window);

	// animation test:
	//sf::Texture bombTex;
	//if (!bombTex.loadFromFile("Content/Images/BombBlast_Original.png"))
	//{
	//	std::cout << "Failed to load bomb spritesheet!" << std::endl;
	//}

	//Animation bomb;
	//bomb.setSpriteSheet(bombTex);
	//
	//bomb.addFrame(sf::IntRect(384, 384, 128, 128));
	//bomb.addFrame(sf::IntRect(0, 0, 128, 128));
	//bomb.addFrame(sf::IntRect(128, 0, 128, 128));
	//bomb.addFrame(sf::IntRect(256, 0, 128, 128));
	//bomb.addFrame(sf::IntRect(384, 0, 128, 128));
	//
	//bomb.addFrame(sf::IntRect(0, 128, 128, 128));
	//bomb.addFrame(sf::IntRect(128, 128, 128, 128));
	//bomb.addFrame(sf::IntRect(256, 128, 128, 128));
	//bomb.addFrame(sf::IntRect(384, 128, 128, 128));
	//
	//bomb.addFrame(sf::IntRect(0, 256, 128, 128));
	//bomb.addFrame(sf::IntRect(128, 256, 128, 128));
	//bomb.addFrame(sf::IntRect(256, 256, 128, 128));
	//bomb.addFrame(sf::IntRect(384, 256, 128, 128));
	//
	//bomb.addFrame(sf::IntRect(0, 384, 128, 128));
	//bomb.addFrame(sf::IntRect(128, 384, 128, 128));
	//bomb.addFrame(sf::IntRect(256, 384, 128, 128));
	//

	//Animation* currentAnimation = &bomb;

	//// set up AnimatedSprite
	//AnimatedSprite animatedSprite(sf::seconds(0.2f), true, false);
	//animatedSprite.setPosition(sf::Vector2f(_window.getSize().x / 2.f - 128, _window.getSize().y / 2.f - 128));

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
				levelObserver.SpawnEnemyUnit(_window);
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
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::K))
			{
				levelObserver.KillCommand();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::B))
			{
				// update AnimatedSprite
				/*animatedSprite.play(*currentAnimation);*/
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

		/*animatedSprite.update(dt);
		_window.draw(animatedSprite);*/
		// Update the LevelObserver object AFTER the player. (we have to check if player is trying to shoot, then toggle if true)
		levelObserver.Update(_window, dt.asSeconds());
		levelObserver.Draw(_window);

		_window.display();
	}

	if (m_state == PlayState::s_level1)
	{
		l1.Show(_window, me);
	}
}
