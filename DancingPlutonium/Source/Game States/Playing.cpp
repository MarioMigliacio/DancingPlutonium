#include "Playing.h"

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

	// Set the State:
	m_state = PlayState::s_playing;
	BasicShip m_ship(_window);
	PlutoniumShip me(_window);
	
	// this works!
	std::vector<AbstractBaseUnit*> mm;
	mm.push_back(&m_ship);

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

	// Perform the Main Menu screen display!
	while (m_state == PlayState::s_playing)
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
				mm[0]->SpawnRandomly(_window);
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LControl ||
				event.key.code == sf::Keyboard::RControl))
			{
 				me.GetWeaponEquipped()->UpgradeWeaponPattern();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LAlt ||
				event.key.code == sf::Keyboard::RAlt))
			{
				me.GetWeaponEquipped()->UpgradeWeaponFireRate();
			}
			else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up))
			{
				me.GetWeaponEquipped()->UpgradeWeaponVelocityRate();
			}
		}

		// Movement check outside of the event loop polls game at any time anyway, screw events - they weren't working smoothly anyway
		bool isPlayerMoving = InputManager::IsMoving();
		me.SetMovingState(isPlayerMoving);
		
		if (isPlayerMoving)
		{
			sf::Uint32 whichDirection = InputManager::GetDirection();
			me.SetMoveState(whichDirection);
		}
		/*else
		{
			me.SetMoveState(Movement::s_noMovement);
		}*/

		dt = clock.restart();
		_window.clear();
		_window.draw(bgSprite);
		//_window.draw(mm[0]->GetSprite());
		me.Update(dt.asSeconds(), _window);
		me.Draw(_window);
		mm[0]->Update(dt.asSeconds(), _window);
		mm[0]->Draw(_window);		
		_window.display();
	}
}
