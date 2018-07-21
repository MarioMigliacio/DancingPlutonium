#include "Level.h"

bool DancingPlutonium::Level::CheckForCollision(const sf::Sprite& _object1, const sf::Sprite& _object2)
{
	if (Collision::BoundingBoxTest(_object1, _object2))
	{
		return true;
	}

	return false;
}

void DancingPlutonium::Level::DoUnitCollisionDamage(AbstractBaseUnit& _unit1, AbstractBaseUnit& _unit2)
{
	_unit1.SetHealth(100);
	_unit2.SetHealth(100);
}

void DancingPlutonium::Level::DoProjectileCollisionDamage(AbstractBaseUnit& _unit, AbstractBaseProjectile& _object2)
{
	_unit.SetHealth(_object2.GetDamage());
}

void DancingPlutonium::Level::EnemyUnitDeath(AbstractBaseUnit& _unit, AbstractBaseUnit& _player)
{

}

void DancingPlutonium::Level::PlayerLoseLife(PlutoniumShip& _unit)
{
	_unit.RemoveLife();

	if (_unit.LivesRemaining() < 0)
	{
		// Gameover :(
	}
}

void DancingPlutonium::Level::PlayerGainLife(PlutoniumShip& _unit)
{
	_unit.AddLife();
}

void DancingPlutonium::Level::UpdateEnemyShipContainer(std::vector<AbstractBaseUnit*>& _from)
{
	enemyShipContainer = _from;
}

void DancingPlutonium::Level::UpdatePlayerShipContainer(std::vector<AbstractBaseUnit*>& _from)
{
	playerShipContainer = _from;
}

void DancingPlutonium::Level::UpdateEnemyProjectileContainer(std::vector<AbstractBaseProjectile*>& _from)
{
	enemyProjectileContainer = _from;
}

void DancingPlutonium::Level::UpdatePlayerProjectileContainer(std::vector<AbstractBaseProjectile*>& _from)
{
	playerProjectileContainer = _from;
}

void DancingPlutonium::Level::Update(float _dt, sf::RenderTarget& _rt)
{

}

void DancingPlutonium::Level::Draw(sf::RenderTarget& _rt)
{

}
