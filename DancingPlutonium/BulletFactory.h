#pragma once

#include <SFML\Graphics.hpp>
#include "Projectile.h"
#include "BasicBulletPlayer.h"
#include "TripleBulletPlayer.h"
#include "Enums.h"

namespace DancingPlutonium
{
	class BulletFactory
	{
	private:
		BulletFactory() {}
	public:
		static Projectile* GetProjectile(ProjectileTypes _toMake, sf::Vector2f& _pos);
	};
}