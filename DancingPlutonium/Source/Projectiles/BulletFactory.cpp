#include "BulletFactory.h"

DancingPlutonium::AbstractBaseProjectile* DancingPlutonium::BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern _toMake, sf::Vector2f& _pos)
{
	AbstractBaseProjectile* retVal;

	switch (_toMake)
	{
		case DancingPlutonium::AbstractBaseProjectile::ProjectilePattern::BasicShot:
			retVal = new Weapon_BasicShot(_pos);
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