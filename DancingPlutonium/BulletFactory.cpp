#include "BulletFactory.h"

DancingPlutonium::Bullet* DancingPlutonium::BulletFactory::GetProjectile(ProjectileTypes _toMake, sf::Vector2f& _pos)
{
	switch (_toMake)
	{
	case DancingPlutonium::NoBullet:
		return nullptr;
		break;
	case DancingPlutonium::BasicBullet:
		return new BasicBulletPlayer(_pos);
		break;
	case DancingPlutonium::TripleBullet:
		return new TripleBulletPlayer(_pos);
		break;
	case DancingPlutonium::MacaroniNCheese:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

/*
BasicBullet,
AimedBullet,(upon origin, aims at target)
HomingBullet,(alters trajectory while updating)
StandardLazer,
JoesLazer(the one thats not gay)
[ExplodingDistance optional parameter]
PURPLEBULLET
*/

/*
BasicCannon,
DoubleShot_straight,
TripleShot_gay,
PacketWeapon_SUPERGAY,
PhotonBeam,
*/