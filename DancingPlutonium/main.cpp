#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "button.h"


#define RES1080P sf::VideoMode(1920, 1080)

int main()
{
	sf::RenderWindow window(RES1080P, "Dancing Plutonium", sf::Style::Fullscreen);	
	sf::Texture texture;
	std::vector<Button> buttonContainer;
	Button welcomeButton = Button(sf::Vector2f(RES1080P.width / 5, RES1080P.height / 10), "Welcome To Dancing Plutonium", sf::Color::Red, sf::Color::Blue);
	Button playButton = Button(sf::Vector2f(RES1080P.width / 2 - 100, RES1080P.height / 5), "Play", sf::Color::Yellow, sf::Color::Blue);
	
	buttonContainer.push_back(welcomeButton);
	buttonContainer.push_back(playButton);

	if (!texture.loadFromFile("Content/Images/TitleBackground.png"))
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
		//fuckinButton.Update();
		//fuckinButton.Draw(window);
		for (int i = 0; i < buttonContainer.size(); i++)
		{
			buttonContainer[i].Update(dt.asSeconds());
			buttonContainer[i].Draw(window);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}