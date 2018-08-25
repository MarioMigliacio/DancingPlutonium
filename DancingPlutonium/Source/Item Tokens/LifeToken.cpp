#include "LifeToken.h"

DancingPlutonium::LifeToken::LifeToken() : ItemToken()
{
	isActive = true;
	accumulator = 0.f;
	SetSprite();
	speed = defaultSpeed;
	itemType = ItemToken::ItemType::LifeToken;
}

void DancingPlutonium::LifeToken::SetSprite()
{
	texture.loadFromFile("Content/Images/LifeToken.png");
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