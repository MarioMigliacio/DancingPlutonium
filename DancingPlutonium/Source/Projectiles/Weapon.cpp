#include "Weapon.h"

/* Now following the principles of using an initializer list to construct. This being the first of all the classes.*/
DancingPlutonium::Weapon::Weapon(const float _fireRate, short _allegiance) : 
	allegiance(_allegiance),
	baseDamage(1.0f), 
	baseFireRate(_fireRate),
	baseVelocity(1.0f),
	weaponPattern(AbstractBaseProjectile::ProjectilePattern::BasicShot),
	weaponDamageState(AbstractBaseProjectile::projectileDamageState::d_Normal),
	weaponFireRateState(AbstractBaseProjectile::projectileFireRateState::r_Normal),
	weaponVelocityRateState(AbstractBaseProjectile::projectileVelocityState::v_Normal)
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
		case AbstractBaseProjectile::projectileDamageState::d_Normal:
			weaponDamageState = AbstractBaseProjectile::projectileDamageState::d_One;
			baseDamage = 1.2f;
			break;

		case AbstractBaseProjectile::projectileDamageState::d_One:
			weaponDamageState = AbstractBaseProjectile::projectileDamageState::d_Two;
			baseDamage = 1.4f;
			break;

		case AbstractBaseProjectile::projectileDamageState::d_Two:
			weaponDamageState = AbstractBaseProjectile::projectileDamageState::d_Three;
			baseDamage = 1.6f;
			break;

		case AbstractBaseProjectile::projectileDamageState::d_Three:
			weaponDamageState = AbstractBaseProjectile::projectileDamageState::d_Four;
			baseDamage = 1.8f;
			break;

		case AbstractBaseProjectile::projectileDamageState::d_Four:
			weaponDamageState = AbstractBaseProjectile::projectileDamageState::d_Max;
			baseDamage = 2.0f;
			break;

		case AbstractBaseProjectile::projectileDamageState::d_Max:
			weaponDamageState = AbstractBaseProjectile::projectileDamageState::d_Max;
			break;

		default:
			break;
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponFireRate()
{
	switch (weaponFireRateState)
	{
		case AbstractBaseProjectile::projectileFireRateState::r_Normal:
			weaponFireRateState = AbstractBaseProjectile::projectileFireRateState::r_One;
			baseFireRate *= 0.8f;
			break;

		case AbstractBaseProjectile::projectileFireRateState::r_One:
			weaponFireRateState = AbstractBaseProjectile::projectileFireRateState::r_Two;
			baseFireRate *= 0.8f;
			break;

		case AbstractBaseProjectile::projectileFireRateState::r_Two:
			weaponFireRateState = AbstractBaseProjectile::projectileFireRateState::r_Three;
			baseFireRate *= 0.8f;
			break;

		case AbstractBaseProjectile::projectileFireRateState::r_Three:
			weaponFireRateState = AbstractBaseProjectile::projectileFireRateState::r_Four;
			baseFireRate *= 0.8f;
			break;

		case AbstractBaseProjectile::projectileFireRateState::r_Four:
			weaponFireRateState = AbstractBaseProjectile::projectileFireRateState::r_Max;
			baseFireRate *= 0.8f;
			break;

		case AbstractBaseProjectile::projectileFireRateState::r_Max:
			break;

		default:
			break;
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponVelocityRate()
{
	switch (weaponVelocityRateState)
	{
		case AbstractBaseProjectile::projectileVelocityState::v_Normal:
			weaponVelocityRateState = AbstractBaseProjectile::projectileVelocityState::v_One;
			baseVelocity = 1.0f;
			break;

		case AbstractBaseProjectile::projectileVelocityState::v_One:
			weaponVelocityRateState = AbstractBaseProjectile::projectileVelocityState::v_Two;
			baseVelocity = 1.25f;
			break;

		case AbstractBaseProjectile::projectileVelocityState::v_Two:
			weaponVelocityRateState = AbstractBaseProjectile::projectileVelocityState::v_Three;
			baseVelocity = 1.5f;
			break;

		case AbstractBaseProjectile::projectileVelocityState::v_Three:
			weaponVelocityRateState = AbstractBaseProjectile::projectileVelocityState::v_Four;
			baseVelocity = 1.75f;
			break;

		case AbstractBaseProjectile::projectileVelocityState::v_Four:
			weaponVelocityRateState = AbstractBaseProjectile::projectileVelocityState::v_Max;
			baseVelocity = 2.0f;
			break;

		case AbstractBaseProjectile::projectileVelocityState::v_Max:
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
	//bool check = false;

	//_dt >= baseFireRate ? check = true : check = false;

	//return check;
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