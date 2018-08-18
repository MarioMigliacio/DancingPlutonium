#include "AbstractBaseUnit.h"

int DancingPlutonium::AbstractBaseUnit::GetValue() const
{
	return value;
}

float DancingPlutonium::AbstractBaseUnit::GetHealth() const
{
	return health;
}

bool DancingPlutonium::AbstractBaseUnit::IsInvulnerable() const
{
	return isInvulnerable;
}

void DancingPlutonium::AbstractBaseUnit::ToggleInvulnerability()
{
	isInvulnerable ? isInvulnerable = false : isInvulnerable = true;
}

bool DancingPlutonium::AbstractBaseUnit::IsFiringBullet() const
{
	return isFiring;
}

void DancingPlutonium::AbstractBaseUnit::ToggleFiring()
{
	isFiring ? isFiring = false : isFiring = true;
}

float DancingPlutonium::AbstractBaseUnit::GetDamageMultiplier() const
{
	return damageMultiplier;
}

float DancingPlutonium::AbstractBaseUnit::GetFireRate() const
{
	return fireRate;
}

float DancingPlutonium::AbstractBaseUnit::GetSpeed() const
{
	return speed;
}

bool DancingPlutonium::AbstractBaseUnit::IsWithinBounds(const sf::RenderTarget& _rt)
{
	auto rect = sprite.getGlobalBounds();
	sf::FloatRect gameBounds = sf::FloatRect(0.0f, 0.0f, static_cast<float>(_rt.getSize().x), static_cast<float>(_rt.getSize().y));

	if (gameBounds.intersects(rect))
	{
		return true;
	}
	else
	{
		isActive = false;
		return false;
	}
}

DancingPlutonium::Weapon* DancingPlutonium::AbstractBaseUnit::GetWeaponEquipped()
{
	return weapon;
}

bool DancingPlutonium::AbstractBaseUnit::GetActiveState() const
{
	return isActive;
}

short DancingPlutonium::AbstractBaseUnit::GetAllegiance() const
{
	return allegiance;
}

sf::Vector2f DancingPlutonium::AbstractBaseUnit::GetPosition() const
{
	return position;
}

void DancingPlutonium::AbstractBaseUnit::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

void DancingPlutonium::AbstractBaseUnit::TakeDamage(const float _val)
{
	if (!isInvulnerable)
	{
		health -= _val;

		// this component should only be for Enemy units, players should just lose life.
		health > 0.0f ? isActive = true : isActive = false;
	}
}

void DancingPlutonium::AbstractBaseUnit::SpawnRandomly(const sf::RenderTarget& _rt)
{
	int randomX = static_cast<int>(_rt.getSize().x - sprite.getGlobalBounds().width / 2.0f);
	randomX = RandomIntRange(static_cast<int>(sprite.getGlobalBounds().width / 2.0f), randomX) % randomX;
	
	SetPosition(sf::Vector2f(static_cast<float>(randomX), 16.0f));
}

void DancingPlutonium::AbstractBaseUnit::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
}
