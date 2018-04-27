#pragma once

#include <SFML\Graphics.hpp>
#include "Projectile.h"
#include "Weapon_BasicShot.h"
#include "Weapon_GrowingShot.h"
#include "Weapon_TripleShot.h"
#include "Enums.h"

namespace DancingPlutonium
{
	/* BulletFactory deploys the factory design pattern and uses a Static member function to return projectile object references based on input parameters */
	class BulletFactory
	{
	private:
		#pragma region Ctor

		/* Disallow access to creating the BulletFactory class. It holds useful static methods which can be queried by using syntax: BulletFactory::<member name> */
		BulletFactory() {}

		#pragma endregion

	public:
		#pragma region Dtor
		
		/* The BulletFactory destructor */
		~BulletFactory() {}
		
		#pragma endregion

		#pragma region Factory Method

		/* Gets a reference to a Projectile based on enum type, and position input parameters */
		static Projectile* GetProjectile(Projectile::ProjectilePattern _toMake, sf::Vector2f& _pos);

		#pragma endregion
	};		
}