#include "AbstractBaseProjectile.h"

void DancingPlutonium::AbstractBaseProjectile::SetAllegiance(short _allegiance)
{
	allegiance = _allegiance;
}

short DancingPlutonium::AbstractBaseProjectile::GetAllegiance() const
{
	return allegiance;
}

float DancingPlutonium::AbstractBaseProjectile::GetSpeed() const
{
	return speed;
}

void DancingPlutonium::AbstractBaseProjectile::SetSpeed(const float _speed)
{
	speed = _speed;
}

bool DancingPlutonium::AbstractBaseProjectile::IsInnert() const
{
	return innert;
}

float DancingPlutonium::AbstractBaseProjectile::GetDamage() const
{
	return damage;
}

void DancingPlutonium::AbstractBaseProjectile::SetDamage(const float _damage)
{
	damage = _damage;
}

bool DancingPlutonium::AbstractBaseProjectile::GetActiveState(const sf::RenderTarget& _rt) const
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

sf::Sprite& DancingPlutonium::AbstractBaseProjectile::GetSprite()
{
	return sprite;
}

sf::FloatRect DancingPlutonium::AbstractBaseProjectile::GetBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2f DancingPlutonium::AbstractBaseProjectile::GetPosition() const
{
	return position;
}

void DancingPlutonium::AbstractBaseProjectile::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}
