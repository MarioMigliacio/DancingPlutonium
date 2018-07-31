#include "ChatBox.h"

DancingPlutonium::ChatBox::ChatBox(const sf::String& _nameOfBox, const sf::Vector2f _sizeOfBox)
{
	accumulator = 0;
	indexer = 0;
	alpha = 0;

	chatBoxName = _nameOfBox;
	outLine.setSize(_sizeOfBox);
	outLine.setFillColor(sf::Color::Black);
	outLine.setOutlineColor(sf::Color(128, 128, 128));
	outLine.setOutlineThickness(2);
	
	isRead = false;

	SetMessage(_nameOfBox, 24);
}

void DancingPlutonium::ChatBox::Draw(sf::RenderTarget& _rt) const
{
	_rt.draw(outLine);
	_rt.draw(typeWriterMessage);
}

void DancingPlutonium::ChatBox::Update(float _dt, float _killTimer)
{
	accumulator += _dt;

	TypeWriterEffect(accumulator);

	if (_killTimer >= 5.f)
	{
		FadeOut(accumulator);
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
	entireMessage.setOutlineThickness(1);

	entireMessage.setPosition(sf::Vector2f(outLine.getPosition().x + 10, outLine.getPosition().y - 10));
}

sf::RectangleShape& DancingPlutonium::ChatBox::GetChatBoxOutline()
{
	return this->outLine;
}

void DancingPlutonium::ChatBox::TypeWriterEffect(float _dt)
{
	typeWriterMessage = entireMessage;
	
	sf::String temp = entireMessage.getString().substring(0, indexer);
	typeWriterMessage.setString(temp);

	if (indexer < entireMessage.getString().getSize() && accumulator >= 0.025f)
	{
		indexer++;
		accumulator = 0.f;
	}
}

void DancingPlutonium::ChatBox::FadeOut(float _dt)
{
	if (alpha < 255 && accumulator >= 0.0025f)
	{
		alpha++;
		accumulator = 0.0f;
	}

	auto outlineFill = outLine.getFillColor();
	auto outlineOut = outLine.getOutlineColor();
	auto entireFill = entireMessage.getFillColor();
	auto entireOut = entireMessage.getOutlineColor();

	outLine.setFillColor(sf::Color(outlineFill.r, outlineFill.g, outlineFill.b, alpha));
	outLine.setOutlineColor(sf::Color(outlineOut.r, outlineOut.g, outlineOut.b, alpha));
	entireMessage.setFillColor(sf::Color(entireFill.r, entireFill.g, entireFill.b, alpha));
	entireMessage.setFillColor(sf::Color(entireOut.r, entireOut.g, outlineFill.b, alpha));
}

void DancingPlutonium::ChatBox::LoadFont()
{
	font.loadFromFile("Content/Fonts/Dejavu.ttf");
}
