#include "TitleMenu.h"

// Static variable declarations:
sf::Uint32 DancingPlutonium::TitleMenu::menuState = s_uninitialized;

void DancingPlutonium::TitleMenu::Show(sf::RenderWindow& _window)
{
	// Ensure that the initialization takes place correctly here and for the first time.
	if (menuState != MenuState::s_uninitialized)
	{
		return;
	}

	// Set the State:
	menuState = MenuState::s_undecided;
	
	// Set up the background:
	sf::Texture bgTexture;
	bgTexture.loadFromFile("Content/Images/TitleBackground.png");

	const float widthScale = static_cast<float>(_window.getSize().x) / static_cast<float>(bgTexture.getSize().x);
	const float heightScale = static_cast<float>(_window.getSize().y) / static_cast<float>(bgTexture.getSize().y);

	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(sf::Vector2f(widthScale, heightScale));
	bgSprite.setOrigin(0.f, 0.f);
	bgSprite.setPosition(0.f, 0.f);

	// Put all the buttons in an iterable container which makes cleanup easy.
	std::vector<Button*> buttonContainer;
	buttonContainer.push_back(new Button("Play", sf::Color::Yellow, sf::Color::Blue, 80, true));
	buttonContainer[0]->setPosition(sf::Vector2f(_window.getSize().x / 2.0f - buttonContainer[0]->getBounds().width / 2.0f, _window.getSize().y / 6.0f - buttonContainer[0]->getBounds().height / 2.0f));
	buttonContainer.push_back(new Button("Options", sf::Color::Yellow, sf::Color::Blue, 80, true));
	buttonContainer[1]->setPosition(sf::Vector2f(_window.getSize().x / 2.0f - buttonContainer[1]->getBounds().width / 2.0f, _window.getSize().y / 6.0f - buttonContainer[1]->getBounds().height / 2.0f + 85));
	buttonContainer.push_back(new Button("ScoreBoard", sf::Color::Yellow, sf::Color::Blue, 80, true));
	buttonContainer[2]->setPosition(sf::Vector2f(_window.getSize().x / 2.0f - buttonContainer[2]->getBounds().width / 2.0f, _window.getSize().y / 6.0f - buttonContainer[2]->getBounds().height / 2.0f + 170));

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
	while (menuState == MenuState::s_undecided)
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				menuState = MenuState::s_quit;
				return;
			}
		}

		dt = clock.restart();

		_window.clear();
		_window.draw(bgSprite);

		for (int i = 0; i < (int)buttonContainer.size(); i++)
		{
			buttonContainer[i]->Update(dt.asSeconds(), _window);
			buttonContainer[i]->Draw(_window);

			if (buttonContainer[i]->IsClicked())
			{
				if (buttonContainer[i]->getName() == "Play")
				{
					menuState = MenuState::s_play;
					cleanup(buttonContainer);
					break;
				}
				else if (buttonContainer[i]->getName() == "Options")
				{
					menuState = MenuState::s_options;
					cleanup(buttonContainer);
					break;
				}
				else if (buttonContainer[i]->getName() == "ScoreBoard")
				{
					menuState = MenuState::s_score;
					cleanup(buttonContainer);
					break;
				}
			}
		}

		_window.display();
	}
}

sf::Uint32 DancingPlutonium::TitleMenu::getMenuState() const
{
	return menuState;
}

void DancingPlutonium::TitleMenu::cleanup(std::vector<Button*>& _container)
{
	int iter = static_cast<int>(_container.size() - 1);

	for (iter; iter >= 0; iter--)
	{
		delete _container[iter];
		_container.erase(_container.end() - 1);
	}
}
