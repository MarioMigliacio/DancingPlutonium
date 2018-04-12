#include "BasicBulletPlayer.h"

DancingPlutonium::BasicBulletPlayer::BasicBulletPlayer(const sf::Vector2f& _pos)
{
	position = _pos;
	speed = 100.0f;
	SetSprite(position);
}

void DancingPlutonium::BasicBulletPlayer::SetSprite(const sf::Vector2f& _origin)
{
	texture.loadFromFile("Content/Images/BulletBlue.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(_origin);
	position = _origin;
}

void DancingPlutonium::BasicBulletPlayer::Update(float _dt)
{
	SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed));
}

void DancingPlutonium::BasicBulletPlayer::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
}

