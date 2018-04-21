#include "BulletFactory.h"

DancingPlutonium::Projectile* DancingPlutonium::BulletFactory::GetProjectile(ProjectilePattern _toMake, sf::Vector2f& _pos)
{
	Projectile* retVal;

	switch (_toMake)
	{
	case DancingPlutonium::ProjectilePattern::BasicShot:
			retVal = new BasicProjectile(_pos);
			break;
	case DancingPlutonium::ProjectilePattern::TripleShot:
			retVal = new Weapon_TripleShot(_pos);
			break;
		default:
			retVal = nullptr;
			break;
	}

	return retVal;
}