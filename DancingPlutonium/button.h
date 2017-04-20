#pragma once

#include<SFML/Graphics.hpp>

class Button
{
public:
	Button(const sf::Vector2f& pos, const sf::String name, const sf::Color& fillColor, const sf::Color& boarderColor);
	void Draw(sf::RenderTarget& rt) const;	
	void Update(float dt);
	bool OnClick();

private:
	bool isFading;
	bool isClickable;
	bool isClicked;
	float accumulator;
	sf::Uint8 alpha;
	sf::Text buttonName;
	sf::Color buttonFillColor;
	sf::Color buttonBoarderColor;
	sf::Vector2f location;
	sf::Font font;

private:
	void setColor(const sf::Color& fillColor, const sf::Color& boarderColor);
	void loadFont();
};