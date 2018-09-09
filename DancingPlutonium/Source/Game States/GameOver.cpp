#include "GameOver.h"

// Static variable declarations:
sf::Uint32 DancingPlutonium::GameOver::m_state = s_uninitialized;

void DancingPlutonium::GameOver::Show(sf::RenderWindow& _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != GameOverState::s_uninitialized)
	{
		m_state = s_uninitialized;
	}

	// Set the State:
	m_state = GameOverState::s_playing;

	// Set up the Timers.
	sf::Clock clock1, clock2;
	sf::Time dt;

	// Set up the background:
	sf::Texture bgTexture;
	bgTexture.loadFromFile("Content/Images/GameOver.png");

	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);
	bgSprite.setPosition(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);

	// Set up the Texts which create the splash screen.
	Button youDied = Button("YOU HAVE DIED.", sf::Color::Red, sf::Color::Blue, 60, false);
	youDied.SetPosition(sf::Vector2f(_window.getSize().x / 2.0f - youDied.GetBounds().width / 2.0f, _window.getSize().y / 3.0f - youDied.GetBounds().height / 2.0f));

	Button youDied2 = Button("YOUR DEEDS OF VALOR WILL BE REMEMBERED.", sf::Color::Red, sf::Color::Blue, 40, false);
	youDied2.SetPosition(sf::Vector2f(_window.getSize().x / 2.0f - youDied2.GetBounds().width / 2.0f, _window.getSize().y / 2.0f - youDied2.GetBounds().height / 2.0f));

	// Set up the music player.
	sf::SoundBuffer sb;
	sb.loadFromFile("Content/Sounds/GameOver.wav");

	sf::Sound gameOverSound;
	gameOverSound.setBuffer(sb);
	gameOverSound.setVolume(10);
	gameOverSound.play();

	// Perform the GameOver splash screen!
	while (m_state == GameOverState::s_playing && clock1.getElapsedTime().asSeconds() <= 19.0f)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				|| sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				m_state = GameOverState::s_done;
				return;
			}
		}

		_window.clear();
		_window.draw(bgSprite);

		dt = clock2.restart();

		if (clock1.getElapsedTime().asSeconds() >= 18.0f)
		{
			youDied.FadeOut(dt.asSeconds());
			youDied.Draw(_window);
		}
		else if (clock1.getElapsedTime().asSeconds() >= 2.0f)
		{
			youDied.FadeIn(dt.asSeconds());
			youDied.Draw(_window);
		}

		if (clock1.getElapsedTime().asSeconds() >= 18.0f)
		{
			youDied2.FadeOut(dt.asSeconds());
			youDied2.Draw(_window);
		}
		else if (clock1.getElapsedTime().asSeconds() >= 4.0f)
		{
			youDied2.FadeIn(dt.asSeconds());
			youDied2.Draw(_window);
		}
				
		_window.display();
	}

	m_state = GameOverState::s_done;

	if (gameOverSound.getStatus() == sf::Sound::Playing)
	{
		gameOverSound.stop();
	}
}

sf::Uint32 DancingPlutonium::GameOver::getGameOverState() const
{
	return m_state;
}
