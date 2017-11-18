#include "Playing.h"

// Static variable declarations:
sf::Uint32 Playing::m_state = s_uninitialized;

void Playing::Show(sf::RenderWindow & _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != play_state::s_uninitialized)
	{
		return;
	}

	// Set the State:
	m_state = play_state::s_playing;

	// Scale screens with different computer screen resolutions: (the standard resolution in place is 720p: 1280wide x 720high, 60 fps)
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	// Set up the background:
	sf::Texture bgTexture;
	bgTexture.loadFromFile("Content/Images/TitleBackground.jpg");

	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);
	bgSprite.setPosition(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);

	// Perform the Main Menu screen display!
	while (m_state == play_state::s_playing)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_state = play_state::s_quit;
				return;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				SpawnShip(_window);
			}
		}

		_window.clear();
		_window.draw(bgSprite);
		m_ship.Draw(_window);
		_window.display();
	}		
}

void Playing::SpawnShip(sf::RenderWindow& _window)
{	
	m_ship.SetPosition(this->Emplace(_window));
}

sf::Vector2f Playing::Emplace(sf::RenderWindow& _window)
{	
	return sf::Vector2f(_window.getSize().x / 2.0f, _window.getSize().y / 6.0f);
}
