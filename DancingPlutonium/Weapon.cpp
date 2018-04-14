#include "Weapon.h"

sf::Uint32 DancingPlutonium::Weapon::weaponType = ProjectileType::None;
sf::Uint32 DancingPlutonium::Weapon::weaponPattern = ProjectilePattern::NoBullet;

DancingPlutonium::Weapon::Weapon(sf::RenderTarget& _rt)
{
	
}

sf::Uint32 DancingPlutonium::Weapon::GetWeaponType()
{
	return weaponType;
}

sf::Uint32 DancingPlutonium::Weapon::GetWeaponPattern()
{
	return weaponPattern;
}

void DancingPlutonium::Weapon::Fire()
{
}
