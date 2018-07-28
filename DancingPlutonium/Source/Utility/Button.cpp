#include "Button.h"

DancingPlutonium::Button::Button(const sf::String _name, const sf::Color& _fillColor, const sf::Color& _boarderColor, int _size, bool _clickable)
	: buttonFillColor(_fillColor), buttonBoarderColor(_boarderColor)
{
	_clickable ? isClickable = true : isClickable = false;
	location = sf::Vector2f(0.0f, 0.0f);
	isClicked = false;
	isFading = false;
	setColor(_fillColor, _boarderColor);
	loadFont();

	buttonName = sf::Text(_name, font, _size);
	buttonName.setPosition(location);
	bounds = buttonName.getGlobalBounds();
	alpha = 0;
	accumulator = 0.0f;
}

DancingPlutonium::Button::Button(const Button& _ref)
{
	isFading = _ref.isFading;
	isClickable = _ref.isClickable;
	isClicked = _ref.isClicked;
	accumulator = _ref.accumulator;

	alpha = _ref.alpha;
	buttonName = _ref.buttonName;
	buttonFillColor = _ref.buttonFillColor;
	buttonBoarderColor = _ref.buttonBoarderColor;
	location = _ref.location;
	bounds = _ref.bounds;
	font = _ref.font;
}

void DancingPlutonium::Button::Draw(sf::RenderTarget& _rt) const
{
	_rt.draw(buttonName);
}

void DancingPlutonium::Button::Update(float _dt, sf::RenderWindow& _window)
{
	if (isClickable)
	{
		accumulator += _dt;

		// special note: do NOT use Mouse::getPosition(), it goes with GLOBAL desktop coords, keep it relative to the window!
		if (buttonName.getGlobalBounds().contains((float)sf::Mouse::getPosition(_window).x, (float)sf::Mouse::getPosition(_window).y))
		{
			if (alpha < 255 && isFading == false)
			{
				if (accumulator >= 0.005f)
				{
					alpha++;
					accumulator = 0.0f;

					if (alpha >= 255)
					{
						isFading = true;
					}
				}
			}
			else if (isFading)
			{
				if (accumulator >= 0.005f)
				{
					alpha--;
					accumulator = 0.0f;

					if (alpha == 0)
					{
						isFading = false;
					}
				}
			}

			// Make the button that is highlighted by the mouse RED color for the border.
			setColor(sf::Color(buttonFillColor.r, buttonFillColor.g, buttonFillColor.b, alpha),
				sf::Color(255, buttonBoarderColor.g, buttonBoarderColor.b, alpha));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isClickable)
			{
				isClicked = true;
			}
			else
			{
				isClicked = false;
			}
		}
		else
		{
			isFading = true;

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

bool DancingPlutonium::Button::IsClicked()
{
	return isClicked;
}

sf::String DancingPlutonium::Button::getName() const
{
	return buttonName.getString();
}

void DancingPlutonium::Button::setOrigin(const sf::Vector2f _pos)
{
	buttonName.setOrigin(_pos);
}

void DancingPlutonium::Button::setPosition(const sf::Vector2f _pos)
{
	buttonName.setPosition(_pos);
}

void DancingPlutonium::Button::fadeIn(float _dt)
{
	accumulator += +_dt;

	if (alpha < 255)
	{
		// this value updates the alpha value every 2.5 ms clock time
		if (accumulator >= 0.0025f)
		{
			alpha++;
			accumulator = 0.0f;			
		}
	}

	setColor(sf::Color(buttonFillColor.r, buttonFillColor.g, buttonFillColor.b, alpha),
		sf::Color(buttonBoarderColor.r, buttonBoarderColor.g, buttonBoarderColor.b, alpha));
}

void DancingPlutonium::Button::fadeOut(float _dt)
{
	accumulator += _dt;
			
	if (alpha > 0)
	{
		// this value updates the alpha value every 2.5 ms clock time
		if (accumulator >= 0.0025f)
		{			
			alpha--;
			accumulator = 0.0f;
		}
	}

	setColor(sf::Color(buttonFillColor.r, buttonFillColor.g, buttonFillColor.b, alpha),
		sf::Color(buttonBoarderColor.r, buttonBoarderColor.g, buttonBoarderColor.b, alpha));
}

sf::FloatRect DancingPlutonium::Button::getBounds() const
{
	return bounds;
}

void DancingPlutonium::Button::setColor(const sf::Color& _fillColor, const sf::Color& _boarderColor)
{
	buttonName.setFillColor(_fillColor);
	buttonName.setOutlineColor(_boarderColor);
	buttonName.setOutlineThickness(2);
}

void DancingPlutonium::Button::loadFont()
{
	font.loadFromFile("Content/Fonts/Dejavu.ttf");
}
