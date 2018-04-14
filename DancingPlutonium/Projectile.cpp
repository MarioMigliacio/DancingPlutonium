#include "Projectile.h"

float DancingPlutonium::Projectile::GetSpeed() const
{
	return speed;
}

bool DancingPlutonium::Projectile::IsFriendly() const
{
	return friendly;
}

bool DancingPlutonium::Projectile::IsInnert() const
{
	return innert;
}

bool DancingPlutonium::Projectile::GetActiveState(const sf::RenderTarget& _rt) const
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

sf::Sprite& DancingPlutonium::Projectile::GetSprite()
{
	return sprite;
}

sf::FloatRect DancingPlutonium::Projectile::GetBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2f DancingPlutonium::Projectile::GetPosition() const
{
	return position;
}

void DancingPlutonium::Projectile::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}
