#include "Intro.h"

// Static variable declarations:
sf::Uint32 DancingPlutonium::Intro::m_state = s_uninitialized;

void DancingPlutonium::Intro::Show(sf::RenderWindow& _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != IntroState::s_uninitialized)
	{
		return;
	}

	// Set the State:
	m_state = IntroState::s_playing;

	// Set up the Timers.
	sf::Clock clock1, clock2;
	sf::Time dt;

	// Set up the Texts which create the splash screen.
	Button welcomeButton = Button("Welcome To Dancing Plutonium", sf::Color::Red, sf::Color::Blue, 60, false);
	welcomeButton.SetPosition(sf::Vector2f(_window.getSize().x / 2.0f - welcomeButton.GetBounds().width / 2.0f, _window.getSize().y / 3.0f - welcomeButton.GetBounds().height / 2.0f));

	Button sponsor = Button("Starring and Directed by: Mario Migliacio", sf::Color::Yellow, sf::Color::Blue, 40, false);
	sponsor.SetPosition(sf::Vector2f(_window.getSize().x / 2.0f - sponsor.GetBounds().width / 2.0f, _window.getSize().y / 2.0f - sponsor.GetBounds().height / 2.0f));

	// Set up the music player.
	sf::SoundBuffer sb;
	sb.loadFromFile("Content/Sounds/IntroClip.wav");

	sf::Sound menusound;
	menusound.setBuffer(sb);
	menusound.setVolume(100);
	menusound.play();

	// Perform the Introduction splash screen!
	while (m_state == IntroState::s_playing && clock1.getElapsedTime().asSeconds() <= 6.0f)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed 
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				|| sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				m_state = IntroState::s_done;
				return;
			}
		}

		_window.clear();

		dt = clock2.restart();
				
		if (clock1.getElapsedTime().asSeconds() >= 5.0f)
		{
			welcomeButton.FadeOut(dt.asSeconds());
			welcomeButton.Draw(_window);
		}
		else if (clock1.getElapsedTime().asSeconds() >= 1.0f)
		{
			welcomeButton.FadeIn(dt.asSeconds());
			welcomeButton.Draw(_window);
		}

		if (clock1.getElapsedTime().asSeconds() >= 5.0f)
		{
			sponsor.FadeOut(dt.asSeconds());
			sponsor.Draw(_window);
		}
		else if (clock1.getElapsedTime().asSeconds() >= 2.0f)
		{
			sponsor.FadeIn(dt.asSeconds());
			sponsor.Draw(_window);
		}		

		_window.display();
	}

	m_state = IntroState::s_done;

	if (menusound.getStatus() == sf::Sound::Playing)
	{
		menusound.stop();
	}
}

sf::Uint32 DancingPlutonium::Intro::getIntroState() const
{
	return m_state;
}
