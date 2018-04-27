#include "Weapon.h"

sf::Uint32 DancingPlutonium::Weapon::weaponPattern = Projectile::ProjectilePattern::NoBullet;
sf::Uint32 DancingPlutonium::Weapon::weaponDamageState = WeaponDamageState::d_Uninitialized;
sf::Uint32 DancingPlutonium::Weapon::weaponFireRateState = WeaponFireRateState::r_Uninitialized;
sf::Uint32 DancingPlutonium::Weapon::weaponVelocityRateState = WeaponVelocityState::v_Uninitialized;

DancingPlutonium::Weapon::Weapon()
{
	InitializeWeaponSystem();
	baseDamage = 1.0f;
	baseFireRate = 1.0f;
	baseVelocity = 1.0f;
}

DancingPlutonium::Weapon::~Weapon()
{
	for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
	{
		delete ammunition[i];
		ammunition.erase(ammunition.begin() + i);		
	}
}

float DancingPlutonium::Weapon::AddMunition(sf::Vector2f& _pos, float _dt)
{
	/* it did */
	Projectile* omgDoesThisWork;
	accumulator += _dt;

	if (accumulator >= fireRate)
	{
		switch (weaponPattern)
		{
			case Projectile::ProjectilePattern::BasicShot:
				omgDoesThisWork = BulletFactory::GetProjectile(Projectile::ProjectilePattern::BasicShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::IncendiaryShot:
				break;
			case Projectile::ProjectilePattern::GrowingShot:
				omgDoesThisWork = BulletFactory::GetProjectile(Projectile::ProjectilePattern::GrowingShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::AimedShot:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::DoubleShot:
				omgDoesThisWork = BulletFactory::GetProjectile(Projectile::ProjectilePattern::DoubleShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::HomingShot:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::TripleShot:
				omgDoesThisWork = BulletFactory::GetProjectile(Projectile::ProjectilePattern::TripleShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::StandardLazer:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::JoesLazer:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::QuadShot:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::PhotonPacket:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::PhotonStream:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::PhotonTriplet:
				accumulator = 0.0f;
				break;
			case Projectile::ProjectilePattern::PhotonQuartet:
				accumulator = 0.0f;
				break;
			default:
				break;
		}
	}

	return accumulator;
}

DancingPlutonium::Projectile* DancingPlutonium::Weapon::GetIndexOfAmmunition(int _index)
{
	if (static_cast<int>(ammunition.size()) > 0 && static_cast<int>(ammunition.size()) > _index)
	{
		return ammunition[_index];
	}

	return nullptr;
}

int DancingPlutonium::Weapon::GetSizeOfAmmunition()
{
	return static_cast<int>(ammunition.size());
}

void DancingPlutonium::Weapon::Update(sf::RenderTarget& _rt, float _dt)
{
	if (ammunition.size() != 0)
	{
		CleanAmmunition(_rt);

		for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
		{
			ammunition[i]->Update(_dt);
		}
	}
}

void DancingPlutonium::Weapon::Draw(sf::RenderTarget& _rt)
{
	for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
	{
		ammunition[i]->Draw(_rt);
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponFireRate()
{
	switch (weaponFireRateState)
	{
		case WeaponFireRateState::r_Normal:
			weaponFireRateState = WeaponFireRateState::r_One;
			fireRate *= 0.8f;
			break;
		case WeaponFireRateState::r_One:
			weaponFireRateState = WeaponFireRateState::r_Two;
			fireRate *= 0.8f;
			break;
		case WeaponFireRateState::r_Two:
			weaponFireRateState = WeaponFireRateState::r_Three;
			fireRate *= 0.8f;
			break;
		case WeaponFireRateState::r_Three:
			weaponFireRateState = WeaponFireRateState::r_Four;
			fireRate *= 0.8f;
			break;
		case WeaponFireRateState::r_Four:
			weaponFireRateState = WeaponFireRateState::r_Max;
			fireRate *= 0.8f;
			break;
		case WeaponFireRateState::r_Max:
			break;
		default:
			break;
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponVelocityRate()
{
	switch (weaponVelocityRateState)
	{
		case WeaponVelocityState::v_Normal:
			weaponVelocityRateState = WeaponVelocityState::v_One;
			baseVelocity *= 2.0;
			break;
		case WeaponVelocityState::v_One:
			weaponVelocityRateState = WeaponVelocityState::v_Two;
			baseVelocity *= 3.0f;
			break;
		case WeaponVelocityState::v_Two:
			weaponVelocityRateState = WeaponVelocityState::v_Three;
			baseVelocity *= 5.0f;
			break;
		case WeaponVelocityState::v_Three:
			weaponVelocityRateState = WeaponVelocityState::v_Four;
			baseVelocity *= 7.5f;
			break;
		case WeaponVelocityState::v_Four:
			weaponVelocityRateState = WeaponVelocityState::v_Max;
			baseVelocity *= 10.0f;
			break;
		case WeaponVelocityState::v_Max:
			break;
		default:
			break;
	}
}

void DancingPlutonium::Weapon::SetWeaponDamageState(Projectile* _shot)
{
	switch (weaponDamageState)
	{
		case WeaponDamageState::d_Normal:
			_shot->SetDamage(_shot->GetDamage() * 1.0f);
			break;
		case WeaponDamageState::d_One:
			_shot->SetDamage(_shot->GetDamage() * 1.2f);
			break;
		case WeaponDamageState::d_Two:
			_shot->SetDamage(_shot->GetDamage() * 1.4f);
			break;
		case WeaponDamageState::d_Three:
			_shot->SetDamage(_shot->GetDamage() * 1.6f);
			break;
		case WeaponDamageState::d_Four:
			_shot->SetDamage(_shot->GetDamage() * 1.8f);
			break;
		case WeaponDamageState::d_Max:
			_shot->SetDamage(_shot->GetDamage() * 2.0f);
			break;
		default:
			break;
	}
}

void DancingPlutonium::Weapon::SetWeaponVelocityState(Projectile* _shot)
{
	switch (weaponVelocityRateState)
	{
	case WeaponVelocityState::v_Normal:
		_shot->SetSpeed(_shot->GetSpeed() * 1.0f);
		break;
	case WeaponVelocityState::v_One:
		_shot->SetSpeed(_shot->GetSpeed() * 1.2f);
		break;
	case WeaponVelocityState::v_Two:
		_shot->SetSpeed(_shot->GetSpeed() * 1.4f);
		break;
	case WeaponVelocityState::v_Three:
		_shot->SetSpeed(_shot->GetSpeed() * 1.6f);
		break;
	case WeaponVelocityState::v_Four:
		_shot->SetSpeed(_shot->GetSpeed() * 1.8f);
		break;
	case WeaponVelocityState::v_Max:
		_shot->SetSpeed(_shot->GetSpeed() * 2.0f);
		break;
	default:
		break;
	}
}

void DancingPlutonium::Weapon::InitializeWeaponSystem()
{
	weaponPattern = Projectile::ProjectilePattern::BasicShot;
	weaponDamageState = WeaponDamageState::d_Normal;
	weaponFireRateState = WeaponFireRateState::r_Normal;
	weaponVelocityRateState = WeaponVelocityState::v_Normal;
	fireRate = 0.5f;
	accumulator = 1.0f;
	ammunition = std::vector<Projectile*>();
}

sf::Uint32 DancingPlutonium::Weapon::GetPattern()
{
	return weaponPattern;
}

void DancingPlutonium::Weapon::UpgradeWeaponPattern()
{
	switch (weaponPattern)
	{
		case Projectile::ProjectilePattern::BasicShot:
			weaponPattern = Projectile::ProjectilePattern::GrowingShot;
			break;
		case Projectile::ProjectilePattern::GrowingShot:
			weaponPattern = Projectile::ProjectilePattern::DoubleShot;
			break;
		case Projectile::ProjectilePattern::IncendiaryShot:
			weaponPattern = Projectile::ProjectilePattern::AimedShot;
			break;
		case Projectile::ProjectilePattern::AimedShot:
			weaponPattern = Projectile::ProjectilePattern::DoubleShot;
			break;
		case Projectile::ProjectilePattern::DoubleShot:
			weaponPattern = Projectile::ProjectilePattern::TripleShot;
			break;
		case Projectile::ProjectilePattern::HomingShot:
			weaponPattern = Projectile::ProjectilePattern::TripleShot;
			break;
		case Projectile::ProjectilePattern::TripleShot:
			weaponPattern = Projectile::ProjectilePattern::BasicShot;
			break;
		case Projectile::ProjectilePattern::StandardLazer:
			weaponPattern = Projectile::ProjectilePattern::JoesLazer;
			break;
		case Projectile::ProjectilePattern::JoesLazer:
			weaponPattern = Projectile::ProjectilePattern::QuadShot;
			break;
		case Projectile::ProjectilePattern::QuadShot:
			weaponPattern = Projectile::ProjectilePattern::PhotonPacket;
			break;
		case Projectile::ProjectilePattern::PhotonPacket:
			weaponPattern = Projectile::ProjectilePattern::PhotonStream;
			break;
		case Projectile::ProjectilePattern::PhotonStream:
			weaponPattern = Projectile::ProjectilePattern::PhotonTriplet;
			break;
		case Projectile::ProjectilePattern::PhotonTriplet:
			weaponPattern = Projectile::ProjectilePattern::PhotonQuartet;
			break;
		case Projectile::ProjectilePattern::PhotonQuartet:
			weaponPattern = Projectile::ProjectilePattern::IMMAFIRINMAHLAZOR;
			break;
		default:
			break;
	}
}

void DancingPlutonium::Weapon::UpgradeWeaponDamage()
{
	switch (weaponDamageState)
	{
		case WeaponDamageState::d_Normal:
			weaponDamageState = WeaponDamageState::d_One;
		break;
		case WeaponDamageState::d_One:
			weaponDamageState = WeaponDamageState::d_Two;
			break;
		case WeaponDamageState::d_Two:
			weaponDamageState = WeaponDamageState::d_Three;
			break;
		case WeaponDamageState::d_Three:
			weaponDamageState = WeaponDamageState::d_Four;
			break;
		case WeaponDamageState::d_Four:
			weaponDamageState = WeaponDamageState::d_Max;
			break;
		case WeaponDamageState::d_Max:
			weaponDamageState = WeaponDamageState::d_Max;
			break;
		default:
			break;
	}
}



void DancingPlutonium::Weapon::CleanAmmunition(sf::RenderTarget& _rt)
{
	if (ammunition.size() != 0)
	{
		for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
		{
			if (ammunition[i]->GetActiveState(_rt) == false)
			{
				delete ammunition[i];
				ammunition.erase(ammunition.begin() + i);
			}
		}
	}
}
