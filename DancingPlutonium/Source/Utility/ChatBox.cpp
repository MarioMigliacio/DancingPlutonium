#include "ChatBox.h"

DancingPlutonium::ChatBox::ChatBox(const sf::String _name, const sf::Color& _fillColor, const sf::Color& _boarderColor, sf::FloatRect& _size)
	: chatBoxBoarderColor(_boarderColor), chatBoxFillColor(_fillColor)
{
	chatBoxName = _name;
	bounds = _size;
}

void DancingPlutonium::ChatBox::Draw(sf::RenderTarget& _rt) const
{
}

void DancingPlutonium::ChatBox::Update(float _dt, sf::RenderWindow& _window)
{
}

bool DancingPlutonium::ChatBox::IsRead()
{
	return false;
}

sf::String DancingPlutonium::ChatBox::GetName() const
{
	return sf::String();
}

void DancingPlutonium::ChatBox::SetOrigin(const sf::Vector2f _pos)
{
}

void DancingPlutonium::ChatBox::SetPosition(const sf::Vector2f _pos)
{
}

void DancingPlutonium::ChatBox::FadeIn(float _dt)
{
}

void DancingPlutonium::ChatBox::FadeOut(float _dt)
{
}

sf::FloatRect DancingPlutonium::ChatBox::GetBounds() const
{
	return sf::FloatRect();
}

void DancingPlutonium::ChatBox::SetColor(const sf::Color& _fillColor, const sf::Color& _boarderColor)
{
	
}

void DancingPlutonium::ChatBox::LoadFont()
{
	font.loadFromFile("Content/Fonts/Dejavu.ttf");
}
