#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Button.h"
#include "enumTypes.h"

int main()
{
	sf::RenderWindow window(RES1080P, "Dancing Plutonium", sf::Style::Fullscreen);
	sf::Texture texture;
	GameState currentState = GameState::MainMenu;
	GameDifficulty gameDifficulty = GameDifficulty::Easy;

	// current button testings:
	std::vector<Button> buttonContainer;
	Button welcomeButton = Button("Welcome To Dancing Plutonium", sf::Color::Red, sf::Color::Blue);
	Button playButton = Button("Play", sf::Color::Yellow, sf::Color::Blue);
	Button optionsButton = Button("Options", sf::Color::Yellow, sf::Color::Blue);
	Button scoreButton = Button("ScoreBoard", sf::Color::Yellow, sf::Color::Blue);

	welcomeButton.setPosition(sf::Vector2f(RES1080P.width / 2 - welcomeButton.getBounds().width / 2, RES1080P.height / 10 - welcomeButton.getBounds().height / 2));
	playButton.setPosition(sf::Vector2f(RES1080P.width / 2 - playButton.getBounds().width / 2, RES1080P.height / 4 - playButton.getBounds().height / 2));
	optionsButton.setPosition(sf::Vector2f(RES1080P.width / 2 - optionsButton.getBounds().width / 2, RES1080P.height / 4 - optionsButton.getBounds().height / 2 + 85));
	scoreButton.setPosition(sf::Vector2f(RES1080P.width / 2 - scoreButton.getBounds().width / 2, RES1080P.height / 4 - scoreButton.getBounds().height / 2 + 170));

	buttonContainer.push_back(welcomeButton);
	buttonContainer.push_back(playButton);
	buttonContainer.push_back(optionsButton);
	buttonContainer.push_back(scoreButton);

	if (!texture.loadFromFile("Content/Images/TitleBackground.jpg"))
	{
		return EXIT_FAILURE;
	}

	sf::Sprite background(texture);
	sf::Music music;

	if (!music.openFromFile("Content/Sounds/RootMenu.wav"))
	{
		return EXIT_FAILURE;
	}

	music.setLoop(true);
	music.play();

	sf::Clock cock;
	sf::Time dt;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		dt = cock.restart();

		window.clear();
		window.draw(background);

		for (int i = 0; i < (int)buttonContainer.size(); i++)
		{
			buttonContainer[i].Update(dt.asSeconds());
			buttonContainer[i].Draw(window);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}