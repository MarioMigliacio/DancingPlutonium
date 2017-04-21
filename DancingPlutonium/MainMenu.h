#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "EnumTypes.h"

class Menu 
{
public:
	Menu(sf::RenderWindow& window);
	~Menu();
	virtual void draw(sf::RenderTarget& window) const;
	void Update(float dt);
	void LoadBackground();
	void LoadMusic();
	void InitializeButtons(sf::RenderWindow& window);
	std::vector<Button> getButtons() const;

private:
	sf::Texture backTexture;
	sf::Sprite backSprite;
	sf::Music music;
	std::vector<Button> buttonContainer;
	Button welcomeButton;
	Button playButton;
	Button optionsButton;
	Button scoreButton;
};