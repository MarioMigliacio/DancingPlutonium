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

void DancingPlutonium::AbstractBaseProjectile::RenderInnert()
{
	if (innert == false)
	{
		innert = true;
	}
}

float DancingPlutonium::AbstractBaseProjectile::GetDamage() const
{
	return damage;
}

void DancingPlutonium::AbstractBaseProjectile::SetDamage(const float _damage)
{
	damage = _damage;
}

sf::Sprite& DancingPlutonium::AbstractBaseProjectile::GetSprite()
{
	return sprite;
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
