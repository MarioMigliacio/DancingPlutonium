#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define RES480P sf::VideoMode(720, 480)
#define RES720P sf::VideoMode(1280, 720)
#define RES1080P sf::VideoMode(1920, 1080)

int main()
{
	sf::RenderWindow window(RES1080P, "Dancing Plutonium");	
	sf::Texture texture;

	if (!texture.loadFromFile("Content/Images/Title_Background.png"))
	{
		return EXIT_FAILURE;
	}

	sf::Sprite sprite(texture);	
	sf::Font font;

	if (!font.loadFromFile("Content/Fonts/arial.ttf"))
	{
		return EXIT_FAILURE;
	}

	sf::Text text("Welcome to Dancing Plutionium", font, 50);
	text.setOutlineColor(sf::Color::Yellow);
	text.setOutlineThickness(2);
	text.setPosition(sf::Vector2f(RES1080P.width / 3, RES1080P.height / 4));
	sf::Music music;	

	if (!music.openFromFile("Content/Sounds/RootMenu.wav"))
	{
		return EXIT_FAILURE;
	}
	
	music.setLoop(true);
	music.play();
	
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
		
		window.clear();
		window.draw(sprite);
		window.draw(text);		
		window.display();
	}

	return EXIT_SUCCESS;
}