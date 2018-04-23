#include "Weapon.h"

sf::Uint32 DancingPlutonium::Weapon::weaponPattern = ProjectilePattern::NoBullet;
sf::Uint32 DancingPlutonium::Weapon::weaponDamageState = WeaponDamageState::d_Uninitialized;
sf::Uint32 DancingPlutonium::Weapon::weaponFireRateState = WeaponFireRateState::r_Uninitialized;

DancingPlutonium::Weapon::Weapon()
{
	InitializeWeaponSystem();
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
			case ProjectilePattern::BasicShot:
				omgDoesThisWork = BulletFactory::GetProjectile(ProjectilePattern::BasicShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 4/22/2018 - alter the bullet based on damage state
				ammunition.push_back(omgDoesThisWork);
				accumulator = 0.0f;
				break;
			case ProjectilePattern::IncendiaryShot:
				break;
			case ProjectilePattern::GrowingShot:
				omgDoesThisWork = BulletFactory::GetProjectile(ProjectilePattern::GrowingShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 4/22/2018 - alter the bullet based on damage state
				ammunition.push_back(omgDoesThisWork);
				accumulator = 0.0f;
				break;
			case ProjectilePattern::AimedShot:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::DoubleShot:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::HomingShot:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::TripleShot:
				omgDoesThisWork = BulletFactory::GetProjectile(ProjectilePattern::TripleShot, _pos);
				SetWeaponDamageState(omgDoesThisWork);		// this needs to be tested 4/22/2018 - alter the bullet based on damage state
				ammunition.push_back(omgDoesThisWork);
				accumulator = 0.0f;
				break;
			case ProjectilePattern::StandardLazer:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::JoesLazer:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::QuadShot:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::PhotonPacket:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::PhotonStream:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::PhotonTriplet:
				accumulator = 0.0f;
				break;
			case ProjectilePattern::PhotonQuartet:
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

void DancingPlutonium::Weapon::InitializeWeaponSystem()
{
	weaponPattern = ProjectilePattern::BasicShot;
	weaponDamageState = WeaponDamageState::d_Normal;
	weaponFireRateState = WeaponFireRateState::r_Normal;
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
		case ProjectilePattern::BasicShot:
			weaponPattern = ProjectilePattern::GrowingShot;
			break;
		case ProjectilePattern::GrowingShot:
			weaponPattern = ProjectilePattern::TripleShot;
			break;
		case ProjectilePattern::IncendiaryShot:
			weaponPattern = ProjectilePattern::AimedShot;
			break;
		case ProjectilePattern::AimedShot:
			weaponPattern = ProjectilePattern::DoubleShot;
			break;
		case ProjectilePattern::DoubleShot:
			weaponPattern = ProjectilePattern::HomingShot;
			break;
		case ProjectilePattern::HomingShot:
			weaponPattern = ProjectilePattern::TripleShot;
			break;
		case ProjectilePattern::TripleShot:
			weaponPattern = ProjectilePattern::BasicShot;
			break;
		case ProjectilePattern::StandardLazer:
			weaponPattern = ProjectilePattern::JoesLazer;
			break;
		case ProjectilePattern::JoesLazer:
			weaponPattern = ProjectilePattern::QuadShot;
			break;
		case ProjectilePattern::QuadShot:
			weaponPattern = ProjectilePattern::PhotonPacket;
			break;
		case ProjectilePattern::PhotonPacket:
			weaponPattern = ProjectilePattern::PhotonStream;
			break;
		case ProjectilePattern::PhotonStream:
			weaponPattern = ProjectilePattern::PhotonTriplet;
			break;
		case ProjectilePattern::PhotonTriplet:
			weaponPattern = ProjectilePattern::PhotonQuartet;
			break;
		case ProjectilePattern::PhotonQuartet:
			weaponPattern = ProjectilePattern::IMMAFIRINMAHLAZOR;
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
