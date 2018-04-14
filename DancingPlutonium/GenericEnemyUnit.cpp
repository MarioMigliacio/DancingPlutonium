#include "GenericEnemyUnit.h"

int DancingPlutonium::GenericEnemyUnit::GetValue() const
{
	return value;
}

int DancingPlutonium::GenericEnemyUnit::GetHealth() const
{
	return health;
}

float DancingPlutonium::GenericEnemyUnit::GetDamageMultiplier() const
{
	return damageMultiplier;
}

float DancingPlutonium::GenericEnemyUnit::GetFireRate() const
{
	return fireRate;
}

float DancingPlutonium::GenericEnemyUnit::GetSpeed() const
{
	return speed;
}

// test this method!
bool DancingPlutonium::GenericEnemyUnit::GetActiveState(const sf::RenderTarget& _rt) const
{
	bool check = ((position.x >= 0.0f && position.x <= _rt.getSize().x) && (position.y >= 0.0f && position.y <= _rt.getSize().y)
		&& health > 0);

	return ((position.x >= 0.0f && position.x <= _rt.getSize().x) && (position.y >= 0.0f && position.y <= _rt.getSize().y)
		&& health > 0);
}

// test this method!
bool DancingPlutonium::GenericEnemyUnit::CheckIfColliding(const Projectile& _shot) const
{
	bool check = GetBounds().contains(_shot.GetPosition());

	return (GetBounds().contains(_shot.GetPosition()));
}

sf::Sprite DancingPlutonium::GenericEnemyUnit::GetSprite() const
{
	return sprite;
}

sf::Texture DancingPlutonium::GenericEnemyUnit::GetTexture() const
{
	return texture;
}

sf::Vector2f DancingPlutonium::GenericEnemyUnit::GetPosition() const
{
	return position;
}

sf::FloatRect DancingPlutonium::GenericEnemyUnit::GetBounds() const
{
	return sprite.getGlobalBounds();
}

void DancingPlutonium::GenericEnemyUnit::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

void DancingPlutonium::GenericEnemyUnit::SetHealth(const int _val)
{
	health -= _val;
}

void DancingPlutonium::GenericEnemyUnit::SpawnRandomly(const sf::RenderTarget& _rt)
{
	int randomX = static_cast<int>(_rt.getSize().x - sprite.getGlobalBounds().width / 2.0f);
	randomX = RandomIntRange(static_cast<int>(sprite.getGlobalBounds().width / 2.0f), randomX) % randomX;
	
	SetPosition(sf::Vector2f(static_cast<float>(randomX), 16.0f));
}

// IMPORTANT DO THIS "SOON"
void DancingPlutonium::GenericEnemyUnit::Update(float _dt)
{
}

