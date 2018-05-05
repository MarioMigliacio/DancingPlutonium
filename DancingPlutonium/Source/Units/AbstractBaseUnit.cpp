#include "AbstractBaseUnit.h"

int DancingPlutonium::AbstractBaseUnit::GetValue() const
{
	return value;
}

float DancingPlutonium::AbstractBaseUnit::GetHealth() const
{
	return health;
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

bool DancingPlutonium::AbstractBaseUnit::GetActiveState(const sf::RenderTarget& _rt)
{
	auto rect = sprite.getGlobalBounds();
	sf::FloatRect holdUp = sf::FloatRect(0.0f, 0.0f, static_cast<float>(_rt.getSize().x), static_cast<float>(_rt.getSize().y));

	if (holdUp.intersects(rect))
	{
		isActive = true;
	}
	else
	{
		isActive = false;
	}

	return isActive;
}

DancingPlutonium::Weapon* DancingPlutonium::AbstractBaseUnit::GetWeaponEquipped() const
{
	return weapon;
}

sf::Sprite& DancingPlutonium::AbstractBaseUnit::GetSprite()
{
	return sprite;
}

sf::Texture DancingPlutonium::AbstractBaseUnit::GetTexture() const
{
	return texture;
}

sf::Vector2f DancingPlutonium::AbstractBaseUnit::GetPosition() const
{
	return position;
}

sf::FloatRect DancingPlutonium::AbstractBaseUnit::GetBounds() const
{
	return sprite.getGlobalBounds();
}

void DancingPlutonium::AbstractBaseUnit::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

void DancingPlutonium::AbstractBaseUnit::SetHealth(const int _val)
{
	health -= _val;

	health > 0.0f ? isActive = true : isActive = false;
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
	weapon->Draw(_rt);
}
