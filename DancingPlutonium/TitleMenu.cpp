#include "TitleMenu.h"

// Static variable declarations:
sf::Uint32 TitleMenu::m_state = s_uninitialized;

void TitleMenu::Show(sf::RenderWindow& _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (m_state != menu_state::s_uninitialized)
	{
		return;
	}

	// Set the State:
	m_state = menu_state::s_undecided;
	
	// Scale screens with different computer screen resolutions: (the standard resolution in place is 720p: 1280wide x 720high, 60 fps)
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	
	// Set up the background:
	sf::Texture bgTexture;
	bgTexture.loadFromFile("Content/Images/TitleBackground.png");

	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);
	bgSprite.setPosition(bgSprite.getGlobalBounds().width / 2.0f, bgSprite.getGlobalBounds().height / 2.0f);

	// Set up the Button locations:
	Button playButton = Button("Play", sf::Color::Yellow, sf::Color::Blue, 80, true);
	Button optionsButton = Button("Options", sf::Color::Yellow, sf::Color::Blue, 80, true);
	Button scoreButton = Button("ScoreBoard", sf::Color::Yellow, sf::Color::Blue, 80, true);

	playButton.setPosition(sf::Vector2f(_window.getSize().x / 2.0f - playButton.getBounds().width / 2.0f, _window.getSize().y / 6.0f - playButton.getBounds().height / 2.0f));
	optionsButton.setPosition(sf::Vector2f(_window.getSize().x / 2.0f - optionsButton.getBounds().width / 2.0f, _window.getSize().y / 6.0f - optionsButton.getBounds().height / 2.0f + 85));
	scoreButton.setPosition(sf::Vector2f(_window.getSize().x / 2.0f - scoreButton.getBounds().width / 2.0f, _window.getSize().y / 6.0f - scoreButton.getBounds().height / 2.0f + 170));

	// Put all the buttons in an iterable container:
	std::vector<Button> buttonContainer;
	buttonContainer.push_back(playButton);
	buttonContainer.push_back(optionsButton);
	buttonContainer.push_back(scoreButton);

	// Set up the Music: 
	sf::Music menuMusic;
	menuMusic.openFromFile("Content/Sounds/RootMenu.wav");
	menuMusic.setLoop(true);
	menuMusic.setVolume(100);
	menuMusic.play();

	// Set up the Timers:
	sf::Clock clock;
	sf::Time dt;

	// Perform the Main Menu screen display!
	while (m_state == menu_state::s_undecided)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_state = menu_state::s_quit;
				return;
			}
		}

		dt = clock.restart();

		_window.clear();
		_window.draw(bgSprite);

		for (int i = 0; i < (int)buttonContainer.size(); i++)
		{
			buttonContainer[i].Update(dt.asSeconds());
			buttonContainer[i].Draw(_window);

			if (buttonContainer[i].IsClicked())
			{
				if (buttonContainer[i].getName() == "Play")
				{
					m_state = menu_state::s_play;
					break;
				}
				else if (buttonContainer[i].getName() == "Options")
				{
					m_state = menu_state::s_options;
					break;
				}
				else if (buttonContainer[i].getName() == "ScoreBoard")
				{
					m_state = menu_state::s_score;
					break;
				}
			}
		}

		_window.display();
	}
}

sf::Uint32 TitleMenu::getMenuState() const
{
	return m_state;
}
