#include "ChatBox.h"

DancingPlutonium::ChatBox::ChatBox(const sf::String& _nameOfBox, const sf::Color& _fillColor, const sf::Color& _boarderColor, const sf::Vector2f _sizeOfBox)
{
	chatBoxName = _nameOfBox;
	outLine.setSize(_sizeOfBox);
	outLine.setFillColor(_fillColor);
	outLine.setOutlineColor(_boarderColor);
	outLine.setOutlineThickness(2);
	
	isRead = false;
	isFadingIn = true;
	isFadingOut = false;

	SetMessage(_nameOfBox, 16);
}

void DancingPlutonium::ChatBox::Draw(sf::RenderTarget& _rt) const
{
	_rt.draw(outLine);
	_rt.draw(entireMessage);
}

void DancingPlutonium::ChatBox::Update(float _dt)
{
	if (isRead == false)
	{
		if (isFadingIn)
		{
			FadeIn(_dt);
		}

		if (InputManager::IsFinishedReadingText())
		{
			isRead = true;
		}
		else
		{
			isRead = false;
		}
	}
	else
	{
		if (isFadingOut)
		{
			FadeOut(_dt);
		}
	}
}

sf::String DancingPlutonium::ChatBox::GetName() const
{
	return chatBoxName;
}

void DancingPlutonium::ChatBox::SetOrigin(const sf::Vector2f _pos)
{
	outLine.setOrigin(_pos);
}

sf::Vector2f DancingPlutonium::ChatBox::GetPosition()
{
	return outLine.getPosition();
}

void DancingPlutonium::ChatBox::SetPosition(const sf::Vector2f _pos)
{
	outLine.setPosition(_pos);

	entireMessage.setPosition(_pos.x + entireMessage.getCharacterSize(), _pos.y + entireMessage.getCharacterSize());
}

void DancingPlutonium::ChatBox::FadeIn(float _dt)
{
	accumulator += _dt;

	if (alpha < 255 && isFadingIn)
	{
		if (accumulator >= 2.f)
		{
			alpha++;
			accumulator = 0.0f;
		}
	}
	else
	{
		isFadingIn = false;
	}

	SetColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, alpha),
		sf::Color(boarderColor.r, boarderColor.g, boarderColor.b, alpha));
}

void DancingPlutonium::ChatBox::FadeOut(float _dt)
{
	accumulator += _dt;

	if (alpha > 0)
	{
		if (accumulator >= 0.0025f)
		{
			alpha--;
			accumulator = 0.0f;
		}
	}
	else
	{
		isFadingOut = false;
	}

	SetColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, alpha),
		sf::Color(boarderColor.r, boarderColor.g, boarderColor.b, alpha));
}

sf::FloatRect DancingPlutonium::ChatBox::GetBounds() const
{
	return outLine.getGlobalBounds();
}

void DancingPlutonium::ChatBox::SetMessage(const sf::String& _msg, const int _size)
{
	LoadFont();

	entireMessage = sf::Text(_msg, font, _size);
	entireMessage.setFillColor(sf::Color::Red);
	entireMessage.setOutlineColor(sf::Color(128, 128, 128));
	entireMessage.setOutlineThickness(2);

	entireMessage.setPosition(sf::Vector2f(outLine.getPosition().x + 10, outLine.getPosition().y - 10));
}

sf::RectangleShape& DancingPlutonium::ChatBox::GetChatBoxOutline()
{
	return outLine;
}

void DancingPlutonium::ChatBox::SetColor(const sf::Color& _fillColor, const sf::Color& _boarderColor)
{
	boarderColor = _boarderColor;
	fillColor = _fillColor;

	// At construction, the isFadingIn property should be true, and we start with perfect opacity (255 alpha)
	if (isFadingIn)
	{
		alpha = 255;
		outLine.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, alpha));
		outLine.setOutlineColor(sf::Color(boarderColor.r, boarderColor.g, boarderColor.b, alpha));
	}
	else
	{
		alpha = 0;
		outLine.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, alpha));
		outLine.setOutlineColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, alpha));
	}

	outLine.setOutlineThickness(2);
}

void DancingPlutonium::ChatBox::LoadFont()
{
	font.loadFromFile("Content/Fonts/Dejavu.ttf");
}
