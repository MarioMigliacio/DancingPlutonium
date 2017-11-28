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
	BasicShip m_ship(_window);
	PlutoniumShip me(_window);
	
	// this works!
	std::vector<GenericEnemyUnit*> mm;
	std::vector<BasicBullet*> bullets;
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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{	
				//mm[0]->EmplaceRandomly(_window);				
				//m_ship.GetSprite().move(sf::Vector2f(5.0f, 0.0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				me.SetPosition(sf::Vector2f(me.GetPosition().x - 1.0f * me.GetSpeed(), me.GetPosition().y));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				me.SetPosition(sf::Vector2f(me.GetPosition().x + 1.0f * me.GetSpeed(), me.GetPosition().y));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				me.SetPosition(sf::Vector2f(me.GetPosition().x, me.GetPosition().y - 1.0f * me.GetSpeed()));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				me.SetPosition(sf::Vector2f(me.GetPosition().x, me.GetPosition().y + 1.0f * me.GetSpeed()));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				//bullets.push_back(new BasicBullet(_window, me.GetPosition()));				
			}
		}

		_window.clear();
		_window.draw(bgSprite);
		mm[0]->Draw(_window);
		me.Draw(_window);
		if (bullets.size() != 0)
		{
			/*for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->SetPosition(sf::Vector2f(bullets[i]->GetPosition().x, bullets[i]->GetPosition().y - 1.0f * bullets[i]->GetSpeed()));

				if (bullets[i]->GetActiveState() == false)
				{
					delete bullets[i];
					bullets.erase(bullets.begin() + i);
				}
			}*/

			/*for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->Draw(_window);
			}*/
		}
		_window.display();
	}
}
