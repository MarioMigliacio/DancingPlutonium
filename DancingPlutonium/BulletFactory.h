#pragma once

#include <SFML\Graphics.hpp>
#include "Bullet.h"
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
		static Bullet* GetProjectile(ProjectileTypes _toMake, sf::Vector2f& _pos);
	};
}