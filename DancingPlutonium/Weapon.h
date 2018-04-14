#pragma once

#include <SFML\Graphics.hpp>
#include "BulletFactory.h"
#include "Projectile.h"
#include "Enums.h"

namespace DancingPlutonium
{
	class Weapon
	{		
	public:
		Weapon(sf::RenderTarget& _rt);
		
		sf::Uint32 GetWeaponType();
		sf::Uint32 GetWeaponPattern();

	public:
		void Fire();

	private:
		std::vector<Projectile*> ammunition;
		static sf::Uint32 weaponType;
		static sf::Uint32 weaponPattern;
	};
}