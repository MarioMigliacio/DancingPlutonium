#include "Bullet.h"

float DancingPlutonium::Bullet::GetSpeed() const
{
	return speed;
}

bool DancingPlutonium::Bullet::GetActiveState(const sf::RenderTarget& _rt) const
{
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

sf::Sprite& DancingPlutonium::Bullet::GetSprite()
{
	return sprite;
}

sf::FloatRect DancingPlutonium::Bullet::GetBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2f DancingPlutonium::Bullet::GetPosition() const
{
	return position;
}

void DancingPlutonium::Bullet::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}
