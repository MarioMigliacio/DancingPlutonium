#include "FireRateToken.h"

DancingPlutonium::FireRateToken::FireRateToken() : ItemToken()
{
	isActive = true;
	accumulator = 0.f;
	SetSprite();
	speed = defaultSpeed;
	itemType = ItemToken::ItemType::FireRateToken;
}

void DancingPlutonium::FireRateToken::SetSprite()
{
	texture.loadFromFile("Content/Images/FireRateToken.png");
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