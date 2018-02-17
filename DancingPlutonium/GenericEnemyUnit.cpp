#include "GenericEnemyUnit.h"

int GenericEnemyUnit::GetValue() const
{
	return value;
}

int GenericEnemyUnit::GetHealth() const
{
	return health;
}

int GenericEnemyUnit::GetFireDamage() const
{
	return fireDamage;
}

float GenericEnemyUnit::GetFireRate() const
{
	return fireRate;
}

float GenericEnemyUnit::GetSpeed() const
{
	return speed;
}

// test this method!
bool GenericEnemyUnit::GetActiveState(const sf::RenderTarget& _rt) const
{
	bool check = ((position.x >= 0.0f && position.x <= _rt.getSize().x) && (position.y >= 0.0f && position.y <= _rt.getSize().y)
		&& health > 0);

	return ((position.x >= 0.0f && position.x <= _rt.getSize().x) && (position.y >= 0.0f && position.y <= _rt.getSize().y)
		&& health > 0);
}

// test this method!
bool GenericEnemyUnit::CheckIfColliding(const Bullet& _shot) const
{
	bool check = GetBounds().contains(_shot.GetPosition());

	return (GetBounds().contains(_shot.GetPosition()));
}

sf::String GenericEnemyUnit::GetName() const
{
	return name;
}

sf::Sprite GenericEnemyUnit::GetSprite() const
{
	return sprite;
}

sf::Texture GenericEnemyUnit::GetTexture() const
{
	return texture;
}

sf::Vector2f GenericEnemyUnit::GetPosition() const
{
	return position;
}

sf::FloatRect GenericEnemyUnit::GetBounds() const
{
	return sprite.getGlobalBounds();
}

void GenericEnemyUnit::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
}

void GenericEnemyUnit::SetHealth(const int _val)
{
	health -= _val;
}

void GenericEnemyUnit::SpawnRandomly(const sf::RenderTarget& _rt)
{
	int randomX = _rt.getSize().x - sprite.getGlobalBounds().width / 2.0f;
	randomX = RandomIntRange(sprite.getGlobalBounds().width / 2.0f, randomX) % randomX;
	
	SetPosition(sf::Vector2f((float)randomX, 16.0f));
}

// IMPORTANT DO THIS "SOON"
void GenericEnemyUnit::Update(float _dt)
{
}

// IMPORTANT DO THIS "SOON"
void GenericEnemyUnit::Draw(const sf::RenderTarget& _rt) const
{
}
