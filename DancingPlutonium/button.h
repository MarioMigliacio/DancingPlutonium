#pragma once

#include<SFML/Graphics.hpp>

class Button
{
public:
	Button(const sf::String name, const sf::Color& fillColor, const sf::Color& boarderColor, int size, bool clickable);
	void Draw(sf::RenderTarget& rt) const;
	void Update(float dt);
	bool IsClicked();
	void setPosition(const sf::Vector2f pos);
	void fadeIn(float dt);
	void fadeOut(float dt);
	sf::FloatRect getBounds() const;

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
	sf::FloatRect bounds;
	sf::Font font;

private:
	void setColor(const sf::Color& fillColor, const sf::Color& boarderColor);
	void loadFont();
};