#include "Bullet.h"

Bullet::Bullet(sf::RenderTarget& _rt, sf::Vector2f& _pos)
{
	position = _pos;
}

float Bullet::GetSpeed() const
{
	return speed;
}

bool Bullet::GetActiveState(const sf::RenderTarget& _rt) const
{
	// check to see if it is possible to get the _rt as a rectangle and use the contains() logic?..
	if (sprite.getPosition().y < 0 || sprite.getPosition().x < 0 ||
		sprite.getPosition().y > _rt.getSize().y || sprite.getPosition().x > _rt.getSize().x)
	{
		return false;
	}
	else
	{
		return true;
	}
}

sf::Sprite& Bullet::GetSprite()
{
	return sprite;
}

sf::FloatRect Bullet::GetBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2f Bullet::GetPosition() const
{
	return position;
}

void Bullet::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

void Bullet::Update(float _dt)
{
	// LATER logic: you need to use the state of the bullet to consider the direction of the bullet (friendly or foe)
	// and also use the clock to make it mooove properly
	SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - 1.0f * speed));
}

void Bullet::Draw(sf::RenderTarget& _rt) const
{
	_rt.draw(sprite);
}
