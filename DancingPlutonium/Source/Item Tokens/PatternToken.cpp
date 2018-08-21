#include "PatternToken.h"

DancingPlutonium::PatternToken::PatternToken() : ItemToken()
{
	isActive = true;
	accumulator = 0.f;
	SetSprite();
	speed = defaultSpeed;
}

void DancingPlutonium::PatternToken::SetSprite()
{
	texture.loadFromFile("Content/Images/PatternToken.png");
	auto width = texture.getSize().x;
	auto height = texture.getSize().y;
	sf::Vector2f origin = sf::Vector2f(width / 2.0f, height / 2.0f);
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(origin);
	sprite.setScale(.5f, .5f);
	position = origin;
	SetPosition(origin);
}

void DancingPlutonium::PatternToken::Update(const float& _dt, const sf::RenderTarget& _rt)
{
	if (IsWithinBounds(_rt))
	{
		accumulator += _dt;

		if (accumulator >= 3.f)
		{
			auto tempPos = position;
			tempPos.y += _dt * speed;
			SetPosition(tempPos);			
		}
	}
}
