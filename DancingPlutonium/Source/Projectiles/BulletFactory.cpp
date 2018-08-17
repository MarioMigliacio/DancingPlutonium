#include "BulletFactory.h"

DancingPlutonium::AbstractBaseProjectile* DancingPlutonium::BulletFactory::GetProjectile(const AbstractBaseProjectile::ProjectilePattern _toMake, const sf::Vector2f& _pos, 
	float _dmg, float _vel, short _alle)
{
	AbstractBaseProjectile* retVal;

	switch (_toMake)
	{
		case DancingPlutonium::AbstractBaseProjectile::ProjectilePattern::BasicShot:
			_dmg > 0.0f ? retVal = new Weapon_BasicShot(_pos, _dmg, _vel, _alle) :	retVal = new Weapon_BasicShot(_pos);
			break;
		case DancingPlutonium::AbstractBaseProjectile::ProjectilePattern::GrowingShot:
			retVal = new Weapon_GrowingShot(_pos);
			break;
		case DancingPlutonium::AbstractBaseProjectile::ProjectilePattern::DoubleShot:
			retVal = new Weapon_DoubleShot(_pos);
			break;
		case DancingPlutonium::AbstractBaseProjectile::ProjectilePattern::TripleShot:
			retVal = new Weapon_TripleShot(_pos);
			break;
		default:
			retVal = nullptr;
			break;
	}

	return retVal;
}