#include "Weapon.h"

/* Now following the principles of using an initializer list to construct. This being the first of all the classes.*/
DancingPlutonium::Weapon::Weapon(const float _fireRate, short _allegiance) : 
	allegiance(_allegiance),
	baseDamage(1.0f), 
	baseFireRate(_fireRate),
	baseVelocity(1.0f),
	weaponPattern(AbstractBaseProjectile::ProjectilePattern::BasicShot),
	weaponDamageState(AbstractBaseProjectile::ProjectileDamageState::d_Normal),
	weaponFireRateState(AbstractBaseProjectile::ProjectileFireRateState::r_Normal),
	weaponVelocityRateState(AbstractBaseProjectile::ProjectileVelocityState::v_Normal)
{
}

DancingPlutonium::Weapon::~Weapon()
{
}

void DancingPlutonium::Weapon::UpgradeWeaponPattern()
{
	switch (weaponPattern)
	{
		case AbstractBaseProjectile::ProjectilePattern::BasicShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::DoubleShot;
			break;

		case AbstractBaseProjectile::ProjectilePattern::DoubleShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::TripleShot;
			break;

		case AbstractBaseProjectile::ProjectilePattern::TripleShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::GrowingShot;
			break;

		case AbstractBaseProjectile::ProjectilePattern::GrowingShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::BasicShot;	// loop to beginning (develop the rest of the bullets and change this)
			break;

		case AbstractBaseProjectile::ProjectilePattern::AimedShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::DoubleShot;
			break;

		case AbstractBaseProjectile::ProjectilePattern::IncendiaryShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::AimedShot;
			break;

		case AbstractBaseProjectile::ProjectilePattern::HomingShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::TripleShot;
			break;

		case AbstractBaseProjectile::ProjectilePattern::StandardLazer:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::JoesLazer;
			break;

		case AbstractBaseProjectile::ProjectilePattern::JoesLazer:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::QuadShot;
			break;

		case AbstractBaseProjectile::ProjectilePattern::QuadShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::PhotonPacket;
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonPacket:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::PhotonStream;
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonStream:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::PhotonTriplet;
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonTriplet:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::PhotonQuartet;
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonQuartet:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::IMMAFIRINMAHLAZOR;
			break;

		default:
			break;
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponDamage()
{
	switch (weaponDamageState)
	{
		case AbstractBaseProjectile::ProjectileDamageState::d_Normal:
			weaponDamageState = AbstractBaseProjectile::ProjectileDamageState::d_One;
			baseDamage = 1.2f;
			break;

		case AbstractBaseProjectile::ProjectileDamageState::d_One:
			weaponDamageState = AbstractBaseProjectile::ProjectileDamageState::d_Two;
			baseDamage = 1.4f;
			break;

		case AbstractBaseProjectile::ProjectileDamageState::d_Two:
			weaponDamageState = AbstractBaseProjectile::ProjectileDamageState::d_Three;
			baseDamage = 1.6f;
			break;

		case AbstractBaseProjectile::ProjectileDamageState::d_Three:
			weaponDamageState = AbstractBaseProjectile::ProjectileDamageState::d_Four;
			baseDamage = 1.8f;
			break;

		case AbstractBaseProjectile::ProjectileDamageState::d_Four:
			weaponDamageState = AbstractBaseProjectile::ProjectileDamageState::d_Max;
			baseDamage = 2.0f;
			break;

		case AbstractBaseProjectile::ProjectileDamageState::d_Max:
			weaponDamageState = AbstractBaseProjectile::ProjectileDamageState::d_Max;
			break;

		default:
			break;
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponFireRate()
{
	switch (weaponFireRateState)
	{
		case AbstractBaseProjectile::ProjectileFireRateState::r_Normal:
			weaponFireRateState = AbstractBaseProjectile::ProjectileFireRateState::r_One;
			baseFireRate *= 0.9f;
			break;

		case AbstractBaseProjectile::ProjectileFireRateState::r_One:
			weaponFireRateState = AbstractBaseProjectile::ProjectileFireRateState::r_Two;
			baseFireRate *= 0.9f;
			break;

		case AbstractBaseProjectile::ProjectileFireRateState::r_Two:
			weaponFireRateState = AbstractBaseProjectile::ProjectileFireRateState::r_Three;
			baseFireRate *= 0.9f;
			break;

		case AbstractBaseProjectile::ProjectileFireRateState::r_Three:
			weaponFireRateState = AbstractBaseProjectile::ProjectileFireRateState::r_Four;
			baseFireRate *= 0.9f;
			break;

		case AbstractBaseProjectile::ProjectileFireRateState::r_Four:
			weaponFireRateState = AbstractBaseProjectile::ProjectileFireRateState::r_Max;
			baseFireRate *= 0.9f;
			break;

		case AbstractBaseProjectile::ProjectileFireRateState::r_Max:
			break;

		default:
			break;
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponVelocityRate()
{
	switch (weaponVelocityRateState)
	{
		case AbstractBaseProjectile::ProjectileVelocityState::v_Normal:
			weaponVelocityRateState = AbstractBaseProjectile::ProjectileVelocityState::v_One;
			baseVelocity = 1.0f;
			break;

		case AbstractBaseProjectile::ProjectileVelocityState::v_One:
			weaponVelocityRateState = AbstractBaseProjectile::ProjectileVelocityState::v_Two;
			baseVelocity = 1.25f;
			break;

		case AbstractBaseProjectile::ProjectileVelocityState::v_Two:
			weaponVelocityRateState = AbstractBaseProjectile::ProjectileVelocityState::v_Three;
			baseVelocity = 1.5f;
			break;

		case AbstractBaseProjectile::ProjectileVelocityState::v_Three:
			weaponVelocityRateState = AbstractBaseProjectile::ProjectileVelocityState::v_Four;
			baseVelocity = 1.75f;
			break;

		case AbstractBaseProjectile::ProjectileVelocityState::v_Four:
			weaponVelocityRateState = AbstractBaseProjectile::ProjectileVelocityState::v_Max;
			baseVelocity = 2.0f;
			break;

		case AbstractBaseProjectile::ProjectileVelocityState::v_Max:
			break;

		default:
			break;
	}
}

void DancingPlutonium::Weapon::SetWeaponPattern(const sf::Uint32 _pat)
{
	weaponPattern = _pat;
}

void DancingPlutonium::Weapon::SetWeaponDamageState(const sf::Uint32 _dmg)
{
	weaponDamageState = _dmg;
}

void DancingPlutonium::Weapon::SetWeaponFireRateState(const sf::Uint32 _rate)
{
	weaponFireRateState = _rate;
}

void DancingPlutonium::Weapon::SetWeaponVelocityState(const sf::Uint32 _veloc)
{
	weaponVelocityRateState = _veloc;
}

bool DancingPlutonium::Weapon::CanShoot(const float _dt)
{
	return _dt >= baseFireRate;
}

DancingPlutonium::AbstractBaseProjectile* DancingPlutonium::Weapon::SpawnBullet(sf::Vector2f& _pos)
{
	AbstractBaseProjectile* omgDoesThisWork = nullptr;

	switch (weaponPattern)
	{
		case AbstractBaseProjectile::ProjectilePattern::BasicShot:
			// work out this constructor
			omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::BasicShot, _pos, 
				baseDamage, baseVelocity, allegiance); 
			break;

		case AbstractBaseProjectile::ProjectilePattern::IncendiaryShot:
			break;

		case AbstractBaseProjectile::ProjectilePattern::GrowingShot:
			// work out this constructor
			omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::GrowingShot, _pos,
				baseDamage, baseVelocity, allegiance); 
			break;

		case AbstractBaseProjectile::ProjectilePattern::AimedShot:
			break;
		case AbstractBaseProjectile::ProjectilePattern::DoubleShot:
			// work out this constructor
			omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::DoubleShot, _pos,
				baseDamage, baseVelocity, allegiance); 
			break;

		case AbstractBaseProjectile::ProjectilePattern::HomingShot:
			break;

		case AbstractBaseProjectile::ProjectilePattern::TripleShot:
			// work out this constructor
			omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::TripleShot, _pos,
				baseDamage, baseVelocity, allegiance); 
			break;

		case AbstractBaseProjectile::ProjectilePattern::StandardLazer:
			break;

		case AbstractBaseProjectile::ProjectilePattern::JoesLazer:
			break;

		case AbstractBaseProjectile::ProjectilePattern::QuadShot:
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonPacket:
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonStream:
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonTriplet:
			break;

		case AbstractBaseProjectile::ProjectilePattern::PhotonQuartet:
			break;

		default:
			break;
	}

	return omgDoesThisWork;
}