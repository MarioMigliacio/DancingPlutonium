#include "BasicBullet.h"

DancingPlutonium::BasicBullet::BasicBullet(const sf::RenderTarget& _rt, const sf::Vector2f& _pos)
{
	position = _pos;
	speed = 100.0f;
	SetSprite(position);
}

void DancingPlutonium::BasicBullet::SetSprite(const sf::Vector2f& _origin)
{
	texture.loadFromFile("Content/Images/BulletBlue.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(_origin);
	position = _origin;
}

void DancingPlutonium::BasicBullet::Update(float _dt)
{
	SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed));
}

