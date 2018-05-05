#include "Weapon.h"

DancingPlutonium::Weapon::Weapon(const float _fireRate, short _allegiance)
{
	InitializeWeaponSystem(_fireRate);
	allegiance = _allegiance;
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

bool DancingPlutonium::Weapon::AddMunition(sf::Vector2f& _pos, float _dt)
{
	/* it did */
	AbstractBaseProjectile* omgDoesThisWork;
	bool check = false;

	if (_dt >= fireRate)
	{
		switch (weaponPattern)
		{
			case AbstractBaseProjectile::ProjectilePattern::BasicShot:
				omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::BasicShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				SetProjectileAllegiance(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				check = true;
				break;
			case AbstractBaseProjectile::ProjectilePattern::IncendiaryShot:
				break;
			case AbstractBaseProjectile::ProjectilePattern::GrowingShot:
				omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::GrowingShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				SetProjectileAllegiance(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				check = true;
				break;
			case AbstractBaseProjectile::ProjectilePattern::AimedShot:
				break;
			case AbstractBaseProjectile::ProjectilePattern::DoubleShot:
				omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::DoubleShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				SetProjectileAllegiance(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				check = true;
				break;
			case AbstractBaseProjectile::ProjectilePattern::HomingShot:
				break;
			case AbstractBaseProjectile::ProjectilePattern::TripleShot:
				omgDoesThisWork = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::TripleShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 
				SetWeaponVelocityState(omgDoesThisWork);
				SetProjectileAllegiance(omgDoesThisWork);
				ammunition.push_back(omgDoesThisWork);
				check = true;
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
	}

	return check;
}

DancingPlutonium::AbstractBaseProjectile* DancingPlutonium::Weapon::GetIndexOfAmmunition(int _index)
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

std::vector<DancingPlutonium::AbstractBaseProjectile*> DancingPlutonium::Weapon::GetAmmunitionContainer()
{
	return ammunition;
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
			baseVelocity = 1.0f;
			break;
		case WeaponVelocityState::v_One:
			weaponVelocityRateState = WeaponVelocityState::v_Two;
			baseVelocity = 1.25f;
			break;
		case WeaponVelocityState::v_Two:
			weaponVelocityRateState = WeaponVelocityState::v_Three;
			baseVelocity = 1.5f;
			break;
		case WeaponVelocityState::v_Three:
			weaponVelocityRateState = WeaponVelocityState::v_Four;
			baseVelocity = 1.75f;
			break;
		case WeaponVelocityState::v_Four:
			weaponVelocityRateState = WeaponVelocityState::v_Max;
			baseVelocity = 2.0f;
			break;
		case WeaponVelocityState::v_Max:
			break;
		default:
			break;
	}
}

void DancingPlutonium::Weapon::SetWeaponDamageState(AbstractBaseProjectile* _shot)
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

void DancingPlutonium::Weapon::SetWeaponVelocityState(AbstractBaseProjectile* _shot)
{
	_shot->SetSpeed(_shot->GetSpeed() * baseVelocity);
}

void DancingPlutonium::Weapon::SetProjectileAllegiance(AbstractBaseProjectile* _shot)
{
	_shot->SetAllegiance(allegiance);
}

void DancingPlutonium::Weapon::InitializeWeaponSystem(const float _fireRate)
{
	weaponPattern = AbstractBaseProjectile::ProjectilePattern::BasicShot;
	weaponDamageState = WeaponDamageState::d_Normal;
	weaponFireRateState = WeaponFireRateState::r_Normal;
	weaponVelocityRateState = WeaponVelocityState::v_Normal;
	fireRate = _fireRate;
	ammunition = std::vector<AbstractBaseProjectile*>();
}

sf::Uint32 DancingPlutonium::Weapon::GetPattern()
{
	return weaponPattern;
}

void DancingPlutonium::Weapon::UpgradeWeaponPattern()
{
	switch (weaponPattern)
	{
		case AbstractBaseProjectile::ProjectilePattern::BasicShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::GrowingShot;
			break;
		case AbstractBaseProjectile::ProjectilePattern::GrowingShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::DoubleShot;
			break;
		case AbstractBaseProjectile::ProjectilePattern::IncendiaryShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::AimedShot;
			break;
		case AbstractBaseProjectile::ProjectilePattern::AimedShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::DoubleShot;
			break;
		case AbstractBaseProjectile::ProjectilePattern::DoubleShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::TripleShot;
			break;
		case AbstractBaseProjectile::ProjectilePattern::HomingShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::TripleShot;
			break;
		case AbstractBaseProjectile::ProjectilePattern::TripleShot:
			weaponPattern = AbstractBaseProjectile::ProjectilePattern::BasicShot;
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
	if (ammunition.size() > 0)
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
