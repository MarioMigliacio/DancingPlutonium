#include "BulletFactory.h"

DancingPlutonium::Projectile* DancingPlutonium::BulletFactory::GetProjectile(ProjectileType _toMake, sf::Vector2f& _pos)
{
	Projectile* retVal;

	switch (_toMake)
	{
		case DancingPlutonium::ProjectileType::None:
			retVal = nullptr;
			break;
		case DancingPlutonium::ProjectileType::BasicBullet:
			retVal = new BasicProjectile(_pos);
			break;
		case DancingPlutonium::ProjectileType::AimedBullet:
			retVal = nullptr;
			break;
		case DancingPlutonium::ProjectileType::HomingBullet:
			retVal = nullptr;
			break;
		case DancingPlutonium::ProjectileType::IncendiaryBullet:
			retVal = nullptr;
			break;
		case DancingPlutonium::ProjectileType::Lazer:
			retVal = nullptr;
			break;
		case DancingPlutonium::ProjectileType::RealLazer:
			retVal = nullptr;
			break;
		default:
			retVal = nullptr;
			break;
	}

	return retVal;
}