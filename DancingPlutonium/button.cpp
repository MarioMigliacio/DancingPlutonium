#include "Button.h"

Button::Button(const sf::String name, const sf::Color& fillColor, const sf::Color& boarderColor, int size, bool clickable)
	: buttonFillColor(fillColor), buttonBoarderColor(boarderColor)
{
	clickable ? isClickable = true : isClickable = false;
	location = sf::Vector2f(0.0f, 0.0f);
	isClicked = false;
	isFading = false;
	setColor(fillColor, boarderColor);
	loadFont();

	buttonName = sf::Text(name, font, size);
	buttonName.setPosition(location);
	bounds = buttonName.getGlobalBounds();
	alpha = 0;
	accumulator = 0.0f;	
}

void Button::Draw(sf::RenderTarget& rt) const
{
	rt.draw(buttonName);
}

void Button::Update(float dt)
{
	if (isClickable)
	{
		accumulator += dt;

		if (buttonName.getGlobalBounds().contains((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y))
		{
			if (alpha < 255 && isFading == false)
			{
				if (accumulator >= 0.005f)
				{
					alpha++;
					isFading = false;
					accumulator = 0.0f;
				}
			}
			else if (alpha >= 254 || isFading)
			{
				if (accumulator >= 0.005f)
				{
					isFading = true;
					alpha--;
					accumulator = 0.0f;

					if (alpha == 0)
					{
						isFading = false;
					}
				}
			}

			setColor(sf::Color(buttonFillColor.r, buttonFillColor.g, buttonFillColor.b, alpha),
				sf::Color(buttonBoarderColor.r, buttonBoarderColor.g, buttonBoarderColor.b, alpha));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				IsClicked();
			}
		}
		else
		{
			setColor(sf::Color(buttonFillColor.r, buttonFillColor.g, buttonFillColor.b, alpha = 255),
				sf::Color(buttonBoarderColor.r, buttonBoarderColor.g, buttonBoarderColor.b, alpha = 255));
			accumulator = 0.0f;
		}
	}
	else
	{
		setColor(buttonFillColor, buttonBoarderColor);
	}
}

bool Button::IsClicked() 
{
	if (isClickable)
	{
		isClicked = true;
	}

	return isClicked;
}

void Button::setPosition(const sf::Vector2f pos)
{
	buttonName.setPosition(pos);
}

void Button::fadeIn(float dt)
{
	accumulator += dt;

	if (alpha < 255)
	{
		if (accumulator >= 0.0025f)
		{
			alpha++;
			accumulator = 0.0f;			
		}
	}

	setColor(sf::Color(buttonFillColor.r, buttonFillColor.g, buttonFillColor.b, alpha),
		sf::Color(buttonBoarderColor.r, buttonBoarderColor.g, buttonBoarderColor.b, alpha));
}

void Button::fadeOut(float dt)
{
	accumulator += dt;
			
	if (alpha > 0)
	{
		if (accumulator >= 0.0025f)
		{			
			alpha--;
			accumulator = 0.0f;
		}
	}

	setColor(sf::Color(buttonFillColor.r, buttonFillColor.g, buttonFillColor.b, alpha),
		sf::Color(buttonBoarderColor.r, buttonBoarderColor.g, buttonBoarderColor.b, alpha));
}

sf::FloatRect Button::getBounds() const
{
	return bounds;
}

void Button::setColor(const sf::Color& fillColor, const sf::Color& boarderColor)
{
	buttonName.setFillColor(fillColor);
	buttonName.setOutlineColor(boarderColor);
	buttonName.setOutlineThickness(2);
}

void Button::loadFont()
{
	font.loadFromFile("Content/Fonts/Arial.ttf");
}
